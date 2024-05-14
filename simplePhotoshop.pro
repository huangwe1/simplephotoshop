QT       += core gui
QT += printsupport
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simplePhotoshop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    cdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    fillingdialog.cpp \
    photoset.cpp \
    photoshape.cpp \
    second.cpp \
    sizedialog.cpp \
    third.cpp

HEADERS += \
    cdialog.h \
    mainwindow.h \
    fillingdialog.h \
    photoset.h \
    photoshape.h \
    second.h \
    sizedialog.h \
    third.h
FORMS += \
    fillingdialog.ui \
    second.ui \
    sizedialog.ui \
    third.ui

RESOURCES += \
    icon.qrc
