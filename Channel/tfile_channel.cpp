/*
 * tfile_channel.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "tfile_channel.h"
#include <QtMath>

template class TFileChannel<GyroFrame>;

template <class T>
bool TFileChannel<T>::Open(const QString &path)
{
	_qfile.reset(new QFile(path));
	if (!_qfile->open(QIODevice::ReadOnly))
		return false;

	_frames_count = (_qfile->size()) / T::FrameSize;
	_qstream.reset(new QDataStream(_qfile.data()));
	_qstream->setByteOrder(QDataStream::LittleEndian);
	return true;
}

template <class T>
void TFileChannel<T>::Close()
{
	_qfile.reset();
	_qstream.reset();
}

template <class T>
quint64 TFileChannel<T>::Counter(quint64 index)
{
	return Read(index).Counter;
}

template <class T>
quint64 TFileChannel<T>::Index(quint64 counter)
{
	quint64 start = 0;
	quint64 end = _frames_count - 1;

	if (counter <= StartCounter()) return start;
	if (counter >= EndCounter()) return end;

	quint64 center = 0, last_center = 0;
	do {
		last_center = center;
		center = (start + end) / 2;

		T frame = Read(center);
		if (counter > frame.Counter)
			start = center;
		else if (counter < frame.Counter)
			end = center;
		else
			return center;

	} while (qAbs(center - last_center) > 1);

	return qMin(last_center, center);
}

template <class T>
quint64 TFileChannel<T>::StartCounter()
{
	return Counter(0);
}

template <class T>
quint64 TFileChannel<T>::EndCounter()
{
	return Counter(_frames_count - 1);
}

template <class T>
quint64 TFileChannel<T>::Count()
{
	_frames_count = (_qfile->size()) / T::FrameSize;
	return _frames_count;
}

// todo: read next
template <class T>
T TFileChannel<T>::Read(quint64 index)
{
	auto position = index * T::FrameSize;
	_qfile->seek(position);

	T result;
	*_qstream >> result;

	return result;
}

template <class T>
QVector<T> TFileChannel<T>::Read(quint64 index, int count)
{
	auto position = index * T::FrameSize;
	_qfile->seek(position);

	QVector<T> result;
	result.reserve(count);
	int i = 0;
	while (i++ < count) {
		T packet;
		*_qstream >> packet;
		result.append(packet);
	}

	return result;
}
