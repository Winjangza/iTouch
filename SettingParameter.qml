import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

Item {
    width: 1000
    height: 475
    property bool focustextInformation: inputPanel.visible
    property string textforinformation:  textInformation.text
    onFocustextInformationChanged: {
        if(focustextInformation == false){
            textPhaseA.color = "#000000"
            textPhaseB.color = "#000000"
            textPhaseC.color = "#000000"
        }
    }
    onTextforinformationChanged: {
        if(textPhaseA.color == "#ff0000"){
            textPhaseA.text = textforinformation
        }
        if(textPhaseB.color == "#ff0000"){
            textPhaseB.text = textforinformation
        }
        if(textPhaseC.color == "#ff0000"){
            textPhaseC.text = textforinformation
        }
        console.log("onTextforinformationChanged",textforinformation)
    }

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
            x: 8
            y: 147
            width: 984
            height: 305

            ParameterPhaseA {
                id: parameterPhaseA
                Layout.fillWidth: true
                Layout.preferredHeight: 305
                Layout.preferredWidth: 275
            }

            ParameterPhaseB {
                id: parameterPhaseB
                Layout.fillWidth: true
                Layout.preferredHeight: 305
                Layout.preferredWidth: 283
            }

            ParameterPhaseC {
                id: parameterPhaseC
                Layout.fillWidth: true
                Layout.preferredHeight: 299
                Layout.preferredWidth: 291
            }
        }

        RowLayout {
            x: 61
            y: 57
            width: 926
            height: 40

            RowLayout {

                Text {
                    id: phaseA
                    text: qsTr("PHASE A")
                    font.pixelSize: 16
                }

                TextField {
                    id: textPhaseA
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 120
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    placeholderText: qsTr("Text Field") ? valueThresholdA : qsTr("Text Field")
                    focus: false
                    onFocusChanged: {
                        if (focus) {
                            textPhaseA.focus = false
                            currentField = "textPhaseA";
                            inputPanel.visible = true;
                            textInformation.visible = true;
                            textInformation.placeholderText = qsTr("Enter textPhaseA");
                            textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                            textInformation.text = "";
                            textInformation.focus = true;
                            textPhaseA.color = "#ff0000"
                        }
                    }
                }

                Text {
                    id: unitPhaseA
                    text: qsTr("mV")
                    font.pixelSize: 16
                }
            }

            RowLayout {

                Text {
                    id: phaseB
                    text: qsTr("PHASE B")
                    font.pixelSize: 16
                }

                TextField {
                    id: textPhaseB
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 120
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    placeholderText: qsTr("Text Field") ?valueThresholdB : qsTr("Text Field")
                    focus: false
                    onFocusChanged: {
                        if (focus) {
                            textPhaseB.focus = false
                            currentField = "textPhaseB";
                            inputPanel.visible = true;
                            textInformation.visible = true;
                            textInformation.placeholderText = qsTr("Enter textPhaseB");
                            textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                            textInformation.text = "";
                            textInformation.focus = true;
                            textPhaseB.color = "#ff0000"
                        }
                    }
                }

                Text {
                    id: unitPhaseB
                    text: qsTr("mV")
                    font.pixelSize: 16
                }
            }

            RowLayout {

                Text {
                    id: phaseC
                    text: qsTr("PHASE C")
                    font.pixelSize: 16
                }

                TextField {
                    id: textPhaseC
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 120
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    placeholderText: qsTr("Text Field")? valueThresholdC :qsTr("Text Field")
                    focus: false
                    onFocusChanged: {
                        if (focus) {
                            textPhaseC.focus = false
                            currentField = "textPhaseC";
                            inputPanel.visible = true;
                            textInformation.visible = true;
                            textInformation.placeholderText = qsTr("Enter textPhaseC");
                            textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                            textInformation.text = "";
                            textInformation.focus = true;
                            textPhaseC.color = "#ff0000"
                        }
                    }
                }

                Text {
                    id: unitPhaseC
                    text: qsTr("mV")
                    font.pixelSize: 16
                }
            }
        }
    }


}
