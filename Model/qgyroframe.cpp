#include "qgyroframe.h"

QGyroFrame::QGyroFrame(QObject *parent)
    : QObject(parent)
{
}

double QGyroFrame::getRoll()
{
    return frame.Angle.X;
}

double QGyroFrame::getPitch()
{
    return frame.Angle.Y;
}

double QGyroFrame::getYaw()
{
    return frame.Angle.Z;
}
