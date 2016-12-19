#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <QtQml>

#include <QtQuick/QQuickView>

#include "Core/Dispatcher.h"
#include "UI/Controls/Chart/Chart.h"
#include "UI/Controls/3D/Projection.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Dispatcher>("Client.Components", 1, 0, "Dispatcher");
    qmlRegisterType<Chart>("Client.Components", 1, 0, "Chart");
    qmlRegisterType<Projection>("Client.Components", 1, 0, "Projection");
    qmlRegisterType<QGyroFrame>("Client.Components", 1,0, "QGyroFrame");

    QQuickView *viewer = new QQuickView;
    viewer->setTitle(QStringLiteral("Gyro client"));

    Dispatcher model(viewer);

    viewer->rootContext()->setContextProperty("dispatcher", &model);
    viewer->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    viewer->show();

    return app.exec();
}
