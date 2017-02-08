TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    core/dispatcher.cpp \
    core/math.cpp \
    channel/tfile_channel.cpp \
    data/devices/qgyro_frame.cpp \
    subsystems/gyro/gyro_chart_model.cpp \
    subsystems/gyro/gyro_3d_model.cpp \
    ui/controls/3d/projection.cpp \
    ui/controls/3d/renderer.cpp \
    ui/controls/3d/model/gl_model.cpp \
    ui/controls/chart/chart.cpp \
    ui/controls/chart/line_node.cpp \
    ui/controls/chart/grid_node.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    core/dispatcher.h \
    core/math.h \
    channel/tfile_channel.h \
    channel/ichannel.h \
    data/devices/gyro_frame.h \
    data/devices/qgyro_frame.h \
    data/iframe.h \
    ui/controls/3d/projection.h \
    ui/controls/3d/renderer.h \
    ui/controls/3d/model/gl_vertex.h \
    ui/controls/3d/model/gl_model.h \
    ui/controls/chart/chart.h \
    ui/controls/chart/line_node.h \
    ui/controls/chart/grid_node.h \
    subsystems/gyro/gyro_3d_model.h \
    subsystems/gyro/gyro_chart_model.h

DISTFILES +=

