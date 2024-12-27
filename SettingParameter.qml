import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

Item {
    width: 920
    height: 475

    Rectangle {
        id: rectangle
        color: "#f2f2f2"
        border.color: "#ffffff"
        border.width: 2
        anchors.fill: parent

        Text {
            id: thresholdsetting
            x: 8
            y: 19
            text: qsTr("THRESHOLD SETTING")
            font.pixelSize: 18
        }

        Text {
            id: text1
            x: 8
            y: 102
            width: 600
            height: 29
            text: "MARGIN SETTING: each margin cover FULL DISTANCE divided by MARGIN"
            font.pixelSize: 15
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
        }

        RowLayout {
            x: 663
            y: 57

            Text {
                id: phaseC
                text: qsTr("PHASE C")
                font.pixelSize: 16
            }

            TextField {
                id: textPhaseC
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                placeholderText: qsTr("Text Field")
            }

            Text {
                id: unitPhaseC
                text: qsTr("mV")
                font.pixelSize: 16
            }
        }

        RowLayout {
            x: 351
            y: 57

            Text {
                id: phaseB
                text: qsTr("PHASE B")
                font.pixelSize: 16
            }

            TextField {
                id: textPhaseB
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                placeholderText: qsTr("Text Field")
            }

            Text {
                id: unitPhaseB
                text: qsTr("mV")
                font.pixelSize: 16
            }
        }

        RowLayout {
            x: 63
            y: 57

            Text {
                id: phaseA
                text: qsTr("PHASE A")
                font.pixelSize: 16
            }

            TextField {
                id: textPhaseA
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                placeholderText: qsTr("Text Field")
            }

            Text {
                id: unitPhaseA
                text: qsTr("mV")
                font.pixelSize: 16
            }
        }

        RowLayout {
            x: 31
            y: 147

            ParameterPhaseA {
                id: parameterPhaseA
                Layout.preferredHeight: 305
                Layout.preferredWidth: 275
            }

            ParameterPhaseB {
                id: parameterPhaseB
                Layout.preferredHeight: 305
                Layout.preferredWidth: 283
            }

            ParameterPhaseC {
                id: parameterPhaseC
                Layout.preferredHeight: 299
                Layout.preferredWidth: 291
            }
        }
    }


}
