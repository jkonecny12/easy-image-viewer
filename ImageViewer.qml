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
        GridView {
            id: listView
            anchors.fill: parent

            cellWidth: 480

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
            height: 120
            width: 500 // 5 items * 90 width + spaces

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
            width: 100
            height: 100

            Image {
                anchors.centerIn: parent
                width: 90
                height: 90

                fillMode: Image.PreserveAspectFit
                asynchronous: true

                source: "file://" + path
            }
        }
    }
}



