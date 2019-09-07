#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <functional>

class Platform : public QObject
{
  Q_OBJECT

  //選択したファイルパスをプロパティとして公開
  Q_PROPERTY(QString selectedFile READ selectedFile NOTIFY selectedFileChanged)
  //テンポラリフォルダの場所をプロパティとして公開
  Q_PROPERTY(QString tempLocation READ tempLocation)

  QString m_selectedFile;

public:
  explicit Platform(QObject *parent = nullptr);

  //プロパティのゲッター
  QString selectedFile() const;
  QString tempLocation() const;
  //テキストファイルを保存するメソッド
  Q_INVOKABLE void saveText(const QString &path, const QString &text);

  Q_INVOKABLE void selectFile(const QString &filter);
  Q_INVOKABLE void saveFile(const QString &temp_file_path,
                            const QString &default_name);


signals:
  void selectedFileChanged(QString selectedFile);

public slots:
  void setSelectedFile(QString selectedFile);
};

#endif // PLATFORM_H
