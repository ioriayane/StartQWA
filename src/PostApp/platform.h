#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString selectedFile READ selectedFile NOTIFY selectedFileChanged)
  QString m_selectedFile;

public:
  explicit Platform(QObject *parent = nullptr);

  Q_INVOKABLE void fileOpenDialog();
  Q_INVOKABLE void saveText(const QString &path, const QString &text);

  QString selectedFile() const;

signals:
  void selectedFileChanged(QString selectedFile);

public slots:
  void setSelectedFile(QString selectedFile);
};

#endif // PLATFORM_H
