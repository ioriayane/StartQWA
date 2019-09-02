import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import tech.relog.plugin.fakesns4q 1.0
import tech.relog.plugin.platform 1.0
import msorvig.plugin.htmlfileaccess 1.0

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Post App")

  //SNSから情報を取得する機能の配置
  FakeSns4Q {
    id: fakeSns4Q
    //取得するユーザーのIDをサンプルでは予め設定
    //本来であれば何らかのイベントで設定される値
    userId: "123456789"
  }
  //HTMLとやり取りしてファイルにアクセスする機能の配置
  HtmlFileAccess {
    id: htmlFileAccess
    onFsFileReady: {
      //HTML側のファイルを開く処理のコールバック
      var path = "file:///" + tmpFilePath
      image.source = path
    }
  }
  //その他機能の配置
  Platform {
    id: platform
  }
  //ブラウザ全体ではなく一部分を使用するイメージでQML的ダイアログ形式にする
  Dialog {
    visible: true
    modal: false
    margins: 10
    //サンプルではダイアログが閉じると困るので自動クローズしない
    closePolicy: Popup.NoAutoClose

    contentItem: ColumnLayout {
      anchors.margins: 10
      spacing: 5

      RowLayout {
        Layout.fillWidth: true
        //ユーザーアイコンの配置
        Image {
          id: userIconImage
          Layout.preferredHeight: 50
          Layout.preferredWidth: 50
          fillMode: Image.PreserveAspectFit
          //SNS機能のアイコンURLが入るプロパティにバインディング
          //情報が取得できれば自動で表示される
          source: fakeSns4Q.userIcon
        }

        Label {
          id: userNameLabel
          Layout.fillWidth: true
          //SNS機能のユーザー名が入るプロパティにバインディング
          //情報が取得できれば自動で表示される
          text: fakeSns4Q.userName
          font.pointSize: 12
        }

      }
      //メッセージを書き込むテキストエリア
      TextArea {
        id: textArea
        Layout.preferredHeight: 100
        Layout.preferredWidth: 350
        text: qsTr("")
        font.pointSize: 11
        wrapMode: Text.WordWrap
        placeholderText: "input message ..."
        Layout.fillHeight: true
        Layout.fillWidth: true
      }
      //ユーザーが選択した画像を表示するエリア
      //初期状態ではsourceは空白で何も表示しない
      Image {
        id: image
        Layout.minimumHeight: 0
        Layout.minimumWidth: 0
        Layout.maximumHeight: 200
        Layout.maximumWidth: 200
        Layout.alignment: Qt.AlignHCenter
        fillMode: Image.PreserveAspectFit
        source: ""
      }

      RowLayout {
        id: rowLayout
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Layout.fillWidth: true
        //画像を追加するボタン
        Button {
          id: addImageButton
          text: qsTr("Add Image")
          onClicked: {
            //HTMLとやり取りする機能の読み込みメソッドを呼び出す
            //ビルドがデスクトップでもQWAでも共通
            htmlFileAccess.loadFsFile("*.jpg", platform.tempLocation)
          }
        }

        Button {
          id: saveDraftButton
          enabled: textArea.text.length > 0
          text: qsTr("Save Draft")
          onClicked: {
            //テンポラリに一旦保存する
            var path = platform.tempLocation + "/debug.txt"
            platform.saveText(path, textArea.text)
            //HTMLとやり取りする機能の保存メソッドを呼び出す
            //ビルドがデスクトップでもQWAでも共通
            htmlFileAccess.saveFsFile(path, "DraftMessage.txt")
          }
        }
      }
    }
  }
}
