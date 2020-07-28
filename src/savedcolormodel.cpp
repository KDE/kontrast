/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: AGPL-3.0-or-later
 */

#include "savedcolormodel.h"

#include <QColor>
#include <KSharedConfig>
#include <KConfigGroup>
#include <QDebug>

SavedColorModel::SavedColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_textColor.append(QColor("black"));
    m_backgroundColor.append(QColor("white"));
    KSharedConfigPtr config = KSharedConfig::openConfig("data", KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup generalGroup(config, "General");
    
    if (generalGroup.exists()) {
        m_textColor = generalGroup.readEntry("backgroundColors", QVariantList());
        m_backgroundColor =  generalGroup.readEntry("textColors", QVariantList());
    }
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
    if (role == TextColor) {
        return m_textColor[index.row()];
    } else if (role == BackgroundColor) {
        return m_backgroundColor[index.row()];
    }
    
    return QVariant();
}

int SavedColorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    qDebug() << m_textColor.count();
    return m_textColor.count();
}

void SavedColorModel::addColor(QColor textColor, QColor backgroundColor)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_textColor.prepend(textColor);
    m_backgroundColor.prepend(backgroundColor);
    endInsertRows();
    saveColors();
}

void SavedColorModel::removeColor(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_textColor.removeAt(index);
    m_backgroundColor.removeAt(index);
    endRemoveRows();
    saveColors();
}


void SavedColorModel::saveColors()
{
    KSharedConfigPtr config = KSharedConfig::openConfig("data", KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    
    KConfigGroup generalGroup(config, "General");
    
    generalGroup.writeEntry("backgroundColors", m_textColor);
    generalGroup.writeEntry("textColors", m_backgroundColor);
    config->sync();
}
