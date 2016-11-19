#ifndef FILECHANNEL_H
#define FILECHANNEL_H

#include <QDataStream>
#include <QFile>
#include <QUrl>

#include "ichannel.h"
#include "Data/gyroframe.h"

class FileChannel : public IChannel<GyroFrame>
{
    public:
        bool Open(const QString &path);
        void Close();

        GyroFrame Read(quint64 index);
        quint64 Count();
    private:
        QFile *_filePtr;
        QDataStream *_streamPtr;

        const int FrameSize = 80;
        quint64 _filePosition = 0;
        quint64 _fileSizeInFrames = 0;
};

#endif // FILECHANNEL_H

