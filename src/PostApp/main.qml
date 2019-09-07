import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import tech.relog.plugin.fakesns4q 1.0
import tech.relog.plugin.platform 1.0

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Post App")
  //Webフォントの読み込み
  FontLoader{
    id:webFont
    source: "http://mplus-fonts.osdn.jp/webfonts/general-j/mplus-1-light-sub.ttf"
  }
  //SNSから情報を取得する機能の配置
  FakeSns4Q {
    id: fakeSns4Q
    //取得するユーザーのIDをサンプルでは予め設定
    //本来であれば何らかのイベントで設定される値
    userId: "123456789"
  }
  //プラットフォーム機能の配置
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
        //ユーザー名の配置
        Label {
          id: userNameLabel
          Layout.fillWidth: true
          //SNS機能のユーザー名が入るプロパティにバインディング
          //情報が取得できれば自動で表示される
          text: fakeSns4Q.userName
          font.pointSize: 12
          font.family: webFont.name
        }
      }
      //メッセージを書き込むテキストエリア
      TextArea {
        id: textArea
        Layout.preferredHeight: 100
        Layout.preferredWidth: 350
        text: qsTr("")
        font.pointSize: 11
        font.family: jfont.name
        wrapMode: Text.WordWrap
        placeholderText: "input message ..."
        Layout.fillHeight: true
        Layout.fillWidth: true
        background: Rectangle {
          border.width: 1
          border.color: textArea.focus ? "#111111" : "#bbbbbb"
        }
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
        //ダイアログで選択したパスがセットされたら表示
        source: platform.selectedFile.length > 0 ?
                  "file:///" + platform.selectedFile : ""
      }

      RowLayout {
        id: rowLayout
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Layout.fillWidth: true
        //画像を追加するボタン
        Button {
          id: addImageButton
          font.family: webFont.name
          text: qsTr("Add Image")
          onClicked: {
            //HTMLとやり取りする機能の選択メソッドを呼び出す
            //ビルドがデスクトップでもQWAでも共通
            platform.selectFile("*.jpg")
          }
        }

        Button {
          id: saveDraftButton
          enabled: textArea.text.length > 0
          font.family: webFont.name
          text: qsTr("Save Draft")
          onClicked: {
            //テンポラリに一旦保存
            var path
            path = platform.saveText("postapp.txt", textArea.text)
            //HTMLとやり取りする機能の保存メソッドを呼び出す
            //ビルドがデスクトップでもQWAでも共通
            platform.saveFile(path, "DraftMessage.txt")
          }
        }
      }
    }
  }
}
