

QT       += core gui


CONFIG += link_pkgconfig
PKGCONFIG += opencv

TARGET = testbench

TEMPLATE = app

SOURCES += \
    main.cpp \
    view.cpp \
    imageprocessing.cpp

HEADERS += \
    view.h \
    imageprocessing.h

FORMS += \
    view.ui
