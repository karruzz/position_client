#ifndef DATAENTRYMODEL_H
#define DATAENTRYMODEL_H

#include <QtCore>
#include <QtGui>

#include "qgyroframe.h"
#include "Channel/TFileChannel.h"
#include "Data/Devices/GyroFrame.h"

class DataEntryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QGyroFrame *frame READ frame NOTIFY seeked)
    Q_PROPERTY( quint64 count READ count NOTIFY opened)

public:
    explicit DataEntryModel(QObject *parent = 0);
    ~DataEntryModel();

    QGyroFrame *frame() const;
    quint64 count() const;

signals:
    void opened();
    void seeked();
    void pointsUpdated(const QVector<QPointF> &points);

public slots:
    void open(const QString &path);
    void seek(quint64 index);

private:
    QGyroFrame *_frame;
    TFileChannel<GyroFrame> *_channel;
    quint64 _count;
};

#endif // DATAENTRYMODEL_H

