# SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

# KDE Application Version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "25")
set (RELEASE_SERVICE_VERSION_MINOR "12")
set (RELEASE_SERVICE_VERSION_MICRO "1")
set (RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(kontrast VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION "6.6.0")
set(KF_MIN_VERSION "6.8.0")

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
include(ECMAddAndroidApk)
include(ECMQmlModule)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX KONTRAST
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/config-kontrast.h"
)

################# Find dependencies #################
find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Qml QuickControls2 Svg Sql)
find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS Kirigami I18n CoreAddons)
find_package(FutureSQL6 REQUIRED)
find_package(QCoro6 REQUIRED COMPONENTS Core)
find_package(KF6KirigamiAddons 1.4.0 REQUIRED)

if(NOT ANDROID)
    find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus Widgets)
    find_package(KF6DocTools ${KF_MIN_VERSION} REQUIRED)
    find_package(KF6Crash ${KF_MIN_VERSION} REQUIRED)
endif()

################# build and install #################
add_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
ecm_set_disabled_deprecation_versions(QT 6.9.0  KF 6.19.0)
kde_enable_exceptions()

add_subdirectory(src)

if(NOT ANDROID)
    add_subdirectory(doc)
    kdoctools_install(po)
endif()

install(FILES org.kde.kontrast.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kontrast.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES org.kde.kontrast.svg DESTINATION ${KDE_INSTALL_FULL_ICONDIR}/hicolor/scalable/apps)

ki18n_install(po)


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

if(ANDROID)
    kirigami_package_breeze_icons(ICONS
        go-home
        favorite
        help-contents
        help-symbolic
        help-about-symbolic
        applications-graphics
        color-picker
        reverse
        randomize
        arrow-right
        license
    )
endif()

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
