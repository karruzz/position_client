#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <QtGlobal>
#include "Data/gyroframe.h"

class IChannel
{
    public:
        virtual GyroFrame Read(quint64 index) = 0;
        virtual quint64 Count() = 0;
};

#endif // ICHANNEL_H

