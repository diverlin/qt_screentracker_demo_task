QT += core gui widgets sql

include(qt_screentracker_demo_task.pri)

SOURCES += \
    $$PWD/main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
