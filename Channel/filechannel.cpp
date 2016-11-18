#include "filechannel.h"

bool FileChannel::Open(const QString &path)
{
    _file = new QFile(path);
    if (!_file->exists()) return false;
    if (!_file->open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    _fileSizeInFrames = (_file->size()) / FrameSize;
    return true;
}

void FileChannel::Close()
{
    if (_file != NULL) _file->close();
    delete _file;
}

quint64 FileChannel::Count()
{
    return _fileSizeInFrames;
}

GyroFrame FileChannel::Read(quint64 index)
{
    auto position = index * FrameSize;
    if (position != _filePosition) {
        _file->seek(position);
        _filePosition = position;
    }

    GyroFrame result;
    result.Deserialize(_file->read(FrameSize));
    _filePosition += FrameSize;

    return result;
}
