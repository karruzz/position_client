#include "filechannel.h"

bool FileChannel::Open(const QString &path)
{
    _file = new QFile(path);
    return _file->open(QIODevice::ReadOnly | QIODevice::Text);
}

void FileChannel::Close()
{
    if (_file != NULL) _file->close();
    delete _file;
}

