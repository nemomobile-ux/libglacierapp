set(SRC libglacierconfig.cpp)

add_executable(glacierconfig ${SRC})

set(QT_LIB_LIST Core Gui Qml Quick)
find_qt_package("${QT_LIB_LIST}" REQUIRED )
add_qt_library(QT_DEPLIBS "${QT_LIB_LIST}")

target_link_libraries(glacierconfig PRIVATE
    Glacier${QT_PKG_VER}::App
    ${QT_DEPLIBS}
    PkgConfig::MLITE)

install(TARGETS glacierconfig RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR})
