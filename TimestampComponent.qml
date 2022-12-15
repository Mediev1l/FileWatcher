import QtQuick 2.15

import FileWatcher

Item {
    Rectangle {
        id: timestampRect
        width: parent.width
        height: parent.height
        border.width: 1
        border.color: "white"
        radius: 5
        color: "transparent"

        Row {
            id: header
            width: timestampRect.width
            height: 20
            spacing: 1
            x: 1

            Repeater {
                model: tableView.model.columnCount()
                Rectangle {
                    width:  tableView.model.columnWidth(index, parent.width) - header.spacing
                    height: parent.height
                    y: 1
                    color: "transparent"

                    Text {
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: tableView.model.headerData(index, Qt.Horizontal)
                        font.bold: true
                    }
                }
            }
        }

        Rectangle {
            id: spacer
            color: "orange"
            width: header.width * 0.98
            height: 1
            anchors.top: header.bottom
            anchors.horizontalCenter: header.horizontalCenter
            anchors.topMargin: 2
        }

        TableView {
            id: tableView
            height: parent.height - (spacer.y + spacer.height) - 4
            width: parent.width
            x: 1
            clip: true
            columnSpacing: 1
            anchors.top: spacer.bottom
            anchors.topMargin: 2
            onWidthChanged: forceLayout()

            model: TimestampModel {
                id: timestampModel
                list: timestamp
            }


            boundsBehavior: Flickable.StopAtBounds

            delegate: Rectangle {
                implicitHeight: 20
                implicitWidth: timestampModel.columnWidth(column,timestampRect.width) - tableView.columnSpacing
//                border.color: "white"
//                border.width: 1
                clip: true
                color: "transparent"
                Text {
                    id: text
                    text: model.display
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
