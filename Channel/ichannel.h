#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <QtGlobal>

template<class T>
class IChannel
{
    public:
        virtual ~IChannel() {}

        virtual T Read(quint64 index) = 0;
        virtual quint64 Count() = 0;
};

#endif // ICHANNEL_H

