set(SRC libglacierconfig.cpp)

add_executable(glacierconfig ${SRC})

target_link_libraries(glacierconfig PRIVATE
    Glacier::App
    PkgConfig::MLITE5)

install(TARGETS glacierconfig RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR})
