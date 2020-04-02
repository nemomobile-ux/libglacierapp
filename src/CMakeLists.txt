set(SRC glacierapp.cpp)
set(HEADERS glacierapp.h)

add_library(glacierapp SHARED ${SRC} ${HEADERS})
add_library(Glacier::App ALIAS glacierapp)

target_link_libraries(glacierapp PUBLIC
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick)

if(MLITE5_FOUND)
	add_definitions(-DHAS_MLITE5)
	target_link_libraries(glacierapp PRIVATE
		PkgConfig::MLITE5)
endif()

if(BOOSTABLE_FOUND)
	add_definitions(-DHAVE_CACHE=1)
	set(BOOSTABLE_REQUIRES "qdeclarative5-boostable")
	target_link_libraries(glacierapp PRIVATE
		PkgConfig::BOOSTABLE)
endif()

target_include_directories(glacierapp PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include/libglacierapp>)

set_target_properties(glacierapp PROPERTIES
	EXPORT_NAME App
	SOVERSION ${PROJECT_VERSION_MAJOR}
	VERSION ${PROJECT_VERSION})

# Install the library
install(TARGETS glacierapp
	EXPORT GlacierTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install headers
install(FILES ${HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libglacierapp
	COMPONENT Devel)

# Configure and install the pkgconfig file
configure_file(libglacierapp.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/glacierapp.pc
	@ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glacierapp.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# Configure and install the CMake Config file
include(CMakePackageConfigHelpers)
set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/glacierapp/)

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
#export(TARGETS glacierapp
#	NAMESPACE Glacier::
#	FILE GlacierTargets.cmake)
