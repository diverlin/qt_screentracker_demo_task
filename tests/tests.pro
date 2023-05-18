QT += testlib

include($$PWD/../qt_screentracker_app/qt_screentracker_lib.pri)

INCLUDEPATH += $$PWD/../qt_screentracker_app

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/datastoragetest.cpp \
    $$PWD/imagecomparatortest.cpp \
    $$PWD/fixedqueuetest.cpp \

HEADERS += \
    $$PWD/datastoragetest.h \
    $$PWD/imagecomparatortest.h \
    $$PWD/fixedqueuetest.h \

RESOURCES += \
    tests.qrc




