TEMPLATE = lib
TARGET = libglacierapp
QT += gui qml
CONFIG += qt link_pkgconfig

VERSION = 0.1.0

# Input
SOURCES += \
    glacierapp.cpp

HEADERS += \
    glacierapp.h

target.path = /usr/lib

public_headers.files = $$HEADERS
public_headers.path = /usr/include/$${TARGET}

CONFIG += create_pc create_prl no_install_prl

QMAKE_PKGCONFIG_NAME = GlacierApp
QMAKE_PKGCONFIG_DESCRIPTION = Glacier applications wrapper library
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

MAKE_SUBSTITUTES += $${pkgconfig.files}
pkgconfig.CONFIG = no_check_exist
pkgconfig.path  = $${INSTALL_LIBDIR}/pkgconfig
QMAKE_EXTRA_TARGETS += pkgconfig
QMAKE_CLEAN += $${pkgconfig.files}

INSTALLS += target public_headers

DISTFILES += \
    ../rpm/libglacierapp.spec
