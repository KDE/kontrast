/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * SPDX-FileCopyrightText: (C) 2022 Vlad Rakhmanin <vladimir.rakhmanin@ucdconnect.ie>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QColor>
#include <QImage>
#include <QObject>

/**
 * @brief Main class that expose all the value to the QML.
 */
class Kontrast : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    Q_PROPERTY(int textHue READ textHue WRITE setTextHue NOTIFY textColorChanged)

    Q_PROPERTY(int textSaturation READ textSaturation WRITE setTextSaturation NOTIFY textColorChanged)

    Q_PROPERTY(int textLightness READ textLightness WRITE setTextLightness NOTIFY textColorChanged)

    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    Q_PROPERTY(int backgroundHue READ backgroundHue WRITE setBackgroundHue NOTIFY backgroundColorChanged)

    Q_PROPERTY(int backgroundSaturation READ backgroundSaturation WRITE setBackgroundSaturation NOTIFY backgroundColorChanged)

    Q_PROPERTY(QString fontSizeLabel READ getFontSizeQualityLabel NOTIFY fontSizeChanged)

    Q_PROPERTY(int backgroundLightness READ backgroundLightness WRITE setBackgroundLightness NOTIFY backgroundColorChanged)

    Q_PROPERTY(qreal contrast READ contrast NOTIFY contrastChanged)

    Q_PROPERTY(QColor displayTextColor READ displayTextColor NOTIFY contrastChanged)

    Q_PROPERTY(QColor grabbedColor READ grabbedColor NOTIFY grabbedColorChanged)

public:
    explicit Kontrast(QObject *parent = nullptr);
    ~Kontrast() override = default;

    enum Quality {
        Bad,
        Good,
        Perfect
    };

    Q_ENUM(Quality)

    struct ContrastQualities {
        Quality small;
        Quality medium;
        Quality large;
    };

    struct ColorRGB {
        double red;
        double green;
        double blue;
    };

    QColor textColor() const;
    void setTextColor(const QColor textColor);

    int textHue() const;
    void setTextHue(int hue);

    int textSaturation() const;
    void setTextSaturation(int saturation);

    int textLightness() const;
    void setTextLightness(int lightness);

    int fontSize() const;
    void setFontSize(int fontSize);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor backgroundColor);

    int backgroundHue() const;
    void setBackgroundHue(int hue);

    int backgroundSaturation() const;
    void setBackgroundSaturation(int saturation);

    int backgroundLightness() const;
    void setBackgroundLightness(int lightness);

    qreal contrast() const;

    QColor displayTextColor() const;

    QColor grabbedColor() const;

    QString getFontSizeQualityLabel();

    Q_INVOKABLE void random();
    Q_INVOKABLE void reverse();
    Q_INVOKABLE void grabColor();
    Q_INVOKABLE QColor pixelAt(const QImage &image, int x, int y) const;

private Q_SLOTS:
    void gotColorResponse(uint response, const QVariantMap &results);

Q_SIGNALS:
    void textColorChanged();
    void backgroundColorChanged();
    void contrastChanged();
    void grabbedColorChanged();
    void fontSizeChanged();

private:
    QColor m_textColor;
    QColor m_backgroundColor;
    QColor m_grabbedColor;
    int m_fontSize;

    ContrastQualities getContrastQualities() const;
};

Q_DECLARE_METATYPE(Kontrast::ColorRGB)
