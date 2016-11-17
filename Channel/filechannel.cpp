#include "filechannel.h"

bool FileChannel::Open(const QString &path)
{
    _file = new QFile(path);
    auto result = _file->open(QIODevice::ReadOnly | QIODevice::Text);
    return result;
}

void FileChannel::Close()
{
    if (_file != NULL) _file->close();
    delete _file;
}

quint64 FileChannel::Count()
{
    return (_file->size()) / FrameSize;
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
