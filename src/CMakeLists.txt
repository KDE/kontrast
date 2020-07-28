qt5_add_resources(kontrast_SRCS resources.qrc)
add_executable(kontrast
    main.cpp
    kontrast.cpp
    savedcolormodel.cpp
    ${kontrast_SRCS})
    
target_link_libraries(kontrast
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Svg
    KF5::I18n
    KF5::CoreAddons
    KF5::ConfigCore)
    
target_compile_features(kontrast PRIVATE cxx_std_17)
        
install(TARGETS kontrast ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})
