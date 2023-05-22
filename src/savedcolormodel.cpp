// SPDX-FileCopyrightText: 2020 Carl Schwan <carl@carlschwan.eu>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "savedcolormodel.h"

#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QStringBuilder>

#include <ThreadedDatabase>

#include <QCoroFuture>
#include <QCoroTask>

SavedColorModel::SavedColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
    DatabaseConfiguration config;
    config.setType(DatabaseType::SQLite);
    config.setDatabaseName(
        QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/") + qApp->applicationName()));

    m_database = ThreadedDatabase::establishConnection(config);
    m_database->runMigrations(QStringLiteral(":/contents/migrations/"));

    auto future = m_database->getResults<ColorEntry>(QStringLiteral("select * from SavedColorModel"));
    QCoro::connect(std::move(future), this, [this](auto &&colors) {
        beginResetModel();
        m_colors = colors;
        endResetModel();
    });
}

SavedColorModel::~SavedColorModel() = default;

QVariant SavedColorModel::data(const QModelIndex &index, int role) const
{
    const auto &entry = m_colors.at(index.row());
    switch (role) {
    case ColorRoles::Id:
        return entry.id;
    case ColorRoles::Name:
        return entry.name;
    case ColorRoles::TextColor:
        return entry.textColor;
    case ColorRoles::BackgroundColor:
        return entry.backgroundColor;
    }

    return {};
}

int SavedColorModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_colors.size();
}

QHash<int, QByteArray> SavedColorModel::roleNames() const
{
    return {{ColorRoles::Id, "id"}, {ColorRoles::Name, "name"}, {ColorRoles::TextColor, "textColor"}, {ColorRoles::BackgroundColor, "backgroundColor"}};
}

void SavedColorModel::addColor(const QString &name, const QColor &foreground, const QColor &background)
{
    m_database->execute(QStringLiteral("insert into SavedColorModel (Name, ForegroundColor, BackgroundColor) values (?, ?, ?)"), name, foreground, background);

    beginInsertRows({}, m_colors.size(), m_colors.size());
    m_colors.push_back(ColorEntry{.id = int(m_colors.size()), .name = name, .textColor = foreground, .backgroundColor = background});
    endInsertRows();
}

void SavedColorModel::removeColor(int index)
{
    m_database->execute(QStringLiteral("delete from SavedColorModel where ID = ?"), m_colors[index].id);
    beginRemoveRows({}, index, index);
    m_colors.erase(m_colors.begin() + index);
    endRemoveRows();
}
