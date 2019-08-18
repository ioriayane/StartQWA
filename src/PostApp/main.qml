import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3 as Dialogs
import tech.relog.plugin.fakesns4q 1.0
import tech.relog.plugin.platform 1.0

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Post App")

  FakeSns4Q {
    id: fakeSns4Q
    userId: "123456789"
  }
  Platform {
    id: platform
  }

  Dialog {
    visible: true
    modal: false
    margins: 10
    closePolicy: Popup.NoAutoClose

    contentItem: ColumnLayout {
      anchors.margins: 10
      spacing: 5

      RowLayout {
        Layout.fillWidth: true
        Image {
          id: userIconImage
          Layout.preferredHeight: 50
          Layout.preferredWidth: 50
          fillMode: Image.PreserveAspectFit
          source: fakeSns4Q.userIcon
        }

        Label {
          id: userNameLabel
          Layout.fillWidth: true
          text: fakeSns4Q.userName
          font.pointSize: 12
        }

      }

      TextArea {
        id: textArea
        Layout.preferredHeight: 50
        Layout.preferredWidth: 350
        text: qsTr("")
        font.pointSize: 11
        wrapMode: Text.WordWrap
        placeholderText: "input message ..."
        Layout.fillHeight: true
        Layout.fillWidth: true
      }

      Image {
        id: image
        Layout.fillWidth: true
        Layout.minimumHeight: 0
        Layout.minimumWidth: 0
        Layout.maximumHeight: 200
        fillMode: Image.PreserveAspectFit
        source: ""
      }

      RowLayout {
        id: rowLayout
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Layout.fillWidth: true

        Button {
          id: addImageButton
          text: qsTr("Add Image")
          onClicked: {
            if(platform.type == "web"){
              htmlFileAccess.loadFsFile("*.jpg", "/tmp")
            }else{
              fileDialog.fileOpen = true
              fileDialog.open()
            }
          }
        }

        Button {
          id: saveDraftButton
          enabled: textArea.text.length > 0
          text: qsTr("Save Draft")
          onClicked: {
            if(platform.type == "web"){
              var path = "/tmp/debug.txt"
              platform.saveText("file://" + path, textArea.text)
              htmlFileAccess.saveFsFile(path, "DraftMessage.txt")
            }else{
              fileDialog.fileOpen = false
              fileDialog.open()
            }
          }
        }
      }
    }
  }
  //HTML側のファイルを開く処理のコールバック
  Connections {
    target: htmlFileAccess
    onFsFileReady: {
      var path = "file://" + tmpFilePath
      console.debug(path)
      image.source = path
    }
  }
  //デスクトップ用のファイルダイアログ
  Dialogs.FileDialog {
    id: fileDialog
    property bool fileOpen: true
    selectExisting: fileOpen
    title: fileOpen ? "Please select image file" :
                      "Please input file name"
    nameFilters: fileOpen ? ["Image files (*.jpg *.png)", "All files (*)"] :
                            ["Text files (*.txt)"]
    onAccepted: {
      console.debug(fileUrl)
      if(fileOpen){
        //開く
        image.source = fileUrl
      }else{
        //保存
        platform.saveText(fileUrl, textArea.text)
      }
    }
  }
}
