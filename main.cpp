#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <QtQml>

#include <QtQuick/QQuickView>
#include <QObject>

#include "Model/dataentrymodel.h"
#include "View/chart.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DataEntryModel>("GyroData", 1,0, "DataEntryModel");
    qmlRegisterType<QGyroFrame>("GyroData", 1,0, "QGyroFrame");
    qmlRegisterType<Chart>("GyroData", 1,0, "Chart");

    qRegisterMetaType<DataEntryModel*>("DataEntryModel");
    qRegisterMetaType<QGyroFrame*>("QGyroFrame");

    QQuickView *viewer = new QQuickView;
    viewer->setTitle(QStringLiteral("Gyro client"));

    DataEntryModel model(viewer);

    viewer->rootContext()->setContextProperty("dataEntry", &model);
    viewer->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    viewer->show();

    QQuickItem *root = viewer->rootObject();
    Chart *chart = root->findChild<Chart*>("chartObj");
    if (chart)
        QObject::connect(&model, &DataEntryModel::pointsUpdated, chart, &Chart::setPoints);
//    QObject::connect(&model, SIGNAL(seeked(int i)), chart, SLOT(seeked(int i)));

    return app.exec();
}
