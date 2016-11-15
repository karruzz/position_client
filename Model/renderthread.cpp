#include "Model/renderthread.h"


RenderThread::RenderThread(IChannel<GyroFrame> *channel, QObject *parent)
    : QThread(parent), _channel(channel)
{
    restart = false;
    abort = false;
}

RenderThread::~RenderThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}


void RenderThread::Render(double index)
{
    QMutexLocker locker(&mutex);

    this->_index = index;

    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void RenderThread::run()
{
    forever {
        GyroFrame frame;
        frame = _channel->Read(_index);

        if (restart)
            continue;
        if (abort)
            return;

        emit Rendered(frame);

        mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock();
    }
}

