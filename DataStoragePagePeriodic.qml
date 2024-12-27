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
    width: 920
    height: 475

    Rectangle {
        id: rectangle
        color: "#e7e6e6"
        radius: 15
        border.color: "#767171"
        border.width: 1
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.topMargin: 8
        anchors.rightMargin: 637
        anchors.bottomMargin: 435

        Text {
            id: text1
            text: qsTr("Text")
            anchors.fill: parent
            font.pixelSize: 17
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    RowLayout {
        x: 8
        y: 66
        width: 275
        height: 55

        ToolButton {
            id: toolButtonOpen
            text: qsTr("OPEN")
            Layout.fillWidth: true
        }

        ToolButton {
            id: toolButtonDelete
            text: qsTr("DELETE")
            Layout.fillWidth: true
        }
    }

    TextField {
        id: textField
        x: 8
        y: 142
        width: 380
        height: 40
        placeholderText: qsTr("Text Field")
    }



    DataStoragePagePeriodicSearch {
        id: dataStoragePagePeriodicSearch
        anchors.fill: parent
        anchors.leftMargin: 450
        anchors.topMargin: 0
    }
}




