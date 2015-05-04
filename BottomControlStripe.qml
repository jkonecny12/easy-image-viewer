import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    signal setShow
    signal setHide

    ComboBox {
        id: usersCombobox

        model: Settings.users
    }

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

        onClicked: root.setShow()
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

        onClicked: root.setHide()
    }
}
