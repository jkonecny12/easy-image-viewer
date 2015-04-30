import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import org.ps.EasyImage 1.0

ApplicationWindow {
    id: root
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: fileDialog.visible = true
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Please choose root folder with images")
        selectFolder: true
        selectMultiple: false

        onAccepted: {
            mainForm.rootFolder = fileDialog.folder
            settings.rootLocation = fileDialog.folder
        }
    }

    MainForm {
        id: mainForm
        anchors.fill: parent
    }

    Settings {
        id: settings

        Component.onCompleted: {
            var path = settings.rootLocation
            if(path !== "")
                mainForm.rootFolder = path
        }
    }
}
