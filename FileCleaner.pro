QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./lib/QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./lib/QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./lib/QXlsx/source/  # current QXlsx source path is ./source/
include(./lib/QXlsx/QXlsx.pri)

SOURCES += \
    main.cpp \
    main_table_model.cpp \
    mainwindow.cpp

HEADERS += \
    main_table_model.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target