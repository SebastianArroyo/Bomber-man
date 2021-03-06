QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bloquedestruible.cpp \
    bloqueindestruible.cpp \
    bomba.cpp \
    campo.cpp \
    enemigo.cpp \
    explosion.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    poderbomba.cpp \
    poderexplosion.cpp \
    podervida.cpp \
    puntaje.cpp

HEADERS += \
    bloque.h \
    bloquedestruible.h \
    bloqueindestruible.h \
    bomba.h \
    campo.h \
    configuracion.h \
    enemigo.h \
    explosion.h \
    jugador.h \
    mainwindow.h \
    menu.h \
    poder.h \
    poderbomba.h \
    poderexplosion.h \
    podervida.h \
    puntaje.h

FORMS += \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
