set(SRC libglacierconfig.cpp)

add_executable(glacierconfig ${SRC})

target_link_libraries(glacierconfig PRIVATE
    Glacier::App
    PkgConfig::MLITE)

install(TARGETS glacierconfig RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR})
