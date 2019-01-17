/*
 * gyro_chart_model.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "gyro_chart_model.h"

GyroChartModel::GyroChartModel(QQuickView *parent, IChannel<GyroFrame>& channel)
	: QObject(parent), _channel(channel)
{
	auto root = parent->rootObject();
	auto viewX = root->findChild<Chart*>("gyroChartAngleX");
	QObject::connect(this, &GyroChartModel::angle_x_updated, viewX, &Chart::append_points);

	auto viewY = root->findChild<Chart*>("gyroChartAngleY");
	QObject::connect(this, &GyroChartModel::angle_y_updated, viewY, &Chart::append_points);

	auto viewZ = root->findChild<Chart*>("gyroChartAngleZ");
	QObject::connect(this, &GyroChartModel::angle_z_updated, viewZ, &Chart::append_points);
}

void GyroChartModel::seek(quint64 counter)
{
	qint64 minCounter = counter - Scale_ns;
	qint64 maxCounter = counter + Scale_ns;

	auto index_left = minCounter < 0 ? 0 : _channel.Index(minCounter);
	auto index_right = _channel.Index(maxCounter);
	auto count = index_right - index_left;
	if (count == 0) return;

	auto frames = _channel.Read(index_left, count);

	QVector<QPointF> pointsX, pointsY, pointsZ;
	float minX = frames[0].Angle.x();
	float maxX = frames[0].Angle.x();
	float minY = frames[0].Angle.y();
	float maxY = frames[0].Angle.y();
	float minZ = frames[0].Angle.z();
	float maxZ = frames[0].Angle.z();

	pointsX.reserve(count);
	pointsY.reserve(count);
	pointsZ.reserve(count);

	for (quint64 i = 0; i < count; i++)
	{
		pointsX.append( QPointF(frames[i].Counter, frames[i].Angle.x()) );
		maxX = qMax(maxX, frames[i].Angle.x());
		minX = qMin(minX, frames[i].Angle.x());

		pointsY.append( QPointF(frames[i].Counter, frames[i].Angle.y()) );
		maxY = qMax(maxY, frames[i].Angle.y());
		minY = qMin(minY, frames[i].Angle.y());

		pointsZ.append( QPointF(frames[i].Counter, frames[i].Angle.z()) );
		maxZ = qMax(maxZ, frames[i].Angle.z());
		minZ = qMin(minZ, frames[i].Angle.z());
	}

	emit angle_x_updated(pointsX, minX - 0.02, maxX + 0.02, minCounter, maxCounter);
	emit angle_y_updated(pointsY, minY - 0.02, maxY + 0.02, minCounter, maxCounter);
	emit angle_z_updated(pointsZ, minZ - 0.02, maxZ + 0.02, minCounter, maxCounter);
}


