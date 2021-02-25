#-------------------------------------------------
#
# Project created by QtCreator 2018-09-30T15:27:37
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = platforma
TEMPLATE = app
#CONFIG += c++14

SOURCES += main.cpp \
    platform/chache/cachefactory.cpp \
    platform/chache/cache.cpp \
    platform/defaultwidget.cpp \
    platform/defaultwidgetmodel.cpp\
    platform/logger/loggerfactory.cpp \
    platform/logger/logger.cpp \
    platform/mainwindow.cpp \
    platform/subprocessmodel.cpp \
    platform/logger/conseleappneder.cpp \
    platform/logger/loggerthread.cpp \
    platform/logger/iappender.cpp \
    platform/viewer.cpp \
    diplom/startform.cpp \
    platform/utils.cpp \
    diplom/servicescontext.cpp \
    diplom/resultfrom.cpp \
    diplom/filters/abstractfilter.cpp \
    diplom/filters/blackwhitefilte.cpp \
    diplom/filters/filterutils.cpp \
    diplom/filters/coords.cpp \
    diplom/filters/mysuperfilter.cpp \
    diplom/acinusrecognizer.cpp \
    platform/logger/haslogger.cpp \
    diplom/filters/binarizer.cpp \
    diplom/recognizers/recongnizerschain.cpp \
    diplom/recognizers/acinus.cpp \
    diplom/recognizers/abstractrecognizer.cpp \
    diplom/recognizers/sizerognizer.cpp \
    diplom/recognizers/formrecognizer.cpp \
    diplom/database/da/idataaccess.cpp \
    diplom/database/vo/imagedbmodel.cpp \
    diplom/database/da/csvdataaccess.cpp \
    diplom/database/da/sqllitedataaccess.cpp \
    diplom/database/da/dataaccessfactory.cpp \
    diplom/recognizers/attributerecognizser.cpp \
    diplom/recognizers/gistogrammrecognizer.cpp \
    diplom/form.cpp

HEADERS  += platform/chache/cachefactory.h \
    platform/chache/cache.h \
    platform/defaultwidget.h \
    platform/defaultwidgetmodel.h\
    platform/logger/loggerfactory.h \
    platform/logger/logger.h \
    platform/mainwindow.h \
    platform/subprocessmodel.h \
    platform/logger/conseleappneder.h \
    platform/logger/loggerthread.h \
    platform/logger/iappender.h \
    platform/viewer.h \
    diplom/startform.h \
    platform/utils.h \
    diplom/servicescontext.h \
    diplom/resultfrom.h \
    diplom/filters/abstractfilter.h \
    diplom/filters/blackwhitefilte.h \
    diplom/filters/filterutils.h \
    diplom/filters/mysuperfilter.h \
    diplom/filters/coords.h \
    diplom/acinusrecognizer.h \
    platform/logger/haslogger.h \
    diplom/filters/binarizer.h \
    diplom/recognizers/recongnizerschain.h \
    diplom/recognizers/acinus.h \
    diplom/recognizers/abstractrecognizer.h \
    diplom/recognizers/sizerognizer.h \
    diplom/constants.h \
    diplom/recognizers/formrecognizer.h \
    diplom/database/da/idataaccess.h \
    diplom/database/vo/imagedbmodel.h \
    diplom/database/da/csvdataaccess.h \
    diplom/database/da/sqllitedataaccess.h \
    platform/property.h \
    diplom/database/da/dataaccessfactory.h \
    diplom/recognizers/attributerecognizser.h \
    diplom/recognizers/gistogrammrecognizer.h \
    diplom/form.h

FORMS    += mainwindow.ui \
    diplom/startform.ui \
    diplom/resultfrom.ui \
    diplom/form.ui
