import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import tech.relog.plugin.fakesns4q 1.0

Window {
  visible: true
  width: 480
  height: 400
  title: qsTr("Post App")

  FakeSns4Q {
    id: fakeSns4Q
    userId: "123456789"
  }
//qmlのダイアログにしてウインドウサイズをある程度制限する

  ColumnLayout {
    anchors.fill: parent
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
      }

      Button {
        id: saveDraftButton
        text: qsTr("Save Draft")
      }


    }

  }
}
