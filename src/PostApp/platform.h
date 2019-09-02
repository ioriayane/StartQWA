#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

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

signals:
public slots:
};

#endif // PLATFORM_H
