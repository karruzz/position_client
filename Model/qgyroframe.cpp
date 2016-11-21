#include "qgyroframe.h"

QGyroFrame::QGyroFrame(QObject *parent)
    : QObject(parent)
{
    data.Angle.X = data.Angle.Y = data.Angle.Z = 0;
}
