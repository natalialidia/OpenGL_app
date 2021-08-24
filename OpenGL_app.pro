QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lopengl32
INCLUDEPATH += $$PWD/glm

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arvore.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    meucanvas.cpp \
    personagem.cpp

HEADERS += \
    arvore.h \
    camera.h \
    mainwindow.h \
    meucanvas.h \
    personagem.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
