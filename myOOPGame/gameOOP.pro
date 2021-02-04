QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coinobject.cpp \
    coinobjectfactory.cpp \
    commandclass.cpp \
    consolelogger.cpp \
    controller.cpp \
    enemybehaviors.cpp \
    exitobject.cpp \
    exitobjectfactory.cpp \
    field.cpp \
    filelogger.cpp \
    gamecommands.cpp \
    gameruller.cpp \
    loggerholder.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playerstrategy.cpp \
    saveandload.cpp \
    square.cpp \
    vortexobject.cpp \
    vortexobjectfactory.cpp \
    wallobject.cpp \
    wallobjectfactory.cpp

HEADERS += \
    LoggerNode.h \
    coinObject.h \
    coinobjectfactory.h \
    command.h \
    commandclass.h \
    consolelogger.h \
    controller.h \
    coords.h \
    direction.h \
    cellobject.h \
    enemy.h \
    enemybehaviors.h \
    enemystate.h \
    exitobject.h \
    exitobjectfactory.h \
    field.h \
    filelogger.h \
    gamecommands.h \
    gameruller.h \
    logger.h \
    loggerholder.h \
    mainwindow.h \
    objectfactory.h \
    player.h \
    playerstrategy.h \
    saveandload.h \
    saveexception.h \
    square.h \
    vortexobject.h \
    vortexobjectfactory.h \
    wallobject.h \
    wallobjectfactory.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc
