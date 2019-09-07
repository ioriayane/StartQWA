#include "platform.h"

#include <QFileDialog>
#include <QStandardPaths>

void PlatformImpl::loadFile(const QString &filter,
                   std::function<void(const char *, size_t, const char *)> fileLoaded)
{
  //ファイルオープンダイアログを開く
  QString file_path = QFileDialog::getOpenFileName(
        nullptr,
        QStringLiteral("Open"),
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        QString("Files (%1)").arg(filter));

  QFile file(file_path);
  QFileInfo file_info(file_path);
  if(file.open(QIODevice::ReadOnly)){
    //選択されたファイルをQByteArrayで呼び出し元へ渡す
    fileLoaded(file.readAll().constData()
               , static_cast<size_t>(file.size())
               , file_info.fileName().toUtf8().constData());
    file.close();
  }
}

void PlatformImpl::saveFile(const QByteArray &data, const QString &default_name)
{
  //ファイル保存ダイアログを開く
  QString file_path = QFileDialog::getSaveFileName(
        nullptr,
        QStringLiteral("Save"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                         + "/" + default_name,
        QStringLiteral("All Files (*.*)"));

  QFile file(file_path);
  if(file.open(QIODevice::WriteOnly)){
    //QByteArrayで受け取ったデータを指定のファイルに書き込む
    file.write(data);
    file.close();
  }
}
