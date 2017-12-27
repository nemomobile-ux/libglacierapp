TEMPLATE = app
TARGET = glacierexample

SOURCES += main.cpp

QT += quick qml

CONFIG += qt link_pkgconfig

DEPENDPATH += ../src
INCLUDEPATH += ../src

LIBS += -L../src -llibglacierapp

target.path = /usr/bin

qml.files = glacierexample.qml
qml.path = /usr/share/glacierexample/qml

DISTFILES += \
    glacierexample.qml

INSTALLS += target qml
