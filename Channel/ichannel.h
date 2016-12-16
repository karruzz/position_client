#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <QtGlobal>
#include <QVector>

template<class T>
class IChannel
{
    public:
        virtual ~IChannel() {}

        virtual quint64 Counter(quint64 index) = 0;
        virtual quint64 Index(quint64 counter) = 0;

        virtual T Read(quint64 index) = 0;
        virtual QVector<T> Read(quint64 index, int count) = 0;

        virtual quint64 Count() = 0;
};

#endif // ICHANNEL_H

