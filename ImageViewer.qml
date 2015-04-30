import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    property url rootFolder: ""

    onRootFolderChanged: {
        fileLoader.loadImageList(rootFolder)
    }

    ScrollView {
        anchors.fill: parent
        ListView {
            id: listView
            anchors.fill: parent

            model: fileLoader.imageModel
            delegate: categoryDelegate
        }
    }

    FileLoader {
        id: fileLoader
    }

    Component {
        id: categoryDelegate

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 100

            ListView {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 450 // maximum 5 items * 90 width
                orientation: Qt.LeftToRight

                delegate: imageDelegate
            }

            ListView {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 450 // maximum 5 items * 90 width
                orientation: Qt.LeftToRight

                delegate: imageDelegate
            }
        }
    }

    Component {
        id: imageDelegate

        Item {
            width: 90
            height: 90

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                asynchronous: true

                source: "file://" + path
            }
        }
    }
}



