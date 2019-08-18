#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString type READ type)

public:
  explicit Platform(QObject *parent = nullptr);

  QString type() const;

  Q_INVOKABLE void saveText(const QUrl &url, const QString &text);

signals:

public slots:

private:
  QString m_type;

};

#endif // PLATFORM_H
