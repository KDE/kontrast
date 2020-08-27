/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * SPDX-FileCopyrightText: (C) 2020 Carson Black <uhhadd@gmail.com>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

#pragma once

#include <QAbstractListModel>
#include <QColor>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

struct ColorCombination {
    QColor textColor;
    QColor backgroundColor;
    
    ColorCombination(QColor textColor, QColor backgroundColor)
        : textColor(textColor)
        , backgroundColor(backgroundColor)
    {}
};
    

/**
 * @brief Store all the user's favorite color combinations.
 */
class SavedColorModel : public  QSqlTableModel
{
    Q_OBJECT

public:
    enum ColorRoles {
        TextColor = Qt::UserRole + 1,
        BackgroundColor
    };

public:
    SavedColorModel(QObject *parent = nullptr);

    virtual ~SavedColorModel() override = default;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE bool addColor(const QString& name, const QColor& foreground, const QColor& background);
    Q_INVOKABLE bool removeColor(int index);

private:
    QSqlDatabase m_db;
};
