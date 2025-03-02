set(SRC main.cpp)

if(!USE_QT6)
    find_package(Qt5QuickCompiler)
endif()
qt_add_resources(RESOURCES glacierexample.qrc)

set(PACKAGE glacierexample)
set(LIB Glacier${LIBGLACIER_PKG_VER}::App)

add_executable(${PACKAGE} ${SRC} ${RESOURCES})

set(QT_LIB_LIST Core Gui Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

target_link_libraries(${PACKAGE}
        ${QT_DEPLIBS}
        ${LIB})

install(TARGETS ${PACKAGE} RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
