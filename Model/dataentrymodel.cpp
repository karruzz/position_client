#include "dataentrymodel.h"

DataEntryModel::DataEntryModel(QObject *parent)
    : QObject(parent), _frame(new QGyroFrame(this)),
      _channel(new TFileChannel<GyroFrame>()),
      _count(0)
{
}

QGyroFrame *DataEntryModel::frame() const
{
    return _frame;
}

quint64 DataEntryModel::count() const
{
    return _count;
}

DataEntryModel::~DataEntryModel()
{
    delete _channel;
}

void DataEntryModel::open(const QString &path)
{
    if (!_channel->Open(path)) return;
    _count = _channel->Count();
    emit opened();
}

void DataEntryModel::seek(quint64 index)
{
    _frame->data = _channel->Read(index);
    emit _frame->changed();
    emit seeked();

    QVector<QPointF> points;
    points.clear();
    points.resize(800);
    for (int i = 0; i<800; i++){
        auto frame = _channel->Read(index + i);
        points[i] = QPointF(i, frame.Omega.X * 100 + 200) ;
    }
    emit pointsUpdated(points);
}

