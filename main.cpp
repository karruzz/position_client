#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui>
#include <QtQml>

#include <QtQuick/QQuickView>

#include "Model/dataentrymodel.h"
#include "Model/roleentrymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<DataEntryModel>("org.example", 1, 0, "DataEntryModel");
//    qmlRegisterType<RoleEntryModel>("org.example", 1, 0, "RoleEntryModel");

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickView *viewer = new QQuickView;

//    QString extraImportPath(QStringLiteral("%1/../../../%2"));
//    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
//                                      QString::fromLatin1("qml")));
//    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer->setTitle(QStringLiteral("QML Oscilloscope"));

    RoleEntryModel model(viewer);

    viewer->rootContext()->setContextProperty("model1", &model);
    viewer->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    //viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer->show();

    return app.exec();
}

