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
    width: 530
    height: 460

    Rectangle {
        id: rectangle
        color: "#f2f2f2"
        border.color: "#ffffff"
        border.width: 2
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

        RowLayout {
            x: 8
            y: 8
            width: 514
            height: 35

            TextField {
                id: namesearch
                Layout.fillWidth: true
                placeholderText: qsTr("Text Field")
            }

            ToolButton {
                id: toolButtonNameSearch
                text: qsTr("Tool Button")
                Layout.preferredHeight: 22
                Layout.preferredWidth: 62
            }

            TextField {
                id: dataSearch
                Layout.fillWidth: true
                placeholderText: qsTr("Text Field")
            }

            ToolButton {
                id: toolButtondataSearech
                text: qsTr("Tool Button")
                Layout.preferredHeight: 22
                Layout.preferredWidth: 62
            }
        }

        Rectangle {
            id: rectangle1
            color: "#d9d9d9"
            border.color: "#ffffff"
            border.width: 2
            anchors.fill: parent
            anchors.bottomMargin: 0
            anchors.topMargin: 49

            Rectangle {
                id: rectangle2
                color: "#d9d9d9"
                radius: 5
                border.color: "#ffffff"
                anchors.fill: parent
                anchors.leftMargin: 8
                anchors.rightMargin: 8
                anchors.topMargin: 8
                anchors.bottomMargin: 373

                ToolButton {
                    id: sortName
                    text: qsTr("Tool Button")
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.topMargin: 1
                    anchors.bottomMargin: 0
                    anchors.rightMargin: 459
                }

                ToolButton {
                    id: sortDate
                    text: qsTr("Tool Button")
                    anchors.fill: parent
                    anchors.leftMargin: 309
                    anchors.rightMargin: 158
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0
                }

                Text {
                    id: nameofdata
                    text: qsTr("NAME")
                    anchors.fill: parent
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.bottomMargin: 0
                    anchors.topMargin: 1
                    anchors.leftMargin: 61
                    anchors.rightMargin: 382
                }

                Text {
                    id: dateofdata
                    text: qsTr("Date")
                    anchors.fill: parent
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0
                    anchors.rightMargin: 90
                    anchors.leftMargin: 362
                }

            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
