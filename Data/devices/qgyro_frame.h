/*
 * qgyro_frame.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef QGYROFRAME
#define QGYROFRAME

#include <QtCore>

#include "data/devices/gyro_frame.h"

class QGyroFrame : public QObject
{
	Q_OBJECT

	Q_PROPERTY( quint64 Counter  READ Counter NOTIFY changed)
	Q_PROPERTY( double Roll  READ Roll NOTIFY changed)
	Q_PROPERTY( double Pitch READ Pitch NOTIFY changed)
	Q_PROPERTY( double Yaw   READ Yaw NOTIFY changed)

	Q_PROPERTY( double wx  READ wx NOTIFY changed)
	Q_PROPERTY( double wy  READ wy NOTIFY changed)
	Q_PROPERTY( double wz  READ wz NOTIFY changed)

	Q_PROPERTY( double ax  READ ax NOTIFY changed)
	Q_PROPERTY( double ay  READ ay NOTIFY changed)
	Q_PROPERTY( double az  READ az NOTIFY changed)

public:
	explicit QGyroFrame(QObject *parent = 0);

	quint64 Counter() const { return data.Counter; }
	double Roll() const { return data.Angle.x(); }
	double Pitch() const { return data.Angle.y(); }
	double Yaw() const { return data.Angle.z(); }

	double wx() const { return data.Omega.x(); }
	double wy() const { return data.Omega.y(); }
	double wz() const { return data.Omega.z(); }

	double ax() const { return data.Acs.x(); }
	double ay() const { return data.Acs.y(); }
	double az() const { return data.Acs.z(); }

	GyroFrame data;

signals:
	void changed();
};

#endif // QGYROFRAME

