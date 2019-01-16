/*
 * main.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtGui>
#include <QtQml>

#include <QtQuick/QQuickView>

#include "core/dispatcher.h"
#include "ui/controls/chart/chart.h"
#include "ui/controls/3d/projection.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<Dispatcher>("Client.Components", 1, 0, "Dispatcher");
	qmlRegisterType<Chart>("Client.Components", 1, 0, "Chart");
	qmlRegisterType<Projection>("Client.Components", 1, 0, "Projection");
	qmlRegisterType<QGyroFrame>("Client.Components", 1, 0, "QGyroFrame");

	QQuickView viewer;
	viewer.setTitle(QStringLiteral("Gyro client"));

	Dispatcher model(&viewer);

	viewer.rootContext()->setContextProperty("dispatcher", &model);
	viewer.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	QObject::connect((QObject*)viewer.engine(), SIGNAL(quit()), &app, SLOT(quit()));
	viewer.showFullScreen();

	return app.exec();
}
