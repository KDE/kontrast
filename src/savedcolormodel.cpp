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
    m_colorCombinations.append(ColorCombination(QColor("black"), QColor("red")));
    m_colorCombinations.append(ColorCombination(QColor("black"), QColor("red")));
    m_colorCombinations.append(ColorCombination(QColor("black"), QColor("red")));
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
    qDebug() << "called";
    if (!index.isValid()) {
        return QVariant();
    }
    
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
    return m_colorCombinations.count();
}
