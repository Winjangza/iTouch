import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Styles 2.15
import QtQuick.VirtualKeyboard.Settings 2.15

Item {
    width: 1024
    height: 600

    ColumnLayout {
        anchors.fill: parent
        anchors.rightMargin: 283
        anchors.bottomMargin: 412
        anchors.leftMargin: 284
        anchors.topMargin: 98

        RowLayout {
            Layout.preferredHeight: 45
            Layout.preferredWidth: 363

            Text {
                id: userName
                text: qsTr("USER NAME")
                font.pixelSize: 18
            }

            TextField {
                id: textUserName
                Layout.fillHeight: true
                Layout.fillWidth: true
                placeholderText: qsTr("Text Field")
            }
        }

        RowLayout {
            Layout.preferredHeight: 45
            Layout.preferredWidth: 363

            Text {
                id: password
                text: qsTr("PASSWORD")
                font.pixelSize: 18
                Layout.fillWidth: false
            }

            TextField {
                id: textPassword
                Layout.fillHeight: true
                Layout.fillWidth: true
                placeholderText: qsTr("Text Field")
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.bottomMargin: 332
        anchors.leftMargin: 284
        anchors.rightMargin: 283
        anchors.topMargin: 217

        ToolButton {
            id: logOutButton
            text: qsTr("LOG-OUT")
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ToolButton {
            id: logInButton
            text: qsTr("LOG-IN")
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
