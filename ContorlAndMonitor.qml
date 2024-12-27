import QtQuick 2.0

Item {
    width: 1024
    height: 600
    Rectangle {
        id: showsinggraph
        color: "#ffffff"
        border.color: "#8bafafaf"
        border.width: 3
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.bottomMargin: 185
        anchors.topMargin: 53

        Rectangle {
            id: datafilename
            color: "#f2f2f2"
            radius: 5
            border.color: "#9b9b9b"
            anchors.fill: parent
            anchors.rightMargin: 209
            anchors.bottomMargin: 329
            anchors.leftMargin: 620
            anchors.topMargin: 9

            Text {
                id: textdatafilename
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            id: patternfilename
            color: "#bfbfbf"
            radius: 5
            border.color: "#9b9b9b"
            anchors.fill: parent
            anchors.leftMargin: 821
            anchors.topMargin: 8
            anchors.rightMargin: 8
            anchors.bottomMargin: 329

            Text {
                id: textpatternfilename
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Cursorcontrol {
            id: cursorcontrol
            x: 655
            y: 363
        }

    }

    DataStatusInfo {
        id: dataStatusInfo
        x: 0
        y: 415
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
