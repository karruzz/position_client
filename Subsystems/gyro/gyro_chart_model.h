/*
 * gyro_chart_model.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef GYROCHARTMODEL_H
#define GYROCHARTMODEL_H

#include <QtCore>
#include <QtQuick>

#include "channel/ichannel.h"
#include "data/devices/gyro_frame.h"
#include "ui/controls/chart/chart.h"

class GyroChartModel : public QObject
{
Q_OBJECT

public:
	GyroChartModel(QQuickView *parent, IChannel<GyroFrame>& channel);

	void seek(quint64 index);

signals:
	void angle_x_updated(const QVector<QPointF> &points, float minY, float maxY, float minX, float maxX );
	void angle_y_updated(const QVector<QPointF> &points, float minY, float maxY, float minX, float maxX );
	void angle_z_updated(const QVector<QPointF> &points, float minY, float maxY, float minX, float maxX );

private:
	IChannel<GyroFrame>& _channel;

	const int Scale_ns = 2e+9;
};

#endif // GYROCHARTMODEL_H

