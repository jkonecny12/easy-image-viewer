import QtQuick 2.0
import QtQuick.Controls 1.2


Rectangle {
    id: root

    property url rootFolder: ""

    TabView {
        id: tabview
        anchors.fill: parent

        Tab {
            title: qsTr("Valečník")

            ImageViewer {
                rootFolder: root.rootFolder + "/3\ Valecnici"
            }
        }

        Tab {
            title: qsTr("Kouzelník")

            ImageViewer {
                rootFolder: root.rootFolder + "/4\ Kouzelnici"
            }
        }

        Tab {
            title: qsTr("Průzkumník")

            ImageViewer {
                rootFolder: root.rootFolder + "/5\ Pruzkumnici"
            }
        }

        Tab {
            title: qsTr("Cennosti")

            ImageViewer {
                rootFolder: root.rootFolder + "/2\ Cennosti"
            }
        }

        Tab {
            title: qsTr("Monstra")

            ImageViewer {
                rootFolder: root.rootFolder + "/1\ Monstra"
                monsters: true
            }
        }
    }
}

