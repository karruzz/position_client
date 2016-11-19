TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    Model/dataentrymodel.cpp \
    Channel/filechannel.cpp \
    Model/renderthread.cpp \
    Model/qgyroframe.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Model/dataentrymodel.h \
    Data/gyroframe.h \
    Math/point3d.h \
    Channel/ichannel.h \
    Channel/filechannel.h \
    Model/renderthread.h \
    Model/qgyroframe.h

DISTFILES +=

