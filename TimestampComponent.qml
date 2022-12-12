import QtQuick 2.15

import FileWatcher

Item {
    Rectangle {
        id: timestampRect
        width: parent.width
        height: parent.height - 20
        border.width: 1
        border.color: "black"
        radius: 5

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
                    color: "orange"

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: tableView.model.headerData(index, Qt.Horizontal)
                    }
                }
            }
        }



        TableView {
            id: tableView
            height: parent.height - header.height - 1
            width: parent.width
            x: 1
            clip: true
            columnSpacing: 1
            anchors.top: header.bottom
            onWidthChanged: forceLayout()

            model: TimestampModel {
                id: timestampModel
            }
            boundsBehavior: Flickable.StopAtBounds

            delegate: Rectangle {
                implicitHeight: 20
                implicitWidth: timestampModel.columnWidth(column,timestampRect.width) - tableView.columnSpacing
                border.color: "black"
                border.width: 1
                Text {
                    id: text
                    text: "delegate"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

        }
    }
}
