import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

Item {
    width: 650
    height: 185


    Rectangle {
        id: mainDataInfo
        x: 0
        y: 0
        width: 650
        height: 185
        color: "#f2f2f2"
        border.color: "#f2f2f2"
        border.width: 1
        Rectangle {
            id: rectangleData
            x: 7
            y: 35
            width: 52
            height: 150
            color: "#f2f2f2"

            Text {
                id: text1
                text: qsTr("DATA")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 131
            }
            Rectangle {
                id: rectangle1
                color: "#fd2d1d"
                anchors.fill: parent
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.bottomMargin: 109
                anchors.topMargin: 35
            }

            Rectangle {
                id: rectangle2
                color: "#fcff3b"
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 72
                anchors.bottomMargin: 72
                anchors.rightMargin: 0
            }

            Rectangle {
                id: rectangle3
                color: "#244d77"
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 113
                anchors.bottomMargin: 32
                anchors.rightMargin: 0
            }

            RowLayout {
            }

            ColumnLayout {
            }
        }
        Rectangle {
            id: rectanglePhase
            x: 76
            y: 35
            width: 52
            height: 150
            color: "#f2f2f2"

            Text {
                id: pattern
                text: qsTr("PATTERN")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 131
            }
            Rectangle {
                id: patternAphase
                color: "#f7cbac"
                anchors.fill: parent
                anchors.rightMargin: 0
                anchors.bottomMargin: 109
                anchors.leftMargin: 0
                anchors.topMargin: 35
            }

            Rectangle {
                id: patternBphase
                color: "#bc9121"
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 72
                anchors.bottomMargin: 72
                anchors.rightMargin: 0
            }

            Rectangle {
                id: patternCphase
                color: "#bed6ed"
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 113
                anchors.rightMargin: 0
                anchors.bottomMargin: 32
            }
        }
        Rectangle {
            id: ledstatusdata
            x: 216
            y: 35
            width: 52
            height: 150
            color: "#f2f2f2"

            Text {
                id: datastatus
                text: qsTr("DATA")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 0
                anchors.bottomMargin: 133
            }

            ColumnLayout {
                x: 8
                y: 23
                width: 36
                height: 120

                LedStatus {
                    id: ledStatusp
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 36
                }

                LedStatus {
                    id: ledStatusp1
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 36

                }

                LedStatus {
                    id: ledStatusp2
                }
            }


        }
        Rectangle {
            id: ledstatusPattern
            x: 292
            y: 35
            width: 52
            height: 150
            color: "#f2f2f2"

            Text {
                id: patternstatus
                text: qsTr("PATTERN")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 0
                anchors.bottomMargin: 134
            }

            ColumnLayout {
                x: 8
                y: 22

                LedStatus {
                    id: ledStatusdata1
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 36
                }

                LedStatus {
                    id: ledStatusdata2
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 36

                }

                LedStatus {
                    id: ledStatusdata3
                }
            }
        }

        Rectangle {
            id: rectangleDistance
            x: 148
            y: 35
            width: 52
            height: 150
            color: "#f2f2f2"
            Text {
                id: phasetext
                text: qsTr("PHASE")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 131
            }

            ColumnLayout {
                x: 20
                y: 25
                width: 24
                height: 117

                Text {
                    id: textA
                    text: qsTr("A")
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }

                Text {
                    id: textB
                    text: qsTr("B")
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }

                Text {
                    id: textC
                    text: qsTr("C")
                    font.pixelSize: 23
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }
            }
        }

        Rectangle {
            id: structureNo
            x: 551
            y: 35
            width: 96
            height: 150
            color: "#f2f2f2"
            Text {
                id: phasetext2
                text: qsTr("STRUCTURE NO")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 131
            }
            Rectangle {
                id: strucNo1
                color: "#e7e6e6"
                radius: 5
                border.color: "#ffffff"
                border.width: 2
                anchors.fill: parent
                anchors.rightMargin: 9
                anchors.bottomMargin: 100
                Text {
                    id: textstrucNo1
                    text: qsTr("Text")
                    anchors.fill: parent
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                anchors.topMargin: 25
                anchors.leftMargin: 9
            }
            Rectangle {
                id: strucNo2
                color: "#e7e6e6"
                radius: 5
                border.color: "#ffffff"
                border.width: 2
                anchors.fill: parent
                anchors.rightMargin: 9
                anchors.bottomMargin: 57
                Text {
                    id: textstrucNo2
                    text: qsTr("Text")
                    anchors.fill: parent
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                anchors.topMargin: 68
                anchors.leftMargin: 9
            }
            Rectangle {
                id: strucNo3
                color: "#e7e6e6"
                radius: 5
                border.color: "#ffffff"
                border.width: 2
                anchors.fill: parent
                anchors.rightMargin: 9
                anchors.bottomMargin: 14
                Text {
                    id: textstrucNo3
                    text: qsTr("Text")
                    anchors.fill: parent
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                anchors.topMargin: 111
                anchors.leftMargin: 9
            }
        }


    }

    Rectangle {
        id: rectanglePattern2
        x: 368
        y: 35
        width: 89
        height: 150
        color: "#f2f2f2"
        border.color: "#f2f2f2"
        Text {
            id: phasetext1
            text: qsTr("DISTANCE(KM)")
            anchors.fill: parent
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 133
        }

        Rectangle {
            id: firstPhaseData
            color: "#ffffff"
            radius: 5
            border.color: "#a6a6a6"
            border.width: 2
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.topMargin: 25
            anchors.rightMargin: 18
            anchors.bottomMargin: 100

            Text {
                id: distancephase1
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            id: secondPhaseData
            color: "#ffffff"
            radius: 5
            border.color: "#a6a6a6"
            border.width: 2
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.topMargin: 68
            anchors.rightMargin: 18
            anchors.bottomMargin: 56

            Text {
                id: distancephase2
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: thirdPhaseData
            color: "#ffffff"
            radius: 5
            border.color: "#a6a6a6"
            border.width: 2
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.topMargin: 111
            anchors.rightMargin: 19
            anchors.bottomMargin: 14

            Text {
                id: distancephase3
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: firstPhaseVoltage
            color: "#e7e6e6"
            radius: 5
            border.color: "#ffffff"
            border.width: 2
            anchors.fill: parent
            anchors.rightMargin: -59
            anchors.bottomMargin: 100
            Text {
                id: vlotagephase1
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            anchors.topMargin: 25
            anchors.leftMargin: 77
        }
        Rectangle {
            id: secondPhaseVoltage
            color: "#e7e6e6"
            radius: 5
            border.color: "#ffffff"
            border.width: 2
            anchors.fill: parent
            anchors.rightMargin: -59
            anchors.bottomMargin: 56
            Text {
                id: vlotagephase2
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            anchors.topMargin: 69
            anchors.leftMargin: 77
        }
        Rectangle {
            id: thirdPhaseVoltage
            color: "#e7e6e6"
            radius: 5
            border.color: "#ffffff"
            border.width: 2
            anchors.fill: parent
            anchors.rightMargin: -59
            anchors.bottomMargin: 14
            Text {
                id: vlotagephase3
                text: qsTr("Text")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            anchors.topMargin: 111
            anchors.leftMargin: 77
        }

        Text {
            id: unitmVlotage1
            x: 154
            y: 30
            text: qsTr("mV")
            font.pixelSize: 12
        }

        Text {
            id: unitmVlotage2
            x: 154
            y: 74
            text: qsTr("mV")
            font.pixelSize: 12
        }

        Text {
            id: unitmVlotage3
            x: 154
            y: 116
            text: qsTr("mV")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: detailofwire
        x: 8
        y: 0
        width: 313
        height: 35
        color: "#ffffff"
        radius: 4
        border.color: "#509d9d9d"
        border.width: 2
    }

    Rectangle {
        id: loadingbar
        x: 338
        y: 4
        width: 176
        height: 28
        color: "#e7e6e6"
        radius: 10
        border.color: "#827d7d"
        border.width: 1
    }

    ToolButton {
        id: toolButton2
        x: 520
        y: 4
        width: 122
        height: 28
        text: qsTr("Tool Button")
        font.pointSize: 10
    }



}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}D{i:29}D{i:30}D{i:31}D{i:26}D{i:32}D{i:48}D{i:55}D{i:56}
D{i:40}
}
##^##*/
