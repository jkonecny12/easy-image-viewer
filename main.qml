import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import org.ps.EasyImage 1.0

ApplicationWindow {
    id: root
    title: qsTr("Hello World")
    width: 870
    height: 640
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("&Open")
                onTriggered: fileDialog.visible = true
            }
            MenuItem {
                text: qsTr("Add &User")
                onTriggered: addUserDialog.visible = true
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

    Dialog {
        id: addUserDialog
        title: qsTr("Add user")
        standardButtons: StandardButton.save | StandardButton.Cancel


        contentItem: Rectangle {
            id: contentRoot

            implicitHeight: 60
            implicitWidth: 280

            RowLayout {
                anchors {
                    top: parent.top
                    bottom: buttonsLayout.top
                    left: parent.left
                    right: parent.right
                }

                Label {
                    text: qsTr("Jméno uživatele:")
                }

                Rectangle {
                    id: textBackground

                    color: "gray"

                    Layout.preferredHeight: 25
                    Layout.fillWidth: true

                    TextInput {
                        id: userName

                        anchors.fill: parent
                    }
                }
            }

            RowLayout {
                id: buttonsLayout

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right

                Button {
                    id: acceptButton

                    text: qsTr("Potvrdit")

                    Layout.fillWidth: true

                    onClicked: {
                        if(userName.text != "") {
                            Settings.addUser(userName.text)
                        }

                        addUserDialog.visible = false
                    }
                }

                Button {
                    id: cancelButton

                    text: qsTr("Zrušit")

                    Layout.fillWidth: true

                    onClicked: addUserDialog.visible = false
                }
            }
        }
    }

    MainForm {
        id: mainForm
        anchors.fill: parent
    }

    Component.onCompleted: {
        var path = Settings.rootLocation
        if(path !== "")
            mainForm.rootFolder = path
    }
}
