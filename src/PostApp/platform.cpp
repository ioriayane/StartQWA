#include "platform.h"

#include <QFileDialog>
#include <QDebug>

Platform::Platform(QObject *parent) : QObject(parent)
{

}

void Platform::fileOpenDialog()
{
  QFileDialog *dlg = new QFileDialog();

  connect(dlg, &QFileDialog::fileSelected,
        [=](const QString &file) {
    QUrl url(QUrl::fromLocalFile(file));
    qDebug() << file;
    qDebug() << url;
    setSelectedFile(url.toString());
  });
  dlg->open();
}

void Platform::saveText(const QString &path, const QString &text)
{
  QFile file(path);
  if(file.open(QFile::WriteOnly)){
    qDebug() << path;
    qDebug() << text;
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
