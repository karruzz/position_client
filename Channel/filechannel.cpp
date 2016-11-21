#include "filechannel.h"

FileChannel::FileChannel() : _filePtr(NULL), _streamPtr(NULL)
{ }

FileChannel::~FileChannel()
{
    Close();
}

bool FileChannel::Open(const QString &path)
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

void FileChannel::Close()
{    
    if (!_filePtr) return;

    if (_filePtr->isOpen()) _filePtr->close();
    delete _filePtr;
    _filePtr = NULL;
}

quint64 FileChannel::Count()
{
    return _fileSizeInFrames;
}

GyroFrame FileChannel::Read(quint64 index)
{
    auto position = index * FrameSize;
    if (position != _filePosition) {
        _filePtr->seek(position);
        _filePosition = position;
    }

    GyroFrame result;
    *_streamPtr >> result;
    _filePosition += FrameSize;

    return result;
}
