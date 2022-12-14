import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls

import FileWatcher

Item {
    FolderDialog {
        id: fileDialog

        onAccepted: {
            fileDialogTextField.text = selectedFolder
        }
    }

    Row {
        width: parent.width - 3
        anchors.verticalCenter: parent.verticalCenter
        spacing: 3

        TextField {
            id: fileDialogTextField
            text: "Add path to watch"
            color: fileDialogTextField.hovered ? "orange" : "white"
            background: Rectangle {
                radius: 7
                color: "transparent"
                border.color: fileDialogTextField.hovered ? "orange" : "white"
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
            id: addButton
            width: 70
            height: 20
            flat: true

            background: Rectangle {
                radius: 7
                color: "transparent"
                border.color: addButton.hovered ? "orange" : "white"
                border.width: 1

                Text {
                    text: "Add"
                    color: addButton.hovered ? "orange" : "white"
                    font.bold: true
                    anchors.centerIn: parent
                }
            }

            onClicked: {
                if(fileDialogTextField.text != "Add path to watch"){
                    fileTracker.appendItem(fileDialogTextField.text);
                    watcher.addPathToWatch(fileDialogTextField.text)
                    fileDialogTextField.text = "Add path to watch";
                }


            }
        }
    }
}
