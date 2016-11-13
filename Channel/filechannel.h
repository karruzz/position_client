#ifndef FILECHANNEL_H
#define FILECHANNEL_H

#include <QFile>
#include "ichannel.h"
#include "Data/gyroframe.h"

class FileChannel : public IChannel
{
    public:
        bool Open(const QString &path);
        void Close();

        GyroFrame Read(quint64 index);
        quint64 Count();
    private:
        QFile *_file;
        const int FrameSize = sizeof(GyroFrame);
};

#endif // FILECHANNEL_H

