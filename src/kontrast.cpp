/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 *
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

#include "kontrast.h"

#include <QtMath>
#include <QRandomGenerator>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusObjectPath>
#include <QDBusConnection>
#include <QDebug>


QDBusArgument &operator <<(QDBusArgument &arg, const Kontrast::ColorRGB &color)
{
    arg.beginStructure();
    arg << color.red << color.green << color.blue;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator >>(const QDBusArgument &arg, Kontrast::ColorRGB &color)
{
    double red, green, blue;
    arg.beginStructure();
    arg >> red >> green >> blue;
    color.red = red;
    color.green = green;
    color.blue = blue;
    arg.endStructure();

    return arg;
}


Kontrast::Kontrast(KAboutData about, QObject *parent)
    : QObject(parent)
    , m_about(about)
{
    setObjectName(QStringLiteral("Kontrast"));

    qDBusRegisterMetaType<ColorRGB>();
}

QColor Kontrast::textColor() const
{
    return m_textColor;
}

void Kontrast::setTextColor(const QColor textColor)
{
    if (textColor == m_textColor) {
        return;
    }

    m_textColor = textColor;
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::textHue() const
{
    return qBound(0, m_textColor.hslHue(), 359);
}

void Kontrast::setTextHue(int hue)
{
    if (m_textColor.hslHue() == hue) {
        return;
    }
    m_textColor.setHsl(hue, m_textColor.hslSaturation(), m_textColor.lightness());
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::textLightness() const
{
    return m_textColor.lightness();
}

void Kontrast::setTextLightness(int lightness)
{
    if (m_textColor.lightness() == lightness) {
        return;
    }
    m_textColor.setHsl(m_textColor.hslHue(), m_textColor.hslSaturation(), lightness);
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::textSaturation() const
{
    return m_textColor.saturation();
}

void Kontrast::setTextSaturation(int saturation)
{
    if (m_textColor.saturation() == saturation) {
        return;
    }
    m_textColor.setHsl(m_textColor.hslHue(), saturation, m_textColor.lightness());
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

QColor Kontrast::backgroundColor() const
{
    return m_backgroundColor;
}

void Kontrast::setBackgroundColor(const QColor backgroundColor)
{
    if (backgroundColor == m_backgroundColor) {
        return;
    }

    m_backgroundColor = backgroundColor;
    Q_EMIT backgroundColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::backgroundHue() const
{
    return qBound(0, m_backgroundColor.hslHue(), 359);
}

void Kontrast::setBackgroundHue(int hue)
{
    if (m_backgroundColor.hslHue() == hue) {
        return;
    }
    m_backgroundColor.setHsl(hue, m_backgroundColor.hslSaturation(), m_backgroundColor.lightness());
    Q_EMIT backgroundColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::backgroundLightness() const
{
    return m_backgroundColor.lightness();
}

void Kontrast::setBackgroundLightness(int lightness)
{
    if (m_backgroundColor.lightness() == lightness) {
        return;
    }
    m_backgroundColor.setHsl(m_backgroundColor.hslHue(), m_backgroundColor.hslSaturation(), lightness);
    Q_EMIT backgroundColorChanged();
    Q_EMIT contrastChanged();
}

int Kontrast::backgroundSaturation() const
{
    return m_backgroundColor.saturation();
}

void Kontrast::setBackgroundSaturation(int saturation)
{
    if (m_backgroundColor.saturation() == saturation) {
        return;
    }
    m_backgroundColor.setHsl(m_backgroundColor.hslHue(), saturation, m_backgroundColor.lightness());
    Q_EMIT backgroundColorChanged();
    Q_EMIT contrastChanged();
}

qreal luminosity(const QColor color)
{
    // http://www.w3.org/TR/WCAG20/#relativeluminancedef
    const qreal red = color.redF();
    const qreal green = color.greenF();
    const qreal blue = color.blueF();

    const qreal redLum = (red <= 0.03928) ? red / 12.92 : qPow(((red + 0.055) /  1.055), 2.4);
    const qreal greenLum = (green <= 0.03928) ? green / 12.92 : qPow(((green + 0.055) /  1.055), 2.4);
    const qreal blueLum = (blue <= 0.03928) ? blue / 12.92 : qPow(((blue + 0.055) /  1.055), 2.4);

    return 0.2126 * redLum + 0.7152 * greenLum + 0.0722 * blueLum;
}

qreal Kontrast::contrast() const
{
    const qreal lum1 = luminosity(m_textColor);
    const qreal lum2 = luminosity(m_backgroundColor);

    if (lum1 > lum2) {
        return (lum1 + 0.05) / (lum2 + 0.05);
    }

    return (lum2 + 0.05) / (lum1 + 0.05);
}

void Kontrast::random()
{
    do {
        m_textColor = QColor::fromRgb(QRandomGenerator::global()->generate());
        m_backgroundColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    } while (contrast() < 3.5);
    Q_EMIT backgroundColorChanged();
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

void Kontrast::reverse()
{
    const QColor temp = m_textColor;
    m_textColor = m_backgroundColor;
    m_backgroundColor = temp;
    Q_EMIT backgroundColorChanged();
    Q_EMIT textColorChanged();
    Q_EMIT contrastChanged();
}

QColor Kontrast::displayTextColor() const
{
    if (contrast() > 3.0) {
        return m_textColor;
    }

    if (luminosity(m_backgroundColor) > 0.5) {
        return Qt::black;
    }
    return Qt::white;
}

KAboutData Kontrast::about() const
{
    return m_about;
}

QColor Kontrast::pixelAt(const QImage &image, int x, int y) const
{
    return image.pixelColor(x, y);
}

void Kontrast::grabColor()
{
    QDBusMessage message = QDBusMessage::createMethodCall(QLatin1String("org.freedesktop.portal.Desktop"),
                                                          QLatin1String("/org/freedesktop/portal/desktop"),
                                                          QLatin1String("org.freedesktop.portal.Screenshot"),
                                                          QLatin1String("PickColor"));
    message << QLatin1String("x11:") << QVariantMap{};
    QDBusPendingCall pendingCall = QDBusConnection::sessionBus().asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall);
    connect(watcher, &QDBusPendingCallWatcher::finished, [this] (QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<QDBusObjectPath> reply = *watcher;
        if (reply.isError()) {
            qWarning() << "Couldn't get reply";
            qWarning() << "Error: " << reply.error().message();
        } else {
            QDBusConnection::sessionBus().connect(QString(),
                                                  reply.value().path(),
                                                  QLatin1String("org.freedesktop.portal.Request"),
                                                  QLatin1String("Response"),
                                                  this,
                                                  SLOT(gotColorResponse(uint, QVariantMap)));
        }
    });
}

QColor Kontrast::grabbedColor() const
{
    return m_grabbedColor;
}

void Kontrast::gotColorResponse(uint response, const QVariantMap& results)
{
    if (!response) {
        if (results.contains(QLatin1String("color"))) {
            auto color = qdbus_cast<ColorRGB>(results.value(QLatin1String("color")));
            m_grabbedColor = QColor(color.red * 256, color.green * 256, color.blue * 256);
            emit grabbedColorChanged();
        }
    } else {
        qWarning() << "Failed to take screenshot";
    }
}
