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
                if(fileDialogTextField.text != "Add path to watch"){
                    fileTracker.appendItem(fileDialogTextField.text);
                    watcher.addPathToWatch(fileDialogTextField.text)
                    fileDialogTextField.text = "Add path to watch";
                }


            }
        }
    }
}
