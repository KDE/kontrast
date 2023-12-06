# SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(kontrast
    main.cpp
    kontrast.cpp kontrast.h
    savedcolormodel.cpp savedcolormodel.h
    clipboard.cpp clipboard.h
    resources.qrc
)

target_link_libraries(kontrast
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
    KF6::CoreAddons)

if (ANDROID)
    ecm_add_android_apk(kontrast ANDROID_DIR ${CMAKE_SOURCE_DIR}/android)
endif()

if(TARGET Qt6::DBus)
    target_link_libraries(kontrast Qt6::DBus Qt6::Widgets)
endif()

install(TARGETS kontrast ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
