#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T19:12:16
#
#-------------------------------------------------

QT   += \
        core gui\
        sql\
        network\
        multimedia\
        core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pokemon
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myserver.cpp \
    login_widget.cpp \
    user_list.cpp \
    pokemon_widget.cpp \
    my_pokemon.cpp \
    myuser.cpp \
    backpack_widget.cpp \
    pokemon_center_widget.cpp \
    battle_ground.cpp \
    battle_field.cpp \
    music_thread.cpp

HEADERS += \
        mainwindow.h \
    myserver.h \
    myserver.h \
    login_widget.h \
    user_list.h \
    pokemon_widget.h \
    my_pokemon.h \
    myuser.h \
    backpack_widget.h \
    pokemon_center_widget.h \
    battle_ground.h \
    battle_field.h \
    music_thread.h

FORMS += \
        mainwindow.ui \
    login_widget.ui \
    pokemon_widget.ui \
    pokemon_center_widget.ui \
    battle_ground.ui \
    battle_field.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source/pics.qrc \
    source/music.qrc

DISTFILES += \
    source/Dewgong.png \
    source/Fushigidane.png \
    source/Hitokage.png \
    source/Pikachu.png \
    source/Zenigame.png \
    source/Peroringa.png \
    source/神奇宝贝中心素材.png \
    source/道馆素材.jpg
