import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Styles 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
Item {
    width: 1000
    height: 475
    property string currentField: ""
    property bool focustextInformation: inputPanel.visible
    property string textforinformation:  textInformation.text
    property string ip_address_Network: ip_address
    property string ip_gateway_Network: ip_gateway
    property string ip_snmp_Network: ip_snmp
    property string ip_timeserver_Network: ip_timeserver
    property string ip_address_Display: ipAddressOfiTouch
    property string ip_gateway_Display: ipGatewatOfiTouch
    property string lastSwVersion: swversionupdate

    onFocustextInformationChanged: {
        if(focustextInformation == false){
            editsSNMPServer.color = "#000000"
            editTimeSyncServer.color = "#000000"
            settingIPaddress.color = "#000000"
            settinggateway.color = "#000000"
            settingIPaddressDisplay.color = "#000000"
            settinggatewayDisplay.color = "#000000"
        }
    }
    onTextforinformationChanged: {
        if(editsSNMPServer.color == "#ff0000"){
            editsSNMPServer.text = textforinformation
        }
        if(editTimeSyncServer.color == "#ff0000"){
            editTimeSyncServer.text = textforinformation
        }
        if(settingIPaddress.color == "#ff0000"){
            settingIPaddress.text = textforinformation
        }
        if(settinggateway.color == "#ff0000"){
            settinggateway.text = textforinformation
        }
        if(settingIPaddressDisplay.color == "#ff0000"){
            settingIPaddressDisplay.text = textforinformation
        }
        if(settinggatewayDisplay.color == "#ff0000"){
            settinggatewayDisplay.text = textforinformation
        }
        console.log("onTextforinformationChanged",textforinformation)
    }
    Rectangle {
        id: rectangle
        color: "#f2f2f2"
        anchors.fill: parent

        Text {
            id: text7
            x: 0
            y: 330
            text: qsTr("SNMP SERVER IP")
            font.pixelSize: 13
        }

        Text {
            id: text8
            x: 0
            y: 400
            text: qsTr("TIME SYCHONIZATION SERVER")
            font.pixelSize: 13
        }

        RowLayout {
            x: 84
            y: 350
            width: 430
            height: 45

            TextField {
                id: currentSNMP
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                placeholderText: qsTr("Current SNMP Server")
                text: ip_snmp_Network
                readOnly: true
                color: "#ffffff"
                background: Rectangle {
                    color: "#bcbcbc"
                    border.color: "#f7f7f7"
                    radius: 5
                }
            }

            TextField {
                id: editsSNMPServer
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true

                placeholderText: qsTr("Edit SNMP Server")
                focus: false

                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1

                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"

                background: Rectangle {
                    color: editsSNMPServer.readOnly ? "#d3d3d3" : "#ffffff"
                    border.color: "#bcbcbc"
                    radius: 5
                }

                onTextChanged: {
                    currentSNMP.text = text
                }

                onFocusChanged: {
                    if (focus && !editsSNMPServer.readOnly) {
                        editsSNMPServer.focus = false;
                        currentField = "editsSNMPServer";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter SNMP Server Address");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        editsSNMPServer.color = "#ff0000";
                    }
                }
            }


            ToolButton {
                id: setSNMPServerIP
                text: qsTr("SET")
                font.pointSize: 9
                Layout.preferredHeight: 35
                onClicked: {
                    var setSNMPData = '{"objectName":"editSetSNMPServerIP", "editsSNMPServer":"'+editsSNMPServer.text+'"}';
                    console.log(setSNMPData)
                    qmlCommand(setSNMPData);

                }
            }
        }

        RowLayout {
            x: 84
            y: 420
            width: 430
            height: 46

            TextField {
                id: currentTimeSyncServer
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                placeholderText: qsTr("Current Time Sync Server")
                text: ip_timeserver_Network
                readOnly: true
                color: "#ffffff"
                background: Rectangle {
                    color: "#bcbcbc"
                    border.color: "#f7f7f7"
                    radius: 5
                }
            }

            TextField {
                id: editTimeSyncServer
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                focus: false

                placeholderText: qsTr("Edit Time Sync Server")

                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1

                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"

                background: Rectangle {
                    color: editTimeSyncServer.readOnly ? "#d3d3d3" : "#ffffff"
                    border.color: "#bcbcbc"
                    radius: 5
                }

                onTextChanged: {
                    currentTimeSyncServer.text = text
                }

                onFocusChanged: {
                    if (focus && !editTimeSyncServer.readOnly) {
                        editTimeSyncServer.focus = false;
                        currentField = "editTimeSyncServer";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter Time Sync Server Address");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        editTimeSyncServer.color = "#ff0000";
                    }
                }
            }

            ToolButton {
                id: timesyncServer
                text: qsTr("SET")
                font.pointSize: 9
                Layout.preferredHeight: 35
                onClicked: {
                    var setTimeServerData = '{"objectName":"editTimesyncServer", "editsTimeSyncServer":"'+editTimeSyncServer.text+'"}';
                    console.log(setTimeServerData);
                    qmlCommand(setTimeServerData);

                }
            }
        }

        SNMPtraps {
            id: sNMPtraps
            x: 570
            y: 8
            width: 422
            height: 460
        }

        ToolButton {
            id: setIPandGateway
            x: 516
            y: 135
            width: 52
            height: 40
            text: qsTr("SET")
            font.pointSize: 12
            Layout.preferredHeight: 35
            onClicked: {
                var setIPAddressGateway = '{"objectName":"editSettingNetwork", "editsIPAddress":"'+settingIPaddress.text+'", "editsGateWays":"'+settinggateway.text+'"}';
                console.log(setIPAddressGateway)
                qmlCommand(setIPAddressGateway)
            }
            Layout.fillWidth: false
        }

        Text {
            id: text1
            x: 8
            y: 14
            text: qsTr("NETWORK SETTING")
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            Layout.bottomMargin: -293
        }

        Text {
            id: text6
            x: 8
            y: 305
            text: qsTr("SNMP SETTING")
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            Layout.bottomMargin: -16
        }

        ToolButton {
            id: setIPandGatewayDisplay
            x: 516
            y: 234
            width: 52
            height: 41
            text: qsTr("SET")
            font.pointSize: 12
            Layout.preferredHeight: 35
            Layout.fillWidth: false
            onClicked: {
                var setIPAddressGatewayDisplay = '{"objectName":"setIPAddressGatewayDisplay", "editsIPAddressDisplay":"'+settingIPaddressDisplay.text+'", "editsGateWaysDisplay":"'+settinggatewayDisplay.text+'"}';
                console.log("QMLsetIPAddressGatewayDisplay:", setIPAddressGatewayDisplay)
                qmlCommand(setIPAddressGatewayDisplay)
            }
        }

        ColumnLayout {
            x: 143
            y: 50
            width: 192
            height: 214

            Text {
                id: text2
                text: qsTr("CURRENT")
                font.pixelSize: 13
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: false
                Layout.fillWidth: true
            }

            TextField {
                id: currentIPaddress
                color: "#ffffff"
                text: ip_address_Network
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                readOnly: true
                Layout.preferredHeight: 40
                background: Rectangle {
                    color: "#bcbcbc"
                    radius: 5
                    border.color: "#f7f7f7"
                }
                Layout.fillWidth: true
                placeholderText: qsTr("Current IP Address")
            }


            TextField {
                id: currentgateway
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                placeholderText: qsTr("Current GateWay")
                text: ip_gateway_Network
                readOnly: true
                color: "#ffffff"
                background: Rectangle {
                    color: "#bcbcbc"
                    radius: 5
                    border.color: "#f7f7f7"
                }
            }


            TextField {
                id: currentIPaddressDisplay
                color: "#ffffff"
                text: ip_address_Display
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                readOnly: true
                Layout.preferredHeight: 40
                background: Rectangle {
                    color: "#bcbcbc"
                    radius: 5
                    border.color: "#f7f7f7"
                }
                Layout.fillWidth: true
                placeholderText: qsTr("Current IP Address")
            }


            TextField {
                id: currentgateway1
                color: "#ffffff"
                text: ip_gateway_Display
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                readOnly: true
                Layout.preferredHeight: 40
                background: Rectangle {
                    color: "#bcbcbc"
                    radius: 5
                    border.color: "#f7f7f7"
                }
                Layout.fillWidth: true
                placeholderText: qsTr("Current GateWay")
            }

        }

        ColumnLayout {
            x: 341
            y: 50
            width: 173
            height: 214


            Text {
                id: text4
                text: qsTr("SETTING")
                font.pixelSize: 13
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: true
            }

            TextField {
                id: settingIPaddress
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                focus: false
                placeholderText: qsTr("Setting IP")

                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1

                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"

                background: Rectangle {
                    color: settingIPaddress.readOnly ? "#d3d3d3" : "#ffffff"
                    border.color: "#bcbcbc"
                    radius: 5
                }

                onTextChanged: {
                    currentIPaddress.text = text
                }

                onFocusChanged: {
                    if (focus && !settingIPaddress.readOnly) {
                        settingIPaddress.focus = false;
                        currentField = "settingIPaddress";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter IP address");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        settingIPaddress.color = "#ff0000";
                    }
                }
            }


            TextField {
                id: settinggateway
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                Layout.preferredWidth: 148
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                focus: false
                placeholderText: qsTr("Setting GateWays")

                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1

                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"

                background: Rectangle {
                    color: settinggateway.readOnly ? "#d3d3d3" : "#ffffff"
                    border.color: "#bcbcbc"
                    radius: 5
                }

                onTextChanged: {
                    currentgateway.text = text
                }

                onFocusChanged: {
                    if (focus && !settinggateway.readOnly) {
                        settinggateway.focus = false;
                        currentField = "settinggateway";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter GateWays");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        settinggateway.color = "#ff0000";
                    }
                }
            }


            TextField {
                id: settingIPaddressDisplay
                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1
                focus: false
                onFocusChanged: {
                    if (focus && !settingIPaddressDisplay.readOnly) {
                        settingIPaddressDisplay.focus = false;
                        currentField = "settingIPaddressDisplay";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter IP Display Address");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        settingIPaddressDisplay.color = "#ff0000";
                    }
                }
                Layout.preferredHeight: 40
                Layout.preferredWidth: 148
                background: Rectangle {
                    color: settingIPaddressDisplay.readOnly ? "#d3d3d3" : "#ffffff"
                    radius: 5
                    border.color: "#bcbcbc"
                }
                Layout.fillWidth: true
                onTextChanged: {
                    currentIPaddressDisplay.text = text
                }
                placeholderText: qsTr("IP Display Address")
            }


            TextField {
                id: settinggatewayDisplay
                color: (userLevelGlobalVars.count > 0 &&
                        userLevelGlobalVars.get(0).userLevel !== 1)
                       ? "#808080" : "#000000"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 10
                readOnly: userLevelGlobalVars.count === 0 ||
                          userLevelGlobalVars.get(0).userLevel !== 1
                focus: false
                onFocusChanged: {
                    if (focus && !settinggatewayDisplay.readOnly) {
                        settinggatewayDisplay.focus = false;
                        currentField = "settinggatewayDisplay";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.placeholderText = qsTr("Enter GateWays DIsplay");
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.text = "";
                        textInformation.focus = true;
                        settinggatewayDisplay.color = "#ff0000";
                    }
                }
                Layout.preferredHeight: 40
                Layout.preferredWidth: 148
                background: Rectangle {
                    color: settinggatewayDisplay.readOnly ? "#d3d3d3" : "#ffffff"
                    radius: 5
                    border.color: "#bcbcbc"
                }
                Layout.fillWidth: true
                onTextChanged: {
                    currentgateway1.text = text
                }
                placeholderText: qsTr("Setting GateWays Display")
            }

        }

        ColumnLayout {
            x: 0
            y: 68
            width: 137
            height: 196

            Text {
                id: ipAddress
                text: qsTr("IP ADDRESS PLC")
                font.pixelSize: 13
                Layout.fillWidth: true
            }

            Text {
                id: ipGateways
                text: qsTr("IP GATEWAY PLC")
                font.pixelSize: 13
                Layout.fillWidth: true
            }

            Text {
                id: ipAddressDisplay
                text: qsTr("IP ADDRESS DISPLAY ")
                font.pixelSize: 13
                Layout.fillWidth: true
            }

            Text {
                id: ipGatewaysDisplay
                text: qsTr("IP GATEWAY DISPLAY")
                font.pixelSize: 13
                Layout.fillWidth: true
            }
        }

        Button {
            id: button
            x: 0
            y: 270
            width: 335
            height: 29
            text: qsTr("RESET  DEFAULT IP")
            onClicked: {
                var resetIP = '{"objectName":"resetDefalutIP","defalutip": "192.168.1.4","defalutgateways": "192.168.1.254","defalutnetmask": "255.255.255.0"}'
                qmlCommand(resetIP);
            }
        }

        RowLayout {
            x: 222
            y: 14
            width: 292
            height: 21

            Text {
                id: swversion
                text: qsTr("Software version:")
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.preferredHeight: 21
                Layout.preferredWidth: 104
            }

            Text {
                id: numberswversion
                text: lastSwVersion
                font.pixelSize: 14
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                Layout.preferredHeight: 21
                Layout.preferredWidth: 129
            }
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
