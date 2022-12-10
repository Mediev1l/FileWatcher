import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls

Item {
    FolderDialog {
        id: fileDialog

        onAccepted: {
            fileDialogTextField.text = currentFolder
        }
    }

    Row {
        width: parent.width - 3
        anchors.verticalCenter: parent.verticalCenter
        spacing: 3

        TextField {
            id: fileDialogTextField
            text: "Add path to watch"
            //            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                radius: 7
                color: "white"
                border.color: "black"
                border.width: 1
            }
            width: parent.width - 70
            height: 20

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    fileDialog.open();
                }
            }
        }

        Button {
            text: "Add"
            width: 70
            height: 20

            background: Rectangle {
                radius: 7
                color: "white"
                border.color: "black"
                border.width: 1
            }

            onClicked: {
                fileDialogTextField.text = "Add path to watch";
                // add to ListView
            }
        }
    }
}