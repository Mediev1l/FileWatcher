import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import FileWatcher

Item {
    Text {
        id:trackerTitle
        text: qsTr("Watched paths")
        height: 20
        width: 5
        leftPadding: 5
    }

    Rectangle {
        width: parent.width
        height: parent.height - 20
        border.width: 1
        border.color: "black"
        radius: 5
        anchors.top: trackerTitle.bottom
        color: "blue"

        ListView {
            id: listView
            height: parent.height - 2
            width: parent.width - 2
            x: 1
            y: 1
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true

            model: FileTrackerModel{
                id: fileTrackerModel
                list: fileTracker

            }

            delegate:
                Rectangle {
                color: "#d7d7e2"
                width: listView.width
                height: 20

                Row {
                    spacing: 3
                    Text {
                        id: trackerText
                        text: model.path
                        width: listView.width - 70
                        leftPadding: 5

                        Rectangle {
                            color: "red"
                            width: parent.width * 0.98
                            height: 1
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Button {
                        text: "Remove"
                        width: 70
                        height: 20

                        background: Rectangle {
                            radius: 7
                            color: "transparent"
                        }

                        onClicked: {
                            console.log(index)
                            fileTracker.removeItemAt(index);
                        }
                    }
                }
            }
        }

    }
}
