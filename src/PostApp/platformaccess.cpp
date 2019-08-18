#include "platformaccess.h"

#include <QFileDialog>
#include <QDebug>

PlatformAccess::PlatformAccess(QObject *parent) : QObject(parent)
{

}

void PlatformAccess::fileOpenDialog()
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

QString PlatformAccess::selectedFile() const
{
  return m_selectedFile;
}

void PlatformAccess::setSelectedFile(QString selectedFile)
{
  if (m_selectedFile == selectedFile)
    return;

  m_selectedFile = selectedFile;
  emit selectedFileChanged(m_selectedFile);
}
