#include "tfilechannel.h"

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
    if (!_filePtr->open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    _fileSizeInFrames = (_filePtr->size()) / FrameSize;
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
}

template <class T>
quint64 TFileChannel<T>::Count()
{
    return _fileSizeInFrames;
}

template <class T>
T TFileChannel<T>::Read(quint64 index)
{
    auto position = index * FrameSize;
    if (position != _filePosition) {
        _filePtr->seek(position);
        _filePosition = position;
    }

    T result;
    *_streamPtr >> result;
    _filePosition += FrameSize;

    return result;
}
