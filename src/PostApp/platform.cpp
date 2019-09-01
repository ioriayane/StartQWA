#include "platform.h"

#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>

Platform::Platform(QObject *parent) : QObject(parent)
{
}

void Platform::saveText(const QUrl &url, const QString &text)
{
  QFile file(url.toLocalFile());
  if(file.open(QFile::WriteOnly)){
    qDebug() << url.toLocalFile();
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << text;
    file.close();
  }
}

QString Platform::tempLocation() const
{
  return QStandardPaths::writableLocation(QStandardPaths::TempLocation);
}

