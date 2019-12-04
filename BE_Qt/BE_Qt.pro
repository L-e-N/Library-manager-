#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T10:56:40
#
#-------------------------------------------------

QT += sql

SOURCES   = \
    book.cpp \
            main.cpp \
    library.cpp \
    table.cpp \
    tablewindow.cpp
HEADERS   = \
    book.h \
    connection.h \
    library.h \
    table.h \
    tablewindow.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/tutorials/addressbook/part1
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS part1.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/tutorials/addressbook/part1
INSTALLS += target sources
QT+=widgets
symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)
