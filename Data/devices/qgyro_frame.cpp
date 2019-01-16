/*
 * qgyro_frame.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "qgyro_frame.h"

QGyroFrame::QGyroFrame(QObject *parent)
    : QObject(parent)
{
	data.Angle = QVector3D(0,0,0);
}
