/*
 * gyro_3d_model.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef GYRO3DMODEL_H
#define GYRO3DMODEL_H

#include <QtCore>
#include <QtQuick>

#include "channel/ichannel.h"
#include "data/devices/gyro_frame.h"
#include "ui/controls/3d/projection.h"

class Gyro3DModel : public QObject
{
Q_OBJECT

public:
	Gyro3DModel(QQuickView *parent, IChannel<GyroFrame>& channel);

	void seek(quint64 index);

signals:
	void PointUpdated(const GyroFrame &points);

private:
	// todo: to const reference
	IChannel<GyroFrame>& _channel;
	quint64 _count;
};

#endif // GYRO3DMODEL_H

