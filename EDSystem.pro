#-------------------------------------------------
#
# Project created by QtCreator 2019-01-27T07:20:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EDSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
    src/configuration/firstconfig.cpp \
    src/menu.cpp \
    src/systems.cpp \
    src/stations.cpp \
    src/database.cpp \
    src/model/systemdatabase.cpp \
    src/model/stationdatabase.cpp \
    src/dialog/stationdialog.cpp \
    src/productcat.cpp \
    src/model/productcatdatabase.cpp \
    src/dialog/productdialog.cpp \
    src/products.cpp \
    src/model/productdatabase.cpp

HEADERS += \
    src/configuration/firstconfig.h \
    src/menu.h \
    src/systems.h \
    src/stations.h \
    src/database.h \
    src/model/systemdatabase.h \
    src/model/stationdatabase.h \
    src/dialog/stationdialog.h \
    src/productcat.h \
    src/model/productcatdatabase.h \
    src/dialog/productdialog.h \
    src/products.h \
    src/model/productdatabase.h

FORMS += \
        src\menu.ui \
    src/configuration/firstconfig.ui \
    src/systems.ui \
    src/stations.ui \
    src/dialog/stationdialog.ui \
    src/productcat.ui \
    src/dialog/productdialog.ui \
    src/products.ui

DISTFILES += \
    sql/base.sql
