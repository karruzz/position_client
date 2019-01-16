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
	QObject::connect(this, &GyroChartModel::AngleXUpdated, viewX, &Chart::appendPoints);

	auto viewY = root->findChild<Chart*>("gyroChartAngleY");
	QObject::connect(this, &GyroChartModel::AngleYUpdated, viewY, &Chart::appendPoints);

	auto viewZ = root->findChild<Chart*>("gyroChartAngleZ");
	QObject::connect(this, &GyroChartModel::AngleZUpdated, viewZ, &Chart::appendPoints);
}

void GyroChartModel::seek(quint64 counter)
{
	qint64 minCounter = counter - Scale_ns;
	qint64 maxCounter = counter + Scale_ns;

	auto indexLeft = minCounter < 0 ? 0 : _channel.Index(minCounter);
	auto indexRight = _channel.Index(maxCounter);
	auto count = indexRight - indexLeft;

	auto frames = _channel.Read(indexLeft, count);

	QVector<QPointF> pointsX, pointsY, pointsZ;
	float minX = 0, maxX = 0, minY = 0, maxY = 0, minZ = 0, maxZ = 0;

	pointsX.reserve(count);
	pointsY.reserve(count);
	pointsZ.reserve(count);
	if (count > 0){
		minX = maxX = frames[0].Angle.x();
		minY = maxY = frames[0].Angle.y();
		minZ = maxZ = frames[0].Angle.z();
	}

	for (quint64 i = 0; i < count; i++)
	{
		pointsX.append( QPointF(frames[i].Counter, frames[i].Angle.x()) );
		if (frames[i].Angle.x() > maxX) maxX = frames[i].Angle.x();
		if (frames[i].Angle.x() < minX) minX = frames[i].Angle.x();

		pointsY.append( QPointF(frames[i].Counter, frames[i].Angle.y()) );
		if (frames[i].Angle.y() > maxY) maxY = frames[i].Angle.y();
		if (frames[i].Angle.y() < minY) minY = frames[i].Angle.y();

		pointsZ.append( QPointF(frames[i].Counter, frames[i].Angle.z()) );
		if (frames[i].Angle.z() > maxZ) maxZ = frames[i].Angle.z();
		if (frames[i].Angle.z() < minZ) minZ = frames[i].Angle.z();
	}

	emit AngleXUpdated(pointsX, minX - 0.02, maxX + 0.02, minCounter, maxCounter);
	emit AngleYUpdated(pointsY, minY - 0.02, maxY + 0.02, minCounter, maxCounter);
	emit AngleZUpdated(pointsZ, minZ - 0.02, maxZ + 0.02, minCounter, maxCounter);
}


