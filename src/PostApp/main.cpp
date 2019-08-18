#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "fakesns4q.h"
#include "platform.h"
#include "qhtml5file/qhtmlfileaccess.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);

  qmlRegisterType<FakeSns4Q>("tech.relog.plugin.fakesns4q"
                             , 1, 0, "FakeSns4Q");
  qmlRegisterType<Platform>("tech.relog.plugin.platform"
                                  , 1, 0, "Platform");


  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);


  QHtmlFileAccess *htmlFileAccess
      = new QHtmlFileAccess(static_cast<QApplication *>(QCoreApplication::instance()));
  engine.rootContext()->setContextProperty("htmlFileAccess", htmlFileAccess);

  engine.load(url);

  return app.exec();
}
