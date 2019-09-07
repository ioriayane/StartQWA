#include "platform.h"

#include <QStandardPaths>
#include <QFile>
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

QString Platform::selectedFile() const
{
  return m_selectedFile;
}

void Platform::setSelectedFile(QString selectedFile)
{
  if (m_selectedFile == selectedFile)
    return;

  m_selectedFile = selectedFile;
  emit selectedFileChanged(m_selectedFile);
}
