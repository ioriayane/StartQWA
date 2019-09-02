#include "fakesns4q.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#ifdef BUILD_FOR_WASM
#include <emscripten.h>
#endif

FakeSns4Q::FakeSns4Q(QObject *parent) : QObject(parent)
{
  //ユーザー情報を取得できるまでのダミー画像
  setUserIcon("noimage.jpg");
  //リクエストに対するレスポンスを受け取るためのシグナル・スロットを接続
  connect(&m_networkManager, &QNetworkAccessManager::finished
          , this, &FakeSns4Q::networkMangerfinished);
}

QString FakeSns4Q::userId() const
{
  return m_userId;
}

QString FakeSns4Q::userName() const
{
  return m_userName;
}

QString FakeSns4Q::userIcon() const
{
  return m_userIcon;
}

void FakeSns4Q::setUserId(QString userId)
{
  if (m_userId == userId)
    return;

  m_userId = userId;
  emit userIdChanged(m_userId);

  //ユーザーIDが変更されたら要求
  QUrl api = "https://qwa.relog.tech/sns/user?id=" + userId;
  m_networkManager.get(QNetworkRequest(api));
}

void FakeSns4Q::setUserName(QString userName)
{
  if (m_userName == userName)
    return;

  m_userName = userName;
  emit userNameChanged(m_userName);
}

void FakeSns4Q::setUserIcon(QString userIcon)
{
  if (m_userIcon == userIcon)
    return;

  m_userIcon = userIcon;
  emit userIconChanged(m_userIcon);
}

void FakeSns4Q::networkMangerfinished(QNetworkReply *reply)
{
  //受け取った内容を処理
  QByteArray data = reply->readAll();
  qDebug() << reply->url().toString();
  qDebug() << reply->attribute(
                QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << QString(data);

#ifdef BUILD_FOR_WASM
  EM_ASM({
           var url = UTF8ToString($0);
           var code = $1;
           var json = UTF8ToString($2);
           var elm = document.createElement("p");
           elm.appendChild(document.createTextNode(url + "," + code));
           document.body.appendChild(elm);
           elm = document.createElement("p");
           elm.appendChild(document.createTextNode(json));
           document.body.appendChild(elm);
           debugger;
         }, reply->url().toString().toUtf8().constData()
         , reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()
         , data.constData()
         );
#endif

  //JSONをパースしてプロパティに設定
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject obj(doc.object());

  setUserName(obj["name"].toString());
  setUserIcon(obj["image"].toString());
}
