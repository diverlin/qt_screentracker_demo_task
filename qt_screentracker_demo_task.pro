QT += core gui widgets sql testlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/gallerywidget.cpp \
    src/screensshooter.cpp \
    src/hashsumutils.cpp \
    src/imagecomparator.cpp \
    src/datastorage.cpp \
    src/pathprovider.cpp \
    test/datastoragetest.cpp \

HEADERS += \
    src/mainwindow.h \
    src/gallerywidget.h \
    src/screensshooter.h \
    src/hashsumutils.h \
    src/imagecomparator.h \
    src/datastorage.h \
    src/pathprovider.h \
    test/datastoragetest.h \

FORMS += \
    forms/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
