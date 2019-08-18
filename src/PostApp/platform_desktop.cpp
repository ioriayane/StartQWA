#include "platform.h"

#include <QFileDialog>
#include <QStandardPaths>

void Platform::selectFile(const QString &filter)
{
  //ファイルオープンダイアログを開く
  QString file_path = QFileDialog::getOpenFileName(
        nullptr,
        QStringLiteral("Open"),
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        QString("Files (%1)").arg(filter));
  //選択していたらファイルのプロパティへ設定（QMLへ通知される）
  if(!file_path.isEmpty()){
    setSelectedFile(file_path);
  }
}

void Platform::saveFile(const QString &temp_file_path
                        , const QString &default_name)
{
  //ファイル保存ダイアログを開く
  QString file_path = QFileDialog::getSaveFileName(
        nullptr,
        QStringLiteral("Save"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                         + "/" + default_name,
        QStringLiteral("All Files (*.*)"));
  //コピー機能は上書きできないので予め消す
  if(QFile::exists(file_path)){
    QFile::remove(file_path);
  }
  //指定の場所に移動
  QFile::rename(temp_file_path, file_path);
}
