QT       += core gui
QT += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorcontainer.cpp \
    colorsectorscollection.cpp \
    datahandler.cpp \
    main.cpp \
    mainwindow.cpp \
    palettemodel.cpp \
    threadcolorcollection.cpp \
    threadcolormodel.cpp \
    userpage.cpp

HEADERS += \
    colorcontainer.h \
    colorsectorscollection.h \
    datahandler.h \
    mainwindow.h \
    palettemodel.h \
    threadcolorcollection.h \
    threadcolormodel.h \
    userpage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MainPage.qml

RESOURCES += \
    qml.qrc \
    resources.qrc
