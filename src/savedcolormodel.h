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
class SavedColorModel : public QAbstractListModel
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

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual int rowCount(const QModelIndex &parent) const override;

    Q_INVOKABLE bool addColor(const QString& name, const QColor& foreground, const QColor& background);
    Q_INVOKABLE bool removeColor(int index);

    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;
    bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole) override;

private:
    void prefetch(int count, bool reset = false);
    void saveColors();
    void refresh();

    mutable QSqlQuery m_query;
    static const int fetch_size = 255;
    int m_rowCount = 0;
    int m_bottom = 0;
    bool m_atEnd = false;
    QSqlDatabase m_db;
};
