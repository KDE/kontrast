add_executable(kontrast
    main.cpp
    kontrast.cpp
    savedcolormodel.cpp
    resources.qrc)
    
target_link_libraries(kontrast
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Sql
    Qt5::Widgets
    KF5::I18n
    KF5::CoreAddons)
    
install(TARGETS kontrast ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
