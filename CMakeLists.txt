cmake_minimum_required(VERSION 3.6.0)

project(glacierapp
	VERSION 0.6.0
	DESCRIPTION "Glacier applications wrapper library")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(BUILD_EXAMPLES "Build the example projects" OFF)

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "5.6.0")
find_package(Qt5 COMPONENTS Gui Qml Quick REQUIRED)

find_package(PkgConfig)
pkg_check_modules(MLITE5 mlite5 IMPORTED_TARGET)
pkg_check_modules(BOOSTABLE qtdeclarative5-boostable IMPORTED_TARGET)

if(MLITE5_FOUND)
	set_property(GLOBAL APPEND PROPERTY PACKAGES_FOUND mlite5)
else()
	set_property(GLOBAL APPEND PROPERTY PACKAGES_NOT_FOUND mlite5)
endif()
if(BOOSTABLE_FOUND)
	set_property(GLOBAL APPEND PROPERTY PACKAGES_FOUND
		qtdeclarative5-boostable)
else()
	set_property(GLOBAL APPEND PROPERTY PACKAGES_NOT_FOUND
		qtdeclarative5-boostable)
	message(WARNING
		"qdeclarative-boostable not available; startup times will be slower")
endif()

add_subdirectory(src)
if(MLITE5_FOUND)
    add_subdirectory(tools)
endif()

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
