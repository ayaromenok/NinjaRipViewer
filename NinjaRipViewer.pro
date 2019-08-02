QT  += core gui widgets
QT  += 3dcore 3drender 3dinput 3dextras

TARGET = ymv
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/view.cpp\
        src/ycustommesh.cpp \
        src/yripparser.cpp \
        src/ytestscene.cpp
HEADERS += \
        src/mainwindow.h \
        src/view.h \
        src/ycustommesh.h \
        src/yripparser.h \
        src/ytestscene.h
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
