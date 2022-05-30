#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QmlFileItem.h>
#include <QmlFileItemModel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qmlRegisterUncreatableType<QmlFileItem>("QmlFileItem", 1,0, "QmlFileItem", "");
    qmlRegisterType<QmlFileItemModel>("QmlFileItem", 1,0, "QmlFileItemModel");
    
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/snitch/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
  
    
    return app.exec();
}
