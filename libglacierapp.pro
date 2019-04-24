TEMPLATE=subdirs
SUBDIRS += src examples
examples.depends = src

DISTFILES += \
    rpm/libglacierapp.spec
