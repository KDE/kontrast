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
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Sql
    Qt::Svg
    FutureSQL${QT_MAJOR_VERSION}::FutureSQL
    QCoro${QT_MAJOR_VERSION}::Core
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::CoreAddons)
    
if(TARGET Qt::DBus)
    target_link_libraries(kontrast Qt::DBus Qt::Widgets)
endif()

install(TARGETS kontrast ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
