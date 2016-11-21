#include "qgyroframe.h"

QGyroFrame::QGyroFrame(QObject *parent)
    : QObject(parent)
{
    data.Acs.X = data.Acs.Y = data.Acs.Z = 0;
}

double QGyroFrame::getRoll()
{
    return data.Acs.X;
}

double QGyroFrame::getPitch()
{
    return data.Acs.Y;
}

double QGyroFrame::getYaw()
{
    return data.Acs.Z;
}
