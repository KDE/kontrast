# SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

# KDE Application Version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "23")
set (RELEASE_SERVICE_VERSION_MINOR "07")
set (RELEASE_SERVICE_VERSION_MICRO "70")
set (RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kontrast VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION "5.15.0")
set(KF_MIN_VERSION "5.92.0")

include(FeatureSummary)

################# set KDE specific information #################
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPoQmTools)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMDeprecationSettings)
if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX KONTRAST
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/config-kontrast.h"
)

################# Find dependencies #################
find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Qml QuickControls2 Svg Sql)
find_package(KF${KF_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS Kirigami2 I18n CoreAddons)

if(NOT ANDROID)
    find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus Widgets)
    find_package(KF${KF_MAJOR_VERSION}DocTools ${KF_MIN_VERSION} REQUIRED)
endif()

################# build and install #################
add_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
ecm_set_disabled_deprecation_versions(QT 6.5  KF 5.240.0)
add_subdirectory(src)

if(NOT ANDROID)
    add_subdirectory(doc)
    kdoctools_install(po)
endif()

install(PROGRAMS org.kde.kontrast.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kontrast.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES org.kde.kontrast.svg DESTINATION ${KDE_INSTALL_FULL_ICONDIR}/hicolor/scalable/apps)

ki18n_install(po)


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

if(ANDROID)
    kirigami_package_breeze_icons(ICONS
        go-home
        favorite
        help-symbolic
        help-about-symbolic
        applications-graphics
        color-picker
        reverse
        randomize
    )
endif()

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
        
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
