import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    width: 369
    height: 184

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 369
        height: 184
        color: "#ffffff"
        border.color: "#c8595959"
        border.width: 1
        ToolButton {
            id: clearalarm
            text: qsTr("CLEAR \n ALARM")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 17
            anchors.rightMargin: 259
            anchors.bottomMargin: 118
        }

        ToolButton {
            id: cleardisplay
            text: qsTr("CLEAR \n DISPLAY")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 72
            anchors.rightMargin: 259
            anchors.bottomMargin: 63
        }

        ToolButton {
            id: cleardisplay1
            text: qsTr("CLEAR \n PATTERN")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 127
            anchors.rightMargin: 259
            anchors.bottomMargin: 8
        }

        Text {
            id: text5
            text: qsTr("CURSOR(KM)")
            anchors.fill: parent
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 187
            anchors.topMargin: 0
            anchors.rightMargin: 59
            anchors.bottomMargin: 152
        }

        ToolButton {
            id: cursorLeft
            text: qsTr("arrowL")
            anchors.fill: parent
            font.pointSize: 9
            anchors.rightMargin: 163
            anchors.bottomMargin: 111
            anchors.topMargin: 38
            anchors.leftMargin: 130
        }

        ToolButton {
            id: cursorRight
            text: qsTr("arrowR")
            anchors.fill: parent
            font.pointSize: 9
            anchors.rightMargin: 14
            anchors.bottomMargin: 111
            anchors.topMargin: 38
            anchors.leftMargin: 279
        }

        Rectangle {
            id: cursorDistance
            color: "#ffffff"
            radius: 5
            border.color: "#7a7a7a"
            border.width: 1
            anchors.fill: parent
            anchors.leftMargin: 212
            anchors.topMargin: 38
            anchors.rightMargin: 96
            anchors.bottomMargin: 111

            Text {
                id: text6
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        ToolButton {
            id: patterntest
            x: 130
            y: 97
            width: 107
            height: 69
            text: qsTr("PATTERN \n TEST")
        }

        ToolButton {
            id: manualtest
            x: 248
            y: 97
            width: 107
            height: 69
            text: qsTr("MANUAL \n TEST")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/
