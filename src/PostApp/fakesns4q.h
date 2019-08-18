#ifndef FAKESNS4Q_H
#define FAKESNS4Q_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class FakeSns4Q : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
  Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
  Q_PROPERTY(QString userIcon READ userIcon WRITE setUserIcon NOTIFY userIconChanged)

public:
  explicit FakeSns4Q(QObject *parent = nullptr);

  QString userId() const;
  QString userName() const;
  QString userIcon() const;

signals:
  void userIdChanged(QString userId);
  void userNameChanged(QString userName);
  void userIconChanged(QString userIcon);

public slots:
  void setUserId(QString userId);
  void setUserName(QString userName);
  void setUserIcon(QString userIcon);
  void networkMangerfinished(QNetworkReply *reply);

private:
  QString m_userId;
  QString m_userName;
  QString m_userIcon;

  QNetworkAccessManager m_networkManager;


};

#endif // FAKESNS4Q_H
