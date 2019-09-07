#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
  Q_OBJECT

  //選択したファイルパスをプロパティとして公開
  Q_PROPERTY(QString selectedFile
             READ selectedFile NOTIFY selectedFileChanged)

  QString m_selectedFile;

public:
  explicit Platform(QObject *parent = nullptr);

  //プロパティのゲッター
  QString selectedFile() const;
  //テキストファイルを保存するメソッド
  Q_INVOKABLE QString saveText(const QString &file_name, const QString &text);
  //ファイル選択・保存のメソッド
  Q_INVOKABLE void selectFile(const QString &filter);
  Q_INVOKABLE void saveFile(const QString &temp_file_path,
                            const QString &default_name);

signals:
  //ファイルが選択されたことを通知するシグナル
  void selectedFileChanged(QString selectedFile);

public slots:
  //プロパティのセッター
  void setSelectedFile(QString selectedFile);
};

#endif // PLATFORM_H
