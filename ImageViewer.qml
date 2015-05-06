import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    property alias rootFolder: fileLoader.rootPath
    property alias folderName: fileLoader.folderName

    property bool monsters: false
    property bool hide: true

    property int itemSize: 85
    property int monsterSize: 245

    signal shiftClicked(string item)

    state: "HIDE"

    states: [
        State {
            name: "HIDE"
            PropertyChanges {
                target: root
                hide: true
            }
       },
        State {
            name: "SHOW"
            PropertyChanges {
                target: root
                hide: false
            }
       }
    ]

    ScrollView {
        anchors
        {
            top: parent.top
            bottom: controlStripe.top
            left: parent.left
            right: parent.right
        }

        GridView {
            id: listView
            anchors.fill: parent

            cellWidth: root.monsters ? root.monsterSize : root.itemSize
            cellHeight: cellWidth

            model: fileLoader.imageModel
            delegate: imageDelegate

            focus: true

            Keys.onPressed: {
                console.log("test")
            }
        }
    }

    BottomControlStripe {
        id: controlStripe

        anchors
        {
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }

        height: 30

        onSetShow: {
            root.state = "SHOW"
            fileLoader.hideItems(false)
        }

        onSetHide: {
            root.state = "HIDE"
            fileLoader.hideItems(true)
            fileLoader.saveSelectedItems(controlStripe.activeUser)
        }

        onActiveUserChanged: {
            if(fileLoader.loadSelectedItems(activeUser))
                fileLoader.loadImageList()
        }
    }

    FileLoader {
        id: fileLoader

        onRootPathChanged: {
            fileLoader.loadSelectedItems(controlStripe.activeUser)
            fileLoader.loadImageList()
        }
    }

    Component {
        id: imageDelegate

        Item {
            id: imageDelegateRoot

            width: root.monsters ? root.monsterSize : root.itemSize
            height: width

            Rectangle {
                id: background
                anchors.fill: parent

                state: selected ? "SELECTED" : "NORMAL"

                onStateChanged: {
                    if(state == "NORMAL")
                        fileLoader.unselectImage(path)
                    else
                        fileLoader.selectImage(path)
                }

                Component.onCompleted: {
                    root.shiftClicked.connect(testForSelection)
                }

                function testForSelection(item)
                {
                    if(fileLoader == undefined)
                        return

                    var selectedItems = fileLoader.selectedItems()
                    var lastSelected = selectedItems[selectedItems.length - 2]

                    if(path > lastSelected && path < item)
                    {
                        background.state = "SELECTED"
                    }
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

                        console.log("modifier: " + (mouse.modifiers & Qt.ShiftModifier))

                        if(background.state == "NORMAL")
                        {
                            console.log("select")
                            background.state = "SELECTED"
                        }
                        else
                            background.state = "NORMAL"

                        if(mouse.modifiers & Qt.ShiftModifier)
                        {
                           root.shiftClicked(path)
                        }
                    }
                }
            }
        }
    }
}
