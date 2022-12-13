import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

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
        height: mainWindow.height * 0.3

        anchors {
            top: fileTrackerComponent.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 20
        }
    }
}
