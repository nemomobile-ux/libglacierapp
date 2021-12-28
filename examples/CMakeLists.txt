set(SRC main.cpp)

find_package(Qt5QuickCompiler)
qtquick_compiler_add_resources(RESOURCES glacierexample.qrc)

add_executable(glacierexample ${SRC} ${RESOURCES})
target_link_libraries(glacierexample
	Qt5::Qml
	Qt5::Quick
	Glacier::App)

install(TARGETS glacierexample RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
