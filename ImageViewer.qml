import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    property url rootFolder: ""

    property bool monsters: false
    property bool hide: true

    state: "HIDE"

    onRootFolderChanged: {
        fileLoader.loadImageList(rootFolder)
    }

    states: [
        State {
            name: "HIDE"
            PropertyChanges {
                target: root
                hide: true
            }
            PropertyChanges {
                target: fileLoader
                hide: true
            }
        },
        State {
            name: "SHOW"
            PropertyChanges {
                target: root
                hide: false
            }
            PropertyChanges {
                target: fileLoader
                hide: false
            }
        }
    ]

    ScrollView {
        anchors
        {
            top: parent.top
            bottom: buttons.top
            left: parent.left
            right: parent.right
        }

        GridView {
            id: listView
            anchors.fill: parent

            cellWidth: 520
            cellHeight: monsters ? 255 : 95

            model: fileLoader.categoryModel
            delegate: categoryDelegate
        }
    }

    Rectangle {
        id: buttons

        anchors
        {
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }

        height: 30

        Button {
            id: showButton
            anchors
            {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            width: 150
            text: qsTr("Zobrazit vše")

            onClicked: {
                root.state = "SHOW"
            }
        }

        Button {
            id: hideButton

            anchors
            {
                right: showButton.left
                top: parent.top
                bottom: parent.bottom
            }

            width: 150
            text: qsTr("Schovat označené")

            onClicked: {
                root.state = "HIDE"
            }
        }
    }

    FileLoader {
        id: fileLoader
    }

    Component {
        id: categoryDelegate

        Item {
            id: categoryRoot
            height: root.monsters ? 255 : 120
            width: root.monsters ? 510 : 450 // 5 items * 90 width + spaces

            ListView {
                anchors.fill: parent
                orientation: Qt.LeftToRight

                delegate: imageDelegate
                model: fileLoader.imageModel(categoryPrefix)
            }
        }
    }

    Component {
        id: imageDelegate

        Item {
            id: imageDelegateRoot

            width: root.monsters ? 255 : 95
            height: root.monsters ? 255 : 95

            Rectangle {
                id: background
                anchors.fill: parent

                state: "NORMAL"

                onStateChanged: {
                    if(state == "NORMAL")
                        fileLoader.unselectImage(path)
                    else
                        fileLoader.selectImage(path)
                }

                states: [
                    State {
                        name: "NORMAL"
                        PropertyChanges {
                            target: background
                            color: "transparent"
                        }
                    },
                    State {
                        name: "SELECTED"
                        PropertyChanges {
                            target: background
                            color: "lightsteelblue"
                        }
                    }
                ]

                Image {
                    width: parent.width - 5
                    height: parent.height - 5
                    anchors.centerIn: parent

                    fillMode: Image.PreserveAspectFit
                    asynchronous: true

                    source: "file://" + path
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("clicked on " + path)

                        if(background.state == "NORMAL")
                        {
                            console.log("select")
                            background.state = "SELECTED"
                        }
                        else
                            background.state = "NORMAL"
                    }
                }
            }
        }
    }
}
