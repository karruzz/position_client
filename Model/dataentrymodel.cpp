#include "dataentrymodel.h"

DataEntryModel::DataEntryModel(QObject *parent)
    : QObject(parent), _channel(new FileChannel), _frame(new QGyroFrame)
{
    _frame->frame.Angle.X = 10;
    _frame->frame.Angle.Y = 11;
    _frame->frame.Angle.Z = 12;
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
    if (_channel != NULL) _channel->Close();
}

void DataEntryModel::open(const QString &path)
{
    if (!_channel->Open(path)) return;

    _count = _channel->Count();
    emit opened();
}

void DataEntryModel::seek(quint64 index)
{
    if (_channel == NULL) return;
    _frame->frame = _channel->Read(index);
}

