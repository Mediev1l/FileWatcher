import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    ListView {
        id: listView
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter

        model: 100

        delegate: Row {
            spacing: 3
            Text {
                id: trackerText
                text: qsTr("test")
                width: listView.width - 70
            }

            Button {
                text: "Remove"
                width: 70
                height: 20

                background: Rectangle {
                    radius: 7
                    color: "white"
                    border.color: "black"
                    border.width: 1
                }

                onClicked: {
                }
            }
        }
    }

}
