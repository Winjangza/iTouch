import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Styles 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
Item {
    width: 920
    height: 475
    property string currentField: ""

    Rectangle {
        id: rectangle
        color: "#f2f2f2"
        anchors.fill: parent

        ColumnLayout {
            x: 15
            y: 79
            width: 499
            height: 96

            RowLayout {
                Layout.leftMargin: 120
                Layout.preferredHeight: 16
                Layout.preferredWidth: 301

                Text {
                    id: text2
                    text: qsTr("CURRENT")
                    font.pixelSize: 13
                    Layout.leftMargin: 30
                    Layout.fillHeight: false
                    Layout.fillWidth: false
                }

                Text {
                    id: text4
                    text: qsTr("SETTING")
                    font.pixelSize: 13
                    Layout.leftMargin: 100
                }
            }

            RowLayout {

                Text {
                    id: ipAddress
                    text: qsTr("IP ADDRESS")
                    font.pixelSize: 13
                    Layout.fillWidth: false
                }

                TextField {
                    id:currentIPaddress
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 35
                    placeholderText: qsTr("")
                    readOnly: true

                }

                TextField {
                    id: settingIPaddress
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 35
                    placeholderText: qsTr("Setting IP")
                    focus: false
                    onFocusChanged: {
                        if (focus) {
                            currentField = "settingIPaddress";
                            inputPanel.visible = true;
                            textInformation.visible = true;
                            textInformation.placeholderText = qsTr("Enter IP address");
                            textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                            textInformation.text = "";
                            textInformation.focus = true;
                        }
                    }
                }

                ToolButton {
                    id: toolButton
                    text: qsTr("SET")
                    font.pointSize: 9
                    Layout.fillWidth: false
                    Layout.preferredHeight: 35

                    onClicked: {
                       currentIPaddress.text = settingIPaddress.text
                    }
                }


            }

            RowLayout {

                Text {
                    id: ipGateways
                    text: qsTr("IP GATEWAY")
                    font.pixelSize: 13
                    Layout.fillWidth: false
                }

                TextField {
                    id: currentgateway
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 35
                    placeholderText: qsTr("Text Field")
                }

                TextField {
                    id: settinggateway
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredHeight: 35
                    placeholderText: qsTr("Setting GateWays")
                    onFocusChanged: {
                        if (focus) {
                            currentField = "settinggateway";
                            inputPanel.visible = true;
                            textInformation.visible = true;
                            textInformation.placeholderText = qsTr("Enter GateWays");
                            textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                            textInformation.text = "";
                            textInformation.focus = true;
                        }
                    }
                }

                ToolButton {
                    id: toolButton1
                    text: qsTr("SET")
                    font.pointSize: 9
                    Layout.fillWidth: false
                    Layout.preferredHeight: 35
                    onClicked: {
                       currentgateway.text = settinggateway.text
                    }
                }
            }
        }

        ColumnLayout {
            x: 8
            y: 0
            width: 126
            height: 475
            Layout.fillWidth: true

            Text {
                id: text1
                text: qsTr("NETWORK SETTING")
                font.pixelSize: 14
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                Layout.bottomMargin: -18
            }

            Text {
                id: text6
                text: qsTr("SNMP SETTING")
                font.pixelSize: 14
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                Layout.bottomMargin: 17
            }
        }

        Text {
            id: text7
            x: 8
            y: 282
            text: qsTr("SNMP SERVER IP")
            font.pixelSize: 12
        }

        Text {
            id: text8
            x: 8
            y: 372
            text: qsTr("TIME SYCHONIZATION SERVER")
            font.pixelSize: 12
        }

        RowLayout {
            x: 100
            y: 304
            width: 414
            height: 35

            TextField {
                id: textField
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                placeholderText: qsTr("Text Field")
            }

            TextField {
                id: textField1
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                placeholderText: qsTr("Text Field")
            }

            ToolButton {
                id: toolButton2
                text: qsTr("SET")
                font.pointSize: 9
                Layout.preferredHeight: 35
            }
        }

        RowLayout {
            x: 100
            y: 399
            width: 414
            height: 35

            TextField {
                id: textField2
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                placeholderText: qsTr("Text Field")
            }

            TextField {
                id: textField3
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                placeholderText: qsTr("Text Field")
            }

            ToolButton {
                id: toolButton3
                text: qsTr("SET")
                font.pointSize: 9
                Layout.preferredHeight: 35
            }
        }

        SNMPtraps {
            id: sNMPtraps
            x: 525
            y: 0
            width: 395
            height: 460
        }
    }


//    InputPanel {
//        id: inputPanel
//        y: 244
//        height: 232
//        visible: false
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.rightMargin: 0
//        anchors.leftMargin: 0

//        Component.onCompleted: {
//            visible = false;
//            textInformation.visible = false;
//        }

//        TextField {
//            id: textInformation
//            anchors.fill: parent
//            anchors.rightMargin: 0
//            anchors.bottomMargin: 285
//            anchors.leftMargin: 0
//            anchors.topMargin: -96
//            placeholderText: qsTr("Text Field")
//            visible: false
//            inputMethodHints: Qt.ImhFormattedNumbersOnly
//            font.pointSize: 12

//            Component.onCompleted: {
//                focus = false;
//            }

//            Keys.onReturnPressed: {
//                if (text.trim() !== "") {
//                    if (currentField === "currentIPaddress") {
//                        currentIPaddress.text = text;
//                        var IpAddress = '{"objectName":"currentIPaddress","currentIPaddress": '+currentIPaddress.text+'}'
//                        qmlCommand(IpAddress);
//                        console.log("Sag Entered:", text, IpAddress);
//                    } else if (currentField === "detailField") {
//                        detailField.text = text;
//                        var Detail = '{"objectName":"detailField","detailField": '+detailField.text+'}'
//                        qmlCommand(Detail);
//                        console.log("Sampling Entered:", text,Detail);
//                    }
//                }
//                inputPanel.visible = false;
//                visible = false;
//            }
//        }
//    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
