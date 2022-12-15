set(SRC main.cpp)

if(QT_MAJOR_VERSION EQUAL 5)
    find_package(Qt5QuickCompiler)
    qt5_add_resources(RESOURCES glacierexample.qrc)
else()
    qt6_add_resources(RESOURCES glacierexample.qrc)
endif()

add_executable(glacierexample ${SRC} ${RESOURCES})
target_link_libraries(glacierexample
        Qt${QT_MAJOR_VERSION}::Qml
        Qt${QT_MAJOR_VERSION}::Quick
        Glacier::App)

install(TARGETS glacierexample RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR})
