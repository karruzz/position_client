#ifndef IFRAME_H
#define IFRAME_H

#include <QtGlobal>

class IFrame
{
    public:
        quint64 Counter;

        virtual int Size() = 0;
};

#endif // IFRAME_H

