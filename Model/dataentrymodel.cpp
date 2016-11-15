#include "dataentrymodel.h"

DataEntryModel::DataEntryModel(QObject *parent)
    : QObject(parent), _channel(new FileChannel), m_frame(new QGyroFrame)
{
    m_frame->frame.Angle.X = 10;
}

QGyroFrame *DataEntryModel::getValue() const
{
    return m_frame;
}

DataEntryModel::~DataEntryModel()
{
    if (_channel != NULL) _channel->Close();
}

void DataEntryModel::Open(const QString &path)
{
    if (_channel->Open(path))
        Count = _channel->Count();
}

void DataEntryModel::Seek(quint64 index)
{
    if (_channel == NULL) return;
    m_frame->frame = _channel->Read(index);
}

