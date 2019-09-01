/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qhtml5file.h"

#include <QFileDialog>
#include <QStandardPaths>

void QHtml5File::load(const QString &accept, std::function<void(const QByteArray &, const QString &)> fileDataReady)
{
  //ファイルオープンダイアログを開く
  QString file_path = QFileDialog::getOpenFileName(nullptr,
                                QStringLiteral("Open"),
                                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                QString("Files (%1)").arg(accept));
  QFile file(file_path);
  QFileInfo file_info(file_path);
  if(file.open(QIODevice::ReadOnly)){
    //選択されたファイルをQByteArrayで呼び出し元へ渡す
    fileDataReady(file.readAll(), file_info.fileName());
    file.close();
  }
}

void QHtml5File::save(const QByteArray &contents, const QString &fileNameHint)
{
  //ファイル保存ダイアログを開く
  QString file_path = QFileDialog::getSaveFileName(nullptr,
                        QStringLiteral("Save"),
                        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + fileNameHint,
                        QStringLiteral("All Files (*.*)"));
  QFile file(file_path);
  if(file.open(QIODevice::WriteOnly)){
    //QByteArrayで受け取ったデータを指定のファイルに書き込む
    file.write(contents);
    file.close();
  }
}
