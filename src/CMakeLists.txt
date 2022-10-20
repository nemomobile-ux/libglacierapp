set(SRC glacierapp.cpp)
set(HEADERS glacierapp.h)

add_library(glacierapp${QT_PKG_VER} SHARED ${SRC} ${HEADERS})
add_library(Glacier${QT_PKG_VER}::App ALIAS glacierapp${QT_PKG_VER})

set(QT_LIB_LIST Core Gui Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

if(MLITE_FOUND)
    add_definitions(-DHAS_MLITE5)
    target_link_libraries(glacierapp${QT_PKG_VER} PUBLIC PkgConfig::MLITE ${QT_DEPLIBS})
else()
    target_link_libraries(glacierapp${QT_PKG_VER} ${QT_DEPLIBS})
endif()

target_include_directories(glacierapp${QT_PKG_VER} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/libglacierapp${QT_PKG_VER}>)

set_target_properties(glacierapp${QT_PKG_VER} PROPERTIES
    EXPORT_NAME App
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

# Install the library
install(TARGETS glacierapp${QT_PKG_VER}
    EXPORT GlacierTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install headers
install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libglacierapp${QT_PKG_VER}
    COMPONENT Devel)

# Configure and install the pkgconfig file
configure_file(libglacierapp.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/glacierapp${QT_PKG_VER}.pc
    @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glacierapp${QT_PKG_VER}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# Configure and install the CMake Config file
include(CMakePackageConfigHelpers)
set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/glacierapp${QT_PKG_VER}/)

configure_package_config_file(
    "GlacierConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GlacierConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_PREFIX CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_LIBDIR NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/GlacierConfigVersion.cmake
    VERSION ${glacierapp_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(EXPORT GlacierTargets
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    NAMESPACE Glacier::
    COMPONENT Devel)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/GlacierConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GlacierConfigVersion.cmake"
    DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    COMPONENT Devel)
