set(SRC main.cpp)

find_package(Qt5QuickCompiler)
qt_add_resources(RESOURCES glacierexample.qrc)

if(USE_QT6)
    set(PACKAGE glacierexample6)
    set(LIB Glacier6::App)
else()
    set(PACKAGE glacierexample)
    set(LIB Glacier5::App)
endif()

add_executable(${PACKAGE} ${SRC} ${RESOURCES})

set(QT_LIB_LIST Core Gui Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

target_link_libraries(${PACKAGE}
        ${QT_DEPLIBS}
        ${LIB})

install(TARGETS ${PACKAGE} RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
