#ifndef DATAENTRYMODEL_H
#define DATAENTRYMODEL_H

#include <QtCore>
#include <QtGui>

#include "qgyroframe.h"
#include "Data/gyroframe.h"
#include "Channel/filechannel.h"

class DataEntryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QGyroFrame *Angle READ getValue)

public:
    explicit DataEntryModel(QObject *parent = 0);
    ~DataEntryModel();
    QGyroFrame *getValue() const;

signals:

public slots:
    void Open(const QString &path);
    void Seek(quint64 index);

private:
    FileChannel *_channel;
    int Count;
    QGyroFrame *_frame;

};

#endif // DATAENTRYMODEL_H

