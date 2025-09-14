// SPDX-FileCopyrightText: 2020 Carl Schwan <carl@carlschwan.eu>
// SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QColor>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <qqmlregistration.h>

class ThreadedDatabase;

struct ColorEntry {
    using ColumnTypes = std::tuple<int, QString, QColor, QColor>;

    int id;
    QString name;
    QColor textColor;
    QColor backgroundColor;
};

/**
 * @brief Store all the user's favorite color combinations.
 */
class SavedColorModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ColorStore)
    QML_SINGLETON

public:
    enum ColorRoles {
        Id = Qt::UserRole + 1,
        Name,
        TextColor,
        BackgroundColor,
    };

public:
    explicit SavedColorModel(QObject *parent = nullptr);
    ~SavedColorModel() override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;

    Q_INVOKABLE void addColor(const QString &name, const QColor &foreground, const QColor &background);
    Q_INVOKABLE void removeColor(int index);

private:
    std::vector<ColorEntry> m_colors;
    std::unique_ptr<ThreadedDatabase> m_database;
};
