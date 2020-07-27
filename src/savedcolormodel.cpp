/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: AGPL-3.0-or-later
 */

#include "savedcolormodel.h"

#include <QColor>
#include <QDebug>

SavedColorModel::SavedColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_colorCombinations.append(ColorCombination(QColor("black"), QColor("white")));
    m_colorCombinations.append(ColorCombination(QColor("red"), QColor("red")));
    m_colorCombinations.append(ColorCombination(QColor("white"), QColor("red")));
    m_colorCombinations.append(ColorCombination(QColor("yellow"), QColor("red")));
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
    qDebug() << "called" << role;
    /*if (!index.isValid()) {
        return QVariant();
    }*/
    
    if (role == TextColor) {
        return m_colorCombinations[index.row()].textColor;
    } else if (role == BackgroundColor) {
        qDebug() << m_colorCombinations[index.row()].backgroundColor;
        return m_colorCombinations[index.row()].backgroundColor;
    }
    
    return QVariant();
}

int SavedColorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    qDebug() << "count called with " << m_colorCombinations.count();
    return m_colorCombinations.count();
}

void SavedColorModel::addColorCombination(QColor textColor, QColor backgroundColor)
{
    beginInsertRows(QModelIndex(), m_colorCombinations.count(), 0);
    m_colorCombinations.append(ColorCombination(textColor, backgroundColor));
    endInsertRows();
}
