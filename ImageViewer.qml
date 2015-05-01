import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    property url rootFolder: ""

    property bool monsters: false

    onRootFolderChanged: {
        fileLoader.loadImageList(rootFolder)
    }

    ScrollView {
        anchors.fill: parent
        GridView {
            id: listView
            anchors.fill: parent

            cellWidth: monsters ? 520 : 480
            cellHeight: monsters ? 255 : 95

            model: fileLoader.categoryModel
            delegate: categoryDelegate
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
            width: root.monsters ? 255 : 95
            height: root.monsters ? 255 : 95

            Image {
                width: parent.width - 5
                height: parent.height - 5
                anchors.centerIn: parent

                fillMode: Image.PreserveAspectFit
                asynchronous: true

                source: "file://" + path
            }
        }
    }
}



