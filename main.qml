import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("FileWatcher")
    color: "#44454a"


    FileDialogComponent {
        id: fileDialogComponent
        width: mainWindow.width * 0.9

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 20
        }
    }

    FileTrackerComponent {
        id: fileTrackerComponent
        width: mainWindow.width * 0.9
        height: mainWindow.height * 0.3

        anchors {
            top: fileDialogComponent.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 20
        }

    }

    TimestampComponent {
        id: timestampComponent
        width: mainWindow.width * 0.9
        height: mainWindow.height * 0.45

        anchors {
            top: fileTrackerComponent.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 30
        }
    }

    Row {
        anchors {
            top: timestampComponent.bottom
            left: timestampComponent.left
            topMargin: 10
        }

        spacing: 10

        Button {
            id: clearButton
            width: timestampComponent.width * 0.2
            height: 20
            flat: true

            onPressed: timestamp.clearItems();

            background: Rectangle {
                radius: 7
                color: "transparent"
                border.color: clearButton.hovered ? "orange" : "white"
                border.width: 1

                Text {
                    text: "Clear"
                    color: clearButton.hovered ? "orange" : "white"
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }

        Button {
            id: trackButton
            width: timestampComponent.width * 0.2
            height: 20
            flat: true

            onPressed: {
                trackerText.text = watcher.m_track ?  "Start" : "Stop";
                watcher.trackFiles(!watcher.m_track);
            }

            background: Rectangle {
                radius: 7
                color: "transparent"
                border.color: trackButton.hovered ? "orange" : "white"
                border.width: 1

                Text {
                    id: trackerText
                    text: "Stop"
                    color: trackButton.hovered ? "orange" : "white"
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }
    }
}
