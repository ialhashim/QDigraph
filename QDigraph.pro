QT += core gui widgets webkitwidgets

TEMPLATE     = lib
CONFIG      += staticlib

TARGET      = QDigraphLib
CONFIG(debug, debug|release) {CFG = debug} else {CFG = release}
DESTDIR     = $$PWD/$$CFG/lib

SOURCES     += Viewer.cpp
FORMS       += Viewer.ui
HEADERS     += Viewer.h

RESOURCES   += Viewer.qrc
