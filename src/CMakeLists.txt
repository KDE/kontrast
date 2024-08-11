# SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(kontrast
    main.cpp
    kontrast.cpp kontrast.h
    savedcolormodel.cpp savedcolormodel.h
    resources.qrc
)

ecm_add_qml_module(kontrast URI "org.kde.kontrast" VERSION 1.0)

ecm_target_qml_sources(kontrast SOURCES
    qml/Main.qml
    qml/MainPage.qml
    qml/AboutPage.qml
    qml/FavoritePage.qml
    qml/HelpPage.qml
)

target_link_libraries(kontrast PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
    Qt6::Svg
    FutureSQL6::FutureSQL
    QCoro6::Core
    KF6::I18n
    KF6::CoreAddons
)

if (TARGET KF6::Crash)
target_link_libraries(kontrast PRIVATE
    KF6::Crash
)
endif()	

if (ANDROID)
    ecm_add_android_apk(kontrast ANDROID_DIR ${CMAKE_SOURCE_DIR}/android)
endif()

if(TARGET Qt6::DBus)
    target_link_libraries(kontrast PRIVATE Qt6::DBus Qt6::Widgets)
endif()

install(TARGETS kontrast ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
