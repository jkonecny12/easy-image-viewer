import QtQuick 2.0
import QtQuick.Controls 1.2

import org.ps.EasyImage 1.0

Rectangle {
    id: root

    signal setShow
    signal setHide

    property alias activeUser: usersCombobox.currentText

    ComboBox {
        id: usersCombobox

        model: Settings.users

        Component.onCompleted: {
            Settings.activeUserChanged.connect(setActiveUser)

            setActiveUser()

            currentTextChanged.connect(setSettingsUser)
        }

        function setActiveUser()
        {
            var activeUser = Settings.activeUser

            if(activeUser !== usersCombobox.currentText)
            {
                var index = usersCombobox.find(activeUser)
                usersCombobox.currentIndex = index
            }
        }

        function setSettingsUser()
        {
            Settings.activeUser = currentText
        }

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
