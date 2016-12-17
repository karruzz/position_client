#ifndef TFILECHANNEL
#define TFILECHANNEL

#include <QDataStream>
#include <QFile>
#include <QUrl>

#include "IChannel.h"
#include "Data/Devices/GyroFrame.h"

template <class T>
class TFileChannel : public IChannel<T>
{
    public:
        explicit TFileChannel();
        ~TFileChannel();

        bool Open(const QString &path);
        void Close();

        quint64 StartCounter() override final;
        quint64 EndCounter() override final;

        quint64 Counter(quint64 index) override final;
        quint64 Index(quint64 counter) override final;

        T Read(quint64 index) override final;
        QVector<T> Read(quint64 index, int count) override final;
        quint64 Count() override final;

    private:
        QFile *_filePtr;
        QDataStream *_streamPtr;

        const int FrameSize = 80;
        quint64 _filePosition = 0;
        quint64 _framesCount = 0;
};

#endif // TFILECHANNEL

