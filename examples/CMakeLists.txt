set(SRC main.cpp)

add_executable(glacierexample ${SRC})
target_link_libraries(glacierexample
	Qt5::Qml
	Qt5::Quick
	Glacier::App)

install(TARGETS glacierexample RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES glacierexample.qml
	DESTINATION ${CMAKE_INSTALL_DATADIR}/glacierexample/qml)
