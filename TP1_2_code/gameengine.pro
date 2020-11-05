QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    espace.cpp \
    objet.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    espace.h \
    mainwidget.h \
    geometryengine.h \
    objet.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    sphere.off

# install
target.path = $$[YOUR_PATH]
INSTALLS += target
