QT       += core gui network location quickwidgets \
    quick sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\" # https://stackoverflow.com/a/60610273

SOURCES += \
    GenMap.cpp \
    db.cpp \
    filehandling.cpp \
    formular.cpp \
    geo.cpp \
    helper.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GenMap.h \
    daten_liste.h \
    db.h \
    filehandling.h \
    formular.h \
    geo.h \
    helper.h \
    mainwindow.h \
    query.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

DISTFILES += \
    DB_Pboerse_ERD_26072021.png \
    DB_Pboerse_SQL_Query.sql \
    DB_Pboerse_Schema.png \
    HereMap.txt \
    Tutorial.html \
    Version.txt \
    classes.qmodel \
    errorfiles/Hilfe_Text001.txt \
    errorfiles/error0001.html \
    errorfiles/error0002.html \
    pics/bluemarker.png \
    pics/left.png \
    pics/png-transparent-location-icon-computer-icredmarker.png \
    pics/redmarker.jpg \
    pics/redpin.jpg
