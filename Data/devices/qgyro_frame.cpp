#include "qgyro_frame.h"

QGyroFrame::QGyroFrame(QObject *parent)
    : QObject(parent)
{
    data.Angle = QVector3D(0,0,0);
}