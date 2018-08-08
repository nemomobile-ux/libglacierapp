TEMPLATE = lib
TARGET = glacierapp
QT += gui qml quick
CONFIG += qt link_pkgconfig

packagesExist(qdeclarative5-boostable) {
    message("Building with qdeclarative-boostable support")
    LIBS += -rdynamic -lmdeclarativecache5
    DEFINES += HAVE_CACHE=1
    QMAKE_CXXFLAGS += -fPIC -I/usr/include/mdeclarativecache5
    QMAKE_PKGCONFIG_REQUIRES += qdeclarative5-boostable
} else {
    warning("qdeclarative-boostable not available; startup times will be slower")
}

VERSION = 0.1.0

# Input
SOURCES += \
    glacierapp.cpp

HEADERS += \
    glacierapp.h

target.path = /usr/lib

public_headers.files = $$HEADERS
public_headers.path = /usr/include/lib$${TARGET}

CONFIG += create_pc create_prl no_install_prl

QMAKE_PKGCONFIG_NAME = glacierapp
QMAKE_PKGCONFIG_DESCRIPTION = Glacier applications wrapper library
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_INCDIR = /usr/include/lib$${TARGET}

MAKE_SUBSTITUTES += $${pkgconfig.files}
pkgconfig.CONFIG = no_check_exist
pkgconfig.path  = $${INSTALL_LIBDIR}/pkgconfig
QMAKE_EXTRA_TARGETS += pkgconfig
QMAKE_CLEAN += $${pkgconfig.files}

INSTALLS += target public_headers

DISTFILES += \
    ../rpm/libglacierapp.spec
