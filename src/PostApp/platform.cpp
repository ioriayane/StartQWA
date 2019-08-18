#include "platform.h"

#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

Platform::Platform(QObject *parent) : QObject(parent)
{
}

QString Platform::saveText(const QString &file_name, const QString &text)
{
  //テンポラリフォルダにテキストファイルを保存
  QString path
      = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
      + "/" + file_name;
  QFile file(path);
  if(file.open(QFile::WriteOnly)){
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << text;
    file.close();
    return path;
  }else{
    return QString();
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
