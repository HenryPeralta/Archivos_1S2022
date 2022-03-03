QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        coman_mkdisk.cpp \
        coman_rmdisk.cpp \
        estructuras.cpp \
        graficar.cpp \
        main.cpp \
        nodo_arbol.cpp \
        parser.cpp \
        scanner.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lexico.l \
    parser.y

HEADERS += \
    coman_mkdisk.h \
    coman_rmdisk.h \
    estructuras.h \
    graficar.h \
    nodo_arbol.h \
    parser.h \
    scanner.h