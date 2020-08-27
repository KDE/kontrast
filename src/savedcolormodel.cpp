/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

#include "savedcolormodel.h"

#include <QCoreApplication>
#include <QColor>
#include <QDir>
#include <QStandardPaths>
#include <QSqlRecord>
#include <QSqlError>

SavedColorModel::SavedColorModel(QObject *parent)
    : QSqlTableModel(parent)
{
    if (!QSqlDatabase::database().tables().contains(QStringLiteral("SavedColorModel"))) {
        const auto statement = QStringLiteral(R"RJIENRLWEY(
            CREATE TABLE IF NOT EXISTS SavedColorModel (
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                Name TEXT NOT NULL,
                ForegroundColor BLOB NOT NULL,
                BackgroundColor BLOB NOT NULL
            )
        )RJIENRLWEY");
        auto query = QSqlQuery();
        if (!query.exec()) {
            qCritical() << query.lastError() << "while creating table";
        }
    }

    setTable(QStringLiteral("SavedColorModel"));
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant SavedColorModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::EditRole) {
        return QSqlTableModel::data(index, Qt::EditRole);
    }
    int parentColumn = 0;
    if (role == Qt::UserRole + 0 + 1) { // ID
        parentColumn = 0;
    } else if (role == Qt::UserRole + 1 + 1) { // Name
        parentColumn = 0;
    } else if (role == Qt::UserRole + 2 + 1) { // ForegroundColor
        parentColumn = 2;
    } else { // BackgroundColor
        parentColumn = 3;
    }
    QModelIndex parentIndex = createIndex(index.row(), parentColumn);
    return QSqlTableModel::data(parentIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> SavedColorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    for (int i = 0; i < this->record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return roles;
}

bool SavedColorModel::addColor(const QString& name, const QColor& foreground, const QColor& background)
{
    QSqlRecord newRecord = this->record();
    newRecord.setValue(QStringLiteral("Name"), name);
    newRecord.setValue(QStringLiteral("ForegroundColor"), foreground);
    newRecord.setValue(QStringLiteral("BackgroundColor"), background);

    bool result = insertRecord(rowCount(), newRecord);
    result &= submitAll();
    return result;
}

bool SavedColorModel::removeColor(int index)
{
    bool result = removeRow(index);
    result &= submitAll();
    return result;
}
