#include "platform.h"

#include <QFile>
#include <QUrl>
#include <QStandardPaths>
#include <QTextStream>

Platform::Platform(QObject *parent) : QObject(parent)
{
}

QString Platform::tempLocation() const
{
  //書き込み可能なテンポラリフォルダを取得
  return QStandardPaths::writableLocation(QStandardPaths::TempLocation);
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

void Platform::loadFile(const QString &filter)
{
  //プラットフォームごとの方法でデータを取得
  PlatformImpl::loadFile(filter,
                         [=](const char *data, size_t size, const char *file_name){
    //テンポラリフォルダに一時保存
    QString file_path = tempLocation() + "/" + QString(file_name);
    QFile file(file_path);
    if(file.open(QIODevice::WriteOnly)){
      file.write(data, size);
      file.close();

      emit fileLoaded(file_path);
    }
  });
}

void Platform::saveFile(const QString &temp_file_path, const QString &default_name)
{
  QFile file(temp_file_path);
  if(file.open(QIODevice::ReadOnly)){
    //プラットフォームごとの方法で保存
    PlatformImpl::saveFile(file.readAll(),
                           default_name.toUtf8().constData());
    //テンポラリのファイルを削除
    file.remove();
  }
}


