#ifndef IFRAME_H
#define IFRAME_H

#include <QByteArray>

class IFrame
{
    public:
        virtual void Deserialize(QByteArray bytes) = 0;
};

#endif // IFRAME_H

