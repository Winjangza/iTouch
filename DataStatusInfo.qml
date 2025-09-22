import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
Item {
    id: root
    width: 650
    height: 220
    //    property alias remoteImage: remoteImage
    property alias progressIndicator: progressIndicator
    property bool isGreenPatternA: updataStatusOfPatternA
    property bool isGreenPatternB: updataStatusOfPatternB
    property bool isGreenPatternC: updataStatusOfPatternC
    property bool isGreenButA: updataStatusOfButtonA
    property bool isGreenButB: updataStatusOfButtonB
    property bool isGreenButC: updataStatusOfButtonC

    property bool activeDataA: hasDataA
    property bool activeDataB: hasDataB
    property bool activeDataC: hasDataC
    property var voltageDataA: dataPointA
    property string detailwire: detailwireInformation
    property double realDistanceA_Measure: realDistanceA
    property double realDistanceB_Measure: realDistanceB
    property double realDistanceC_Measure: realDistanceC
    property string modeUserMasterandSlave: remoteMonitor
    property bool isMasterMode: true
    property string userModeSelect: userMode || deviceMode
    property bool hidding

    property int percent: contorlAndMonitorPercentPlot
    Rectangle {
        id: mainDataInfo
        color: "#f2f2f2"
        border.color: "#f2f2f2"
        border.width: 1
        anchors.fill: parent
        anchors.bottomMargin: 0

        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 187

            Rectangle {
                id: detailofwire
                color: "#ffffff"
                radius: 4
                border.color: "#509d9d9d"
                border.width: 2
                Layout.fillWidth: false
                Layout.leftMargin: 3
                Layout.preferredHeight: 29
                Layout.preferredWidth: 217

                Text {
                    id: detailInfor
                    text: detailwire
                    anchors.fill: parent
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.leftMargin: 0
                }

            }

            Rectangle {
                id: progressContainer
                width: 184
                height: 23
                radius: height / 2
                border.color: "#000000"
                border.width: 2
                color: "#E1E1E1"
                clip: true

                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.topMargin: 10

                opacity: (contorlAndMonitorPercentPlot > 0 && contorlAndMonitorPercentPlot < 100) ? 1 : 0

                Behavior on opacity {
                    NumberAnimation { duration: 100 }
                }

                Rectangle {
                    id: progressIndicator
                    width: progressContainer.width * (contorlAndMonitorPercentPlot / 100.0)
                    height: parent.height
                    radius: height / 2
                    border.color: "#E0E0E0"
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#3BC425" }
                        GradientStop { position: 1.0; color: "#3BC425" }
                    }
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    anchors.centerIn: parent
                    text: contorlAndMonitorPercentPlot + "%"
                    color: "black"
                    font.pixelSize: 12
                    visible: contorlAndMonitorPercentPlot > 0 && contorlAndMonitorPercentPlot < 100
                }
            }


            DelayButton {
                id: delayButton
                x: 211
                y: 0
                text: userModeSelect === "MASTER"? qsTr("REMOTE TO SLAVE") : qsTr("REMOTE TO MASTER")
                delay: 500
                Layout.rightMargin: 10
                Layout.leftMargin: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
                contentItem: Text {
                    anchors.centerIn: parent
                    text: delayButton.text
                    font.pixelSize: 14
                    font.bold: true
                    color: "#000000"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onActivated: {
                    const remote = '{"objectName":"CHANGE"}'
                    qmlCommand(remote);
                    console.log("DelayButton activated! Sent:", remote);
                }
            }
        }


        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 4
            anchors.topMargin: 33


            ColumnLayout {
                id: datacolor
                Layout.preferredHeight: 180
                Layout.fillWidth: true
                Text {
                    id: dataline
                    text: qsTr("DATA")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                }

                Rectangle {
                    id: rectangle1
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: false
                    Layout.topMargin: 0
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 50

                    Rectangle {
                        id: rectangle4
                        height: 6
                        color: "#fd2d1d"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.topMargin: 0
                        Layout.preferredWidth: 50
                        Layout.preferredHeight: 6
                        Layout.fillHeight: false
                        Layout.fillWidth: false
                    }

                }

                Rectangle {
                    id: rectangle5
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.topMargin: 0
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 40

                    Rectangle {
                        id: rectangle2
                        height: 6
                        color: "#fcff3b"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 0
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredHeight: 6
                        Layout.preferredWidth: 50

                    }
                    Layout.fillWidth: false
                }

                Rectangle {
                    id: rectangle6
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.topMargin: 0
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 40

                    Rectangle {
                        id: rectangle3
                        height: 6
                        color: "#0088ff"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 0
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredHeight: 5
                        Layout.preferredWidth: 50

                    }
                    Layout.fillWidth: false
                }
            }


            ColumnLayout {
                id: patterncolor
                width: 50
                Layout.preferredHeight: 180
                Text {
                    id: dataline1
                    text: qsTr("PATTERN")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                }

                Rectangle {
                    id: rectangle10
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.topMargin: 0
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 40

                    Rectangle {
                        id: patternAphase
                        height: 6
                        color: "#f7cbac"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Layout.fillHeight: false
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredHeight: 6
                        Layout.preferredWidth: 50

                    }
                    Layout.fillWidth: false
                }

                Rectangle {
                    id: rectangle12
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.topMargin: 0
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false

                    Rectangle {
                        id: patternBphase
                        height: 6
                        color: "#bc9121"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredHeight: 6
                        Layout.preferredWidth: 50

                    }
                }

                Rectangle {
                    id: rectangle14
                    color: "#00fd2d1d"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.topMargin: 0
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false

                    Rectangle {
                        id: patternCphase
                        height: 6
                        color: "#bed6ed"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredHeight: 5
                        Layout.preferredWidth: 50
                    }
                }

                Layout.fillWidth: true
            }

            ColumnLayout {
                id: phaseName
                width: 40
                height: 163
                Layout.fillWidth: true
                Layout.preferredHeight: 180

                Text {
                    id: phasetext
                    text: qsTr("PHASE")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    Layout.fillWidth: true
                }
                Text {
                    id: textA
                    text: qsTr("A")
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    font.bold: true
                }

                Text {
                    id: textB
                    text: qsTr("B")
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    font.bold: true
                }

                Text {
                    id: textC
                    text: qsTr("C")
                    font.pixelSize: 23
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    font.bold: true
                }

            }

            ColumnLayout {
                id: databutton
                width: 53
                height: 194
                Layout.fillWidth: true
                Layout.preferredHeight: 180
                Layout.leftMargin: 0

                Text {
                    id: datastatus
                    x: 197
                    y: 39
                    text: qsTr("DATA")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: databuttonPhaseA
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    topPadding: 6
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenButA ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: {
                        isGreenButA = !isGreenButA;
                        console.log("isGreenButA:", isGreenButA);

                        if (isGreenButA) {
                            //                            controlAndMonitor.replotDataA();
                            reloadTaggingData()
                        } else {
                            //                            controlAndMonitor.hiddingGraphDataPhaseA();
                            reloadTaggingData()
                        }
                        var updateStatusisGreenButA = '{"objectName":"updateisGreenBut","updateStatusisGreenButA": '+isGreenButA+'}'
                        console.log("updateStatusisGreenButA:", updateStatusisGreenButA);
                        qmlCommand(updateStatusisGreenButA);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }

                ToolButton {
                    id: databuttonPhaseB
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    topPadding: 6
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    Layout.fillHeight: false
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenButB  ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: {
                        isGreenButB = !isGreenButB;
                        console.log("isGreenButB:", isGreenButB);

                        if (isGreenButB) {
                            //                            controlAndMonitor.replotDataB();
                            reloadTaggingData()
                        } else {
                            //                            controlAndMonitor.hiddingGraphDataPhaseB();
                            reloadTaggingData()
                        }

                        var updateStatusisGreenButB = '{"objectName":"updateisGreenBut","updateStatusisGreenButB": '+isGreenButB+'}'
                        console.log("updateStatusisGreenButB:", updateStatusisGreenButB);
                        qmlCommand(updateStatusisGreenButB);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }

                ToolButton {
                    id: databuttonPhaseC
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    topPadding: 6
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    Layout.fillHeight: false
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenButC ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    onClicked: {
                        isGreenButC = !isGreenButC;
                        console.log("isGreenButC:", isGreenButC);
                        if (isGreenButC) {
                            //                            controlAndMonitor.replotDataC();
                            reloadTaggingData()
                        } else {
                            //                            controlAndMonitor.hiddingGraphDataPhaseC();
                            reloadTaggingData()
                        }
                        var updateStatusisGreenButC = '{"objectName":"updateisGreenBut","updateStatusisGreenButC": '+isGreenButC+'}'
                        console.log("updateStatusisGreenButC:", updateStatusisGreenButC);
                        qmlCommand(updateStatusisGreenButC);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }







            ColumnLayout {
                id: patternButton
                width: 51
                height: 190
                Layout.fillWidth: true
                Layout.preferredHeight: 180
                Text {
                    id: patternstatus
                    x: 258
                    y: 39
                    text: qsTr("PATTERN")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: patternButtonPhaseA
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenPatternA ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                    }
                    onClicked: {
                        isGreenPatternA = !isGreenPatternA;
                        console.log("isGreenPatternA:", isGreenPatternA);

                        if (isGreenPatternA) {
                            //                              controlAndMonitor.replotPatternA();
                            reloadTaggingData()
                        } else {
                            //                              controlAndMonitor.hiddingGraphPatternPhaseA();
                            reloadTaggingData()
                        }

                        var updateStatusPatternA = '{"objectName":"updateisGreenBut","updateStatusisGreenPatternA": '+isGreenPatternA+'}'
                        console.log("updateStatusPatternA:", updateStatusPatternA);
                        qmlCommand(updateStatusPatternA);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }

                ToolButton {
                    id: patternButtonPhaseB
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenPatternB ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                    }
                    onClicked: {
                        isGreenPatternB = !isGreenPatternB;
                        console.log("isGreenPatternB:", isGreenPatternB);

                        if (isGreenPatternB) {
                            //                              controlAndMonitor.replotPatternB();
                            reloadTaggingData()
                        } else {
                            //                              controlAndMonitor.hiddingGraphPatternPhaseB();
                            reloadTaggingData()
                        }

                        var updateStatusPatternB = '{"objectName":"updateisGreenBut","updateStatusisGreenPatternB": '+isGreenPatternB+'}'
                        console.log("updateStatusPatternB:", updateStatusPatternB);
                        qmlCommand(updateStatusPatternB);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }

                ToolButton {
                    id: patternButtonPhaseC
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: false
                    Layout.preferredWidth: 50
                    contentItem: Image {
                        width: 50
                        height: 50
                        source: isGreenPatternC ? "images/GreenButton2.png" : "images/grayButton.png"
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                    }
                    onClicked: {
                        isGreenPatternC = !isGreenPatternC;
                        console.log("isGreenPatternC:", isGreenPatternC);

                        if (isGreenPatternC) {
                            //                              controlAndMonitor.replotPatternC();
                            reloadTaggingData()
                        } else {
                            //                              controlAndMonitor.hiddingGraphPatternPhaseC();
                            reloadTaggingData()
                        }

                        var updateStatusPatternC = '{"objectName":"updateisGreenBut","updateStatusisGreenPatternC": '+isGreenPatternC+'}'
                        console.log("updateStatusPatternC:", updateStatusPatternC);
                        qmlCommand(updateStatusPatternC);
                    }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }

            ColumnLayout {
                id: fulldistance

                RowLayout {

                    Text {
                        id: phasetext1
                        text: qsTr("DISTANCE(KM)")
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        Layout.preferredHeight: 40
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: fullDistance3Phaseframe
                        color: "#ffffff"
                        radius: 5
                        border.color: "#a6a6a6"
                        border.width: 2
                        Layout.bottomMargin: 5
                        Layout.topMargin: 5
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Text {
                            id: fullDistance3Phasetext
                            x: 0
                            y: 0
                            width: 70
                            height: 30
                            text: fullDistance3Phase.toFixed(2) + "Km"
                            font.pixelSize: 13
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        Layout.preferredHeight: 34
                        Layout.preferredWidth: 77
                    }
                }

                Rectangle {
                    id: firstPhaseData
                    color: "#ffffff"
                    radius: 5
                    border.color: "#a6a6a6"
                    border.width: 2
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: distancephase1
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: fullDistanceA.toFixed(2)
                        font.pixelSize: 13
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                }

                Rectangle {
                    id: secondPhaseData
                    color: "#ffffff"
                    radius: 5
                    border.color: "#a6a6a6"
                    border.width: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: distancephase2
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: fullDistanceB.toFixed(2)
                        font.pixelSize: 13
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
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: distancephase3
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: fullDistanceC.toFixed(2)
                        font.pixelSize: 13
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            ColumnLayout {
                height: 187
                Layout.fillWidth: false
                Layout.preferredHeight: 190
                visible: !(currentUserLevel === 3)
                Text {
                    id: phasetext2
                    height: 40
                    text: ""
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                }

                Rectangle {
                    id: firstPhaseVoltage
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    //                    visible: !(currentUserLevel === 3)
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Component.onCompleted: {
                        console.log("userLevelGlobalVars:", currentUserLevel)
                    }

                    Text {
                        id: vlotagephase1
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: contorlAndMonitor.positionOfVoltageA || "0.00 mV"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                    }
                }


                Rectangle {
                    id: secondPhaseVoltage
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    //                    visible: !(userLevelGlobalVars.get(0).userLevel === 3)
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: vlotagephase2
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: contorlAndMonitor.positionOfVoltageB || "0.00 mV"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }


                Rectangle {
                    id: thirdPhaseVoltage
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                    visible: !(currentUserLevel === 3)
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: vlotagephase3
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: contorlAndMonitor.positionOfVoltageC || "0.00 mV"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

            }


            ColumnLayout {
                Layout.preferredHeight: 190
                Layout.preferredWidth: 19
                visible: !(currentUserLevel === 3)

                Text {
                    id: phasetext3
                    text: qsTr("")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                }

                Text {
                    id: unitmVlotage1
                    text: qsTr("mV")
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                }

                Text {
                    id: unitmVlotage2
                    text: qsTr("mV")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                }

                Text {
                    id: unitmVlotage3
                    text: qsTr("mV")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                }
            }


            ColumnLayout {
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.preferredHeight: 180

                Text {
                    id: structurenum
                    x: 502
                    y: 39
                    text: qsTr("STRUCTURE NO")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    Layout.preferredHeight: 40
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    Layout.fillWidth: true
                    Layout.margins: 0
                    Layout.leftMargin: 0
                    Layout.preferredWidth: -1
                }
                Rectangle {
                    id: strucNo1
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.bottomMargin: 5
                    Layout.topMargin: 5
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: textstrucNo1
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: "0/0" ? transmissionLineA : "0/0"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Rectangle {
                    id: strucNo2
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: textstrucNo2
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: "0/0" ? transmissionLineB : "0/0"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Rectangle {
                    id: strucNo3
                    color: "#e7e6e6"
                    radius: 5
                    border.color: "#ffffff"
                    border.width: 2
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 70
                    Text {
                        id: textstrucNo3
                        x: 0
                        y: 0
                        width: 70
                        height: 30
                        text: "0/0" ? transmissionLineC : "0/0"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/
