TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    Model/dataentrymodel.cpp \
    Model/renderthread.cpp \
    Model/qgyroframe.cpp \
    Channel/tfilechannel.cpp \
    UI/Controls/3D/Projection.cpp \
    UI/Controls/Chart/Chart.cpp \
    Subsystems/Gyro/GyroChartModel.cpp \
    UI/Controls/3D/Renderer.cpp \
    Math/Quaternion.cpp \
    UI/Controls/3D/Model/GlModel.cpp \
    Subsystems/Gyro/Gyro3DModel.cpp \
    Core/Dispatcher.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Model/dataentrymodel.h \
    Model/renderthread.h \
    Model/qgyroframe.h \
    UI/Controls/3D/Projection.h \
    UI/Controls/Chart/Chart.h \
    Subsystems/Gyro/GyroChartModel.h \
    Math/Point3d.h \
    Data/IFrame.h \
    Data/Devices/GyroFrame.h \
    Core/Dispatcher.h \
    Channel/TFileChannel.h \
    Channel/IChannel.h \
    UI/Controls/3D/Renderer.h \
    Math/Quaternion.h \
    UI/Controls/3D/Model/GlVertex.h \
    UI/Controls/3D/Model/GlModel.h \
    Subsystems/Gyro/Gyro3DModel.h

DISTFILES +=

