#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <QtQml>

#include <QtQuick/QQuickView>

#include "Model/dataentrymodel.h"
#include "View/chart.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<DataEntryModel>("Client.Components", 1,0, "DataEntryModel");
    qmlRegisterType<QGyroFrame>("Client.Components", 1,0, "QGyroFrame");
    qmlRegisterType<Chart>("Client.Components", 1,0, "Chart");

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

    return app.exec();
}
