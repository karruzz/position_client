#ifndef TFILECHANNEL
#define TFILECHANNEL

#include <QDataStream>
#include <QFile>
#include <QUrl>

#include "ichannel.h"
#include "Data/Devices/gyroframe.h"

template <class T>
class TFileChannel : public IChannel<T>
{
    public:
        explicit TFileChannel();
        ~TFileChannel();

        bool Open(const QString &path);
        void Close();

        T Read(quint64 index);
        quint64 Count();

    private:
        QFile *_filePtr;
        QDataStream *_streamPtr;

        const int FrameSize = 80;
        quint64 _filePosition = 0;
        quint64 _fileSizeInFrames = 0;
};

#endif // TFILECHANNEL

