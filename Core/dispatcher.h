/*
 * dispatcher.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>
#include <QFileSystemWatcher>
#include <QScopedPointer>

#include "channel/tfile_channel.h"
#include "data/devices/gyro_frame.h"
#include "subsystems/gyro/gyro_chart_model.h"
#include "subsystems/gyro/gyro_3d_model.h"

class Dispatcher : public QObject
{
Q_OBJECT
	Q_PROPERTY( quint64 start_counter READ start_counter NOTIFY count_changed)
	Q_PROPERTY( quint64 end_counter READ end_counter NOTIFY count_changed)
	Q_PROPERTY( bool is_opened READ is_opened NOTIFY opened)

public:
	explicit Dispatcher(QQuickView *parent = 0)
		: QObject(parent), _parent(parent)
	{}

	quint64 start_counter() const { return is_opened() ? _channel->StartCounter() : 0; }
	quint64 end_counter() const { return is_opened() ? _channel->EndCounter() : 0; }
	bool is_opened() const { return !_channel.isNull(); }

signals:
	void opened();
	void count_changed();

public slots:
	void open(const QString &path);
	void seek(quint64 counter);

private:
	QQuickView *_parent;

	QScopedPointer<GyroChartModel> _gyroChart;
	QScopedPointer<Gyro3DModel> _gyro3D;
	QScopedPointer<TFileChannel<GyroFrame>> _channel;
};

#endif // DISPATCHER_H

