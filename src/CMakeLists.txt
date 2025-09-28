# SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(kontrast
    main.cpp
    kontrast.cpp kontrast.h
    savedcolormodel.cpp savedcolormodel.h
    resources.qrc
)

ecm_add_qml_module(kontrast
    URI org.kde.kontrast
    GENERATE_PLUGIN_SOURCE
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/org/kde/kontrast
    DEPENDENCIES
        QtCore
        QtQml
        QtQuick
)

ecm_target_qml_sources(kontrast SOURCES
    qml/Main.qml
    qml/MainPage.qml
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
    KF6::I18nQml
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
