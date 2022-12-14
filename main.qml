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
            text: "Clear"
            width: timestampComponent.width * 0.2

            onPressed: timestamp.clearItems();
        }

        Button {
            text: "Start"
            width: timestampComponent.width * 0.2

            onPressed: watcher.start();
        }

        Button {
            text: "Stop"
            width: timestampComponent.width * 0.2

            onPressed: watcher.stop();
        }
    }
}
