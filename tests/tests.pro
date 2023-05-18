QT += testlib

include($$PWD/../qt_screentracker_app/qt_screentracker_lib.pri)

INCLUDEPATH += $$PWD/../qt_screentracker_app

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/datastoragetest.cpp \
    $$PWD/imagecomparatortest.cpp \

HEADERS += \
    $$PWD/datastoragetest.h \
    $$PWD/imagecomparatortest.h \

RESOURCES += \
    tests.qrc




