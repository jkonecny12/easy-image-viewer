import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    ListView {
        id: listView

        model: fileLoader.imageModel
        delegate: categoryDelegate

    }

    ListModel {
        id: testModel

        ListElement {
            path: "../../test.jpg"
        }
    }

    FileLoader {
        id: fileLoader
    }

    Component {
        id: categoryDelegate

        Item {
            width: 80
            height: 80

            Rectangle {
                anchors.fill: parent
                color: "cyan"

                Text {
                    text: "name: " + name + " path: " + path
                }
            }
        }
    }
}



