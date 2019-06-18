QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++14

INCLUDEPATH += "../../"
INCLUDEPATH += "googletest"
INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googlemock"
INCLUDEPATH += "googlemock/include"

SOURCES += \
    main.cpp \
    ../../bplustree.cpp \
    ../../dateandtime.cpp \
    ../../hashtable.cpp \
    ../../list.cpp \
    ../../rbtree.cpp \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc

FORMS += \
    ../../mainwindow.ui \

HEADERS += \
    ../../bplustree.h \
    ../../dateandtime.h \
    ../../hashtable.h \
    ../../list.h \
    ../../rbtree.h \
    main.h
