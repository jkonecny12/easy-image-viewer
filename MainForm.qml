import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root

    property url rootFolder: ""

    TabView {
        id: tabview
        anchors.fill: parent

        Tab {
            title: "Valečník"

            ImageViewer {
                rootFolder: root.rootFolder + "/3\ Valecnici"
            }
        }

        Tab {
            title: "Kouzelník"

            Rectangle {
                color: "blue"
            }
        }

        Tab {
            title: "Průzkumník"


        }
    }
}

