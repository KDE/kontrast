add_executable(kontrast
    main.cpp
    kontrast.cpp
    savedcolormodel.cpp
    resources.qrc)
    
target_link_libraries(kontrast
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Sql
    Qt::Svg
    KF5::I18n
    KF5::CoreAddons)
    
if(TARGET Qt::DBus)
    target_link_libraries(kontrast Qt::DBus Qt::Widgets)
endif()

install(TARGETS kontrast ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
