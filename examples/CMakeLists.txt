set(SRC main.cpp)

if(!USE_QT6)
    find_package(Qt5QuickCompiler)
endif()
qt_add_resources(RESOURCES glacierexample.qrc)

set(PACKAGE glacierexample)
set(LIB Glacier${LIBGLACIER_PKG_VER}::App)

add_executable(${PACKAGE} ${SRC} ${RESOURCES})

set(QT_LIB_LIST Core Gui Qml Quick)
find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

target_link_libraries(${PACKAGE}
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    ${LIB})

install(TARGETS ${PACKAGE} RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
