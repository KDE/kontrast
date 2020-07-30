/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

#include "savedcolormodel.h"

#include <QCoreApplication>
#include <QColor>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QSqlError>

const QString DRIVER("QSQLITE");

SavedColorModel::SavedColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Q_ASSERT(QSqlDatabase::isDriverAvailable(DRIVER));
    Q_ASSERT(QDir().mkpath(QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation))));
    m_db = QSqlDatabase::addDatabase(DRIVER);
    const auto path = QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/" + qApp->applicationName());
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        qCritical() << m_db.lastError() << "while opening database at" << path;
    }
    const auto statement = QStringLiteral(R"RJIENRLWEY(
        CREATE TABLE IF NOT EXISTS SavedColorModel (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Name TEXT NOT NULL,
            ForegroundColor BLOB NOT NULL,
            BackgroundColor BLOB NOT NULL
        )
    )RJIENRLWEY");
    auto query = QSqlQuery();
    query.prepare(statement);
    auto ok = query.exec();
    if (!ok) {
        qCritical() << query.lastError() << "while creating table";
    }
    m_query = QSqlQuery(m_db);
    ok = m_query.prepare("SELECT * FROM SavedColorModel");
    if (!ok) {
        qCritical() << m_query.lastError() << "while preparing query";
    }
    ok = m_query.exec();
    if (!ok) {
        qCritical() << m_query.lastError() << "while executing query";
    }
    prefetch(fetch_size);
}

auto SavedColorModel::prefetch(int toRow, bool reset) -> void
{
    if (m_atEnd || toRow <= m_bottom)
        return;

    int oldBottom = m_bottom;
    int newBottom = 0;
    
    if (m_query.seek(toRow)) {
        newBottom = toRow;
    } else {
        int i = oldBottom;
        if (m_query.seek(i)) {
            while (m_query.next()) i++;
            newBottom = i;
        } else {
            newBottom = -1;
        }
        m_atEnd = true;
    }
    if (newBottom >= 0 && newBottom >= oldBottom) {
        if (!reset) beginInsertRows(QModelIndex(), oldBottom + 1, newBottom);
        m_bottom = newBottom;
        if (!reset) endInsertRows();
    }
}

auto SavedColorModel::refresh() -> void
{
    beginResetModel();
    m_bottom = 0;
    m_atEnd = false;
    m_query.seek(0);
    m_query.prepare(m_query.executedQuery());
    m_query.exec();
    prefetch(m_bottom + fetch_size, true);
    endResetModel();
}

auto SavedColorModel::fetchMore(const QModelIndex &parent) -> void {
    Q_UNUSED(parent)
    prefetch(m_bottom + fetch_size);
}

auto SavedColorModel::canFetchMore(const QModelIndex &parent) const -> bool {
    Q_UNUSED(parent)
    return !m_atEnd;
}

QHash<int, QByteArray> SavedColorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextColor] = "textColor";
    roles[BackgroundColor] = "backgroundColor";
    return roles;
}

QVariant SavedColorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (!m_query.seek(index.row())) {
        qCritical() << m_query.lastError() << "when seeking data";
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:
        return m_query.value("Name");
    case TextColor:
        return m_query.value("ForegroundColor");
    case BackgroundColor:
        return m_query.value("BackgroundColor");
    }

    return QVariant();
}

auto SavedColorModel::setData(const QModelIndex &idx, const QVariant &value, int role) -> bool
{
    if (!idx.isValid()) return false;

    if (!m_query.seek(idx.row())) {
        qCritical() << m_query.lastError() << "when seeking data";
        return false;
    }

    const auto statement = QStringLiteral("UPDATE SavedColorModel SET %1 = :value WHERE ID = :id");
    QString mutated;

    switch (role) {
    case Qt::DisplayRole:
        mutated = statement.arg("Name"); break;
    case TextColor:
        mutated = statement.arg("ForegroundColor"); break;
    case BackgroundColor:
        mutated = statement.arg("BackgroundColor"); break;
    default:
        return false;
    }

    QSqlQuery query;
    query.prepare(mutated);
    query.bindValue(":value", value);
    query.bindValue(":id", m_query.value("ID"));

    auto ok = query.exec();
    if (!ok) {
        qCritical() << m_query.lastError() << "when updating data";
        return false;
    }
    refresh();
    return true;
}

int SavedColorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_bottom;
}

bool SavedColorModel::addColor(const QString& name, const QColor& foreground, const QColor& background)
{
    const auto statement = QStringLiteral(R"RJIENRLWEY(
        INSERT INTO SavedColorModel
            (Name, ForegroundColor, BackgroundColor)
        VALUES
            ( :name, :foreground, :background )
    )RJIENRLWEY");
    QSqlQuery query;
    query.prepare(statement);
    query.bindValue(":name", name);
    query.bindValue(":foreground", foreground);
    query.bindValue(":background", background);

    auto ok = query.exec();
    if (!ok) {
        qCritical() << m_query.lastError() << "when inserting data";
        return false;
    }
    prefetch(m_bottom + fetch_size);
    return true;
}

bool SavedColorModel::removeColor(int index)
{
    const auto statement = QStringLiteral(R"RJIENRLWEY(
        DELETE FROM SavedColorModel
            WHERE ID = :id
    )RJIENRLWEY");
    QSqlQuery query;
    query.prepare(statement);
    query.bindValue(":id", index);

    auto ok = query.exec();
    if (!ok) {
        qCritical() << m_query.lastError() << "when deleting data";
        return false;
    }
    refresh();
    return true;
}
