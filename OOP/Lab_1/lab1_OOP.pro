QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle

CONFIG   += c++11

QMAKE_CXXFLAGS += -Wall -Werror

SOURCES += \
    main.cpp \
    circle.cpp \
    rectangle.cpp \
    triangle.cpp \
    shapeManager.cpp \
    inputHandler.cpp \
    outputHandler.cpp

HEADERS += \
    figure.h \
    circle.h \
    rectangle.h \
    triangle.h \
    shapeManager.h \
    inputHandler.h \
    outputHandler.h
