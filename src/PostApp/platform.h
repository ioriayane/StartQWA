#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <functional>

namespace PlatformImpl {
  //プラットフォームごとの処理を書くための関数の宣言
  void loadFile(const QString &filter,
           std::function<void(const char *, size_t, const char *)> fileLoaded);
  void saveFile(const QByteArray &data, const QString &default_name);
}

class Platform : public QObject
{
  Q_OBJECT

  //テンポラリフォルダの場所をプロパティとして公開
  Q_PROPERTY(QString tempLocation READ tempLocation)

public:
  explicit Platform(QObject *parent = nullptr);

  //プロパティのゲッター
  QString tempLocation() const;
  //テキストファイルを保存するメソッド
  Q_INVOKABLE void saveText(const QString &path, const QString &text);

  Q_INVOKABLE void loadFile(const QString &filter);
  Q_INVOKABLE void saveFile(const QString &temp_file_path,
                            const QString &default_name);

signals:
  void fileLoaded(const QString &file_path);

public slots:
};

#endif // PLATFORM_H
