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
        color: "white"
        font.bold: true
    }

    Rectangle {
        width: parent.width
        height: parent.height
        border.width: 1
        border.color: "white"
        radius: 8
        anchors.top: trackerTitle.bottom
        color: "transparent"

        ListView {
            id: listView
            height: parent.height - 2
            width: parent.width - 2
            x: 1
            y: 1
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            model: FileTrackerModel{
                id: fileTrackerModel
                list: fileTracker

            }

            delegate: Rectangle {
                id: delegateRect
                color: "transparent"
                width: listView.width
                height: 20


                Row {
                    spacing: 3

                    Text {
                        id: trackerText
                        text: model.path
                        width: listView.width - 70
                        leftPadding: 6
                        topPadding: 2
                        color: "white"
                        clip: true
                    }

                    Button {
                        id: removeButton
                        width: 70
                        height: 20
                        flat: true

                        background: Rectangle {
                            radius: 7
                            color: "transparent"

                            Text {
                                text: "Remove"
                                color: removeButton.hovered ? "orange" : "white"
                                font.bold: true
                                anchors.centerIn: parent
                                bottomPadding: 2
                            }
                        }

                        onClicked: {
                            fileTracker.removeItemAt(index);
                            watcher.removePathFromWatcher(trackerText.text);
                        }
                    }
                }

                Rectangle {
                    color: "orange"
                    width: delegateRect.width * 0.98
                    height: 1
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: delegateRect.horizontalCenter
                }
            }

        }

    }
}
