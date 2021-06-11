set(SRC libglacierconfig.cpp)

add_executable(glacierconfig ${SRC})
target_link_libraries(glacierconfig
    PkgConfig::MLITE5
    Glacier::App)

install(TARGETS glacierconfig RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR})
