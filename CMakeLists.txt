cmake_minimum_required(VERSION 3.10.0)

project(glacierapp
    VERSION 1.2
    DESCRIPTION "Glacier applications wrapper library")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(BUILD_EXAMPLES "Build the example projects" OFF)

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "6.0.0")
find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif()

find_package(PkgConfig)
pkg_check_modules(MLITE mlite6 IMPORTED_TARGET)

if(MLITE_FOUND)
    set_property(GLOBAL APPEND PROPERTY PACKAGES_FOUND mlite)
else()
    set_property(GLOBAL APPEND PROPERTY PACKAGES_NOT_FOUND mlite)
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
