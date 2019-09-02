#include "platform.h"

#include <QFile>
#include <QUrl>
#include <QStandardPaths>
#include <QTextStream>

Platform::Platform(QObject *parent) : QObject(parent)
{
}

void Platform::saveText(const QString &path, const QString &text)
{
  //テキストファイルに保存
  QFile file(path);
  if(file.open(QFile::WriteOnly)){
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << text;
    file.close();
  }
}

QString Platform::tempLocation() const
{
  //書き込み可能なテンポラリフォルダを取得
  return QStandardPaths::writableLocation(QStandardPaths::TempLocation);
}

