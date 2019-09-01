#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString tempLocation READ tempLocation)

public:
  explicit Platform(QObject *parent = nullptr);

  QString tempLocation() const;

  Q_INVOKABLE void saveText(const QUrl &url, const QString &text);

signals:

public slots:

};

#endif // PLATFORM_H
