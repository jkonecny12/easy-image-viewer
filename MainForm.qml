import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root

    TabView {
        id: tabview
        anchors.fill: parent

        Tab {
            title: "Valečník"

            ImageViewer {
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

