QT       += core gui
QT  += webenginewidgets
QT  += opengl
QT  += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attitudeindicator.cpp \
    lnk_com_port.cpp \
    main.cpp \
    mainwindow.cpp \
    objloader.cpp \
    plane_frame.cpp

HEADERS += \
    attitudeindicator.h \
    lnk_com_port.h \
    mainwindow.h \
    objloader.h \
    plane_frame.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    proekt_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    models/plane/fuselage.mtl \
    models/textures/bricks.jpg
