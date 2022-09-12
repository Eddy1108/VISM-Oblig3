QT          += core gui widgets opengl
QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++11
INCLUDEPATH += .\Matrix4x4\
TARGET      = Rulleball

FORMS += \
    mainwindow.ui

HEADERS += \
    Matrix4x4/matrix4x4.h \
    Matrix4x4/vector3d.h \
    Matrix4x4/vertex.h \
    Tri.h \
    mainwindow.h \
    octahedronball.h \
    renderwindow.h \
    rollingball.h \
    shader.h \
    trianglesurface.h \
    visualobject.h \
    xyz.h

SOURCES += \
    Matrix4x4/matrix4x4.cpp \
    Matrix4x4/vertex.cpp \
    Tri.cpp \
    main.cpp \
    mainwindow.cpp \
    octahedronball.cpp \
    renderwindow.cpp \
    rollingball.cpp \
    shader.cpp \
    trianglesurface.cpp \
    visualobject.cpp \
    xyz.cpp

DISTFILES += \
    dagfragment.frag \
    dagvertex.vert
