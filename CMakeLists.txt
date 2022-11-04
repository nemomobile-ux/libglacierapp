cmake_minimum_required(VERSION 3.6.0)

project(glacierapp
        VERSION 1.0.0
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
include(QtVersionCompat)

set(QT_MIN_VERSION "5.11.0")
set(QT_LIB_LIST Core Gui Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif()

find_package(PkgConfig)
if(USE_QT6)
pkg_check_modules(MLITE mlite6 IMPORTED_TARGET)
else()
pkg_check_modules(MLITE mlite5 IMPORTED_TARGET)
endif()

if(MLITE_FOUND)
        set_property(GLOBAL APPEND PROPERTY PACKAGES_FOUND mlite)
else()
        set_property(GLOBAL APPEND PROPERTY PACKAGES_NOT_FOUND mlite)
endif()

add_subdirectory(src)
if(MLITE_FOUND)
    add_subdirectory(tools)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

install(FILES
    cmake/modules/QtVersionCompat.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PACKAGE}
    COMPONENT Devel)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
