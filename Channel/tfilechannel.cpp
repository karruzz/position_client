#include "TFileChannel.h"
#include <QtMath>

template class TFileChannel<GyroFrame>;

template <class T>
TFileChannel<T>::TFileChannel() : _filePtr(NULL), _streamPtr(NULL)
{ }

template <class T>
TFileChannel<T>::~TFileChannel()
{
    Close();
}

template <class T>
bool TFileChannel<T>::Open(const QString &path)
{
    if (_filePtr) Close();

    _filePtr = new QFile(path);
    if (!_filePtr->exists()) return false;
    if (!_filePtr->open(QIODevice::ReadOnly)) return false;
    _framesCount = (_filePtr->size()) / FrameSize;
    _streamPtr = new QDataStream(_filePtr);
    _streamPtr->setByteOrder(QDataStream::LittleEndian);
    return true;
}

template <class T>
void TFileChannel<T>::Close()
{
    if (!_filePtr) return;

    if (_filePtr->isOpen()) _filePtr->close();
    delete _filePtr;
    _filePtr = NULL;

    delete _streamPtr;
    _streamPtr = NULL;
}

template <class T>
quint64 TFileChannel<T>::Counter(quint64 index)
{
    return Read(index).Counter;
}

template <class T>
quint64 TFileChannel<T>::Index(quint64 counter)
{
    if (counter <= StartCounter()) return 0;
    if (counter >= EndCounter()) return _framesCount - 1;

    quint64 left = 0;
    quint64 right = _framesCount - 1;
    quint64 center = (right + left) / 2;
    quint64 lastCenter = 0;

    while (qAbs(center - lastCenter)>1)
    {
        T frame = Read(center);
        if (counter > frame.Counter) left = center;
        else if (counter < frame.Counter) right = center;
        else return center;

        lastCenter = center;
        center = (right + left) / 2;
    }

    return qMin(lastCenter, center);
}

template <class T>
quint64 TFileChannel<T>::StartCounter()
{
    return Counter(0);
}

template <class T>
quint64 TFileChannel<T>::EndCounter()
{
    return Counter(_framesCount - 1);
}

template <class T>
quint64 TFileChannel<T>::Count()
{
    _framesCount = (_filePtr->size()) / FrameSize;
    return _framesCount;
}

template <class T>
T TFileChannel<T>::Read(quint64 index)
{
    auto position = index * FrameSize;
    _filePtr->seek(position);

    T result;
    *_streamPtr >> result;

    return result;
}

template <class T>
QVector<T> TFileChannel<T>::Read(quint64 index, int count)
{
    auto position = index * FrameSize;
    _filePtr->seek(position);

    QVector<T> result;
    result.reserve(count);
    int i = 0;
    while (i++ < count)
    {
        T packet;
        *_streamPtr >> packet;
        result.append(packet);
    }

    return result;
}
