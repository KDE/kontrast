/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: AGPL-3.0-or-later
 */

#pragma once

#include <QAbstractListModel>
#include <QColor>

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

    /**
     * Value of the saved colors.
     * 
     * @param index The index of the data.
     * @param role The item role, can be TextColor or BackgroundColor
     * @return The color for the given role.
     */
    virtual QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Length of the saved colors.
     *
     * @param parent 
     * @return The lenght of the saved colors.
     */
    virtual int rowCount(const QModelIndex &parent) const override;
    
    Q_INVOKABLE void addColor(QColor textColor, QColor backgroundColor);
    Q_INVOKABLE void removeColor(int index);
    
private:
    void saveColors();
    
    QList<QVariant> m_textColor;
    QList<QVariant> m_backgroundColor;
};
