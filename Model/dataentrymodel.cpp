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
    if (_isChannelOpened) _channel->Close();
}

void DataEntryModel::open(const QString &path)
{
    _isChannelOpened = _channel->Open(path);
    if (!_isChannelOpened) return;

    _count = _channel->Count();
    emit opened();
}

void DataEntryModel::seek(quint64 index)
{
    if (_isChannelOpened)
        _frame->frame = _channel->Read(index);
}

