QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        coman_exec.cpp \
        coman_fdisk.cpp \
        coman_mkdisk.cpp \
        coman_mkfs.cpp \
        coman_mount.cpp \
        coman_rep.cpp \
        coman_rmdisk.cpp \
        coman_unmount.cpp \
        estructuras.cpp \
        graficar.cpp \
        list_particiones.cpp \
        main.cpp \
        n_particiones.cpp \
        nodo_arbol.cpp \
        parser.cpp \
        scanner.cpp \
        valores.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lexico.l \
    parser.y

HEADERS += \
    coman_exec.h \
    coman_fdisk.h \
    coman_mkdisk.h \
    coman_mkfs.h \
    coman_mount.h \
    coman_rep.h \
    coman_rmdisk.h \
    coman_unmount.h \
    estructuras.h \
    graficar.h \
    list_particiones.h \
    n_particiones.h \
    nodo_arbol.h \
    parser.h \
    scanner.h \
    valores.h
