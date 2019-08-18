#ifndef PLATFORMACCESS_H
#define PLATFORMACCESS_H

#include <QObject>

class PlatformAccess : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString selectedFile READ selectedFile NOTIFY selectedFileChanged)
  QString m_selectedFile;

public:
  explicit PlatformAccess(QObject *parent = nullptr);

  Q_INVOKABLE void fileOpenDialog();
  QString selectedFile() const;

signals:
  void selectedFileChanged(QString selectedFile);

public slots:
  void setSelectedFile(QString selectedFile);
};

#endif // PLATFORMACCESS_H
