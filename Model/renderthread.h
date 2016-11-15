#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

#include "Data/gyroframe.h"
#include "Channel/ichannel.h"
#include "Channel/filechannel.h"

class RenderThread : public QThread
{
    Q_OBJECT

public:
    explicit RenderThread(IChannel<GyroFrame> *channel, QObject *parent = 0);
    ~RenderThread();

    void Render(double index);

signals:
    void Rendered(const GyroFrame &frame);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    IChannel<GyroFrame> *_channel;
    QMutex mutex;
    QWaitCondition condition;
    double _index;
    bool restart;
    bool abort;
};

#endif // RENDERTHREAD_H

