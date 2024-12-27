import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.15
import QtQuick3D.Effects 1.15
import QtQuick.Layouts 1.0
import QtWebSockets 1.0

Window {
    id: window
    width: 1024
    height: 600
    visible: true
    property string serverAddress: "127.0.0.1"
    property var socketPort: 1234
    property string socketUrl: "ws://"+ serverAddress + ":" + socketPort.toString()
    property bool sockStart: false
    property var objectName: []
    property string userTypeMaster: "MASTER"
    property string userTypeSlave: "SLAVE"
    property string mainBarMasterSelect
    property string mainBarSlaveSelect
    property string usertypeMaster:""
    property string usertypeSlave:""
    property bool usertypeSelect
    property bool usertypeSelectMaster: true
    property bool usertypeSelectSlave: false
    property string currentUserType: userTypeMaster
    signal qmlCommand(string msg)
    property string currentField: ""
    signal updateField(string fieldName, string value)
    property string datetime: ""
    property string textforInformation: textInformation.text
    property bool status
    property int number: 0
    property double distance: 0
    property string detail: ""
    property string phase: ""
    property bool checkedStates: false

    ListModel {
        id:newlistdatateble
        property bool list_status: false
        property int list_number: 0
        property double list_distance: 0
        property string list_detail: ""
        property string list_phase: ""
    }
    color: "#f2f2f2"
    title: qsTr("Hello World")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "qrc:/Mainpage.qml"
    }

    MainBar {
        id: mainBar
        x: 0
        y: 0
    }
    function setpropertyCheck(check){
        console.log("setpropertyCheck",check)
        if(check === true){
            checkedStates = check
        }else if(check === false){
            checkedStates = check
        }
    }

    function qmlSubmitTextFiled(message){
        console.log("receviceSocket:", message);
        var JsonObject = JSON.parse(message);
        var objectName = JsonObject.objectName;

        if (objectName === "UserSelectM") {
            mainBarMasterSelect = userTypeMaster;
            usertypeSelect = JsonObject.userStatusMaster
        }
        else if (objectName === "UserSelectS") {
            mainBarSlaveSelect = userTypeSlave;
            usertypeSelect = !JsonObject.userStatusSlave
        }else if (objectName === "DateTime") {
            datetime = JsonObject.formattedDateTime
        }else if (objectName === "getMySqlPhase") {
            status = JsonObject.status;
            number = JsonObject.temp_no;
            distance = JsonObject.Distance;
            detail = JsonObject.Detail;
            phase = JsonObject.Phase;
            console.log("getMySqlPhase:", message);

            appendNewDataTable(message)
        }else if(objectName === 'deletedcommand'){
            commandID = JsonObject.list_deviceID
            console.log("command from monitor",message , commandID)
            deletedCommand(message)
        }

    }

    function appendNewDataTable(message) {
        console.log("debug_for_mysqlTable", message);
        var JsonObject = JSON.parse(message)
        var commandName = JsonObject.objectName
        var selectStatus =JsonObject.status;
        var numberPhase =JsonObject.temp_no;
        var distancePhase = JsonObject.Distance;
        var detailPhase = JsonObject.Detail;
        var tablePhase = JsonObject.Phase;
        var getdeviceIndex = getDeviceIndex(numberPhase);
        if(getdeviceIndex === -1){
            if(tablePhase === "A"){
                newlistdatateble.append({
                    "list_status": selectStatus,
                    "list_number": numberPhase,
                    "list_distance": distancePhase,
                    "list_detail": detailPhase,
                    "list_phase": tablePhase
                });
                console.log("debug_new_data", message);
            }
        }
    }

    function getDeviceIndex(temp_no) {
        for (var i = 0; i < newlistdatateble.count; i++) {
            var currentDeviceId = newlistdatateble.get(i).list_number;
            if (currentDeviceId === temp_no || currentDeviceId === parseInt(temp_no)) {
                return i;
            }
        }
        console.log("getDeviceIndex", temp_no,currentDeviceId);

        return -1;
    }

    function deletedCommand(message){
        var JsonObject = JSON.parse(message);
            var commandName = JsonObject.objectName;
            if (commandName === "deletedcommand") {
                var deviceIDToDelete = JsonObject.list_deviceID;
                var deviceIndex = getDeviceIndex(deviceIDToDelete);
                if (deviceIndex !== -1) {
                    newlistdatateble.remove(deviceIndex);
                    console.log("Row with device ID", deviceIDToDelete, "deleted");
                } else {
                    console.log("No row found with device ID", deviceIDToDelete);
                }
            }
    }
    WebSocket {
        id: socketCPP
        url: "ws://127.0.0.1:1234"
        property bool checkuser: true

        onTextMessageReceived: {
            qmlSubmitTextFiled(message)
            if (message != ""){
                console.log("onTextMessageReceived",message);
            }
        }
        onStatusChanged: if (socketCPP.status == WebSocket.Error) {
                             console.log("socketCPP Error: " + socketCPP.errorString)
                         }
                         else if (socketCPP.status == WebSocket.Open)
                         {

                             console.log("socketCPP Hello World")
                             var selectUserType = '{"objectName":"UserSelectM","userType": "Master" ,"userStatusMaster": '+usertypeSelectMaster+'}'
                             qmlCommand(selectUserType);
                             var tableTaggingPhaseA = '{"objectName":"TaggingPhaseA", "tableTaggingPhaseA": "TaggingPhaseA"}'
                             qmlCommand(tableTaggingPhaseA);

                         }
                         else if (socketCPP.status == WebSocket.Closed)
                         {
                             console.log("Socket closed")
                             connectToCPPServer.running = true
                             connectToCPPServer.repeat = true
                             connectToCPPServer.start()
                             socketCPP.active = false
                         }
        active: false
    }

    function socketConnect() {
        if (socket.status === WebSocket.Open){
            connectToServer.running = false
            connectToServer.repeat = false
            connectToServer.stop()
        }else{
            sockStart=true
            console.log("Reconnecting....")
            if (socket.status === WebSocket.Error)
            {
                console.log("Error: " + socket.errorString)
            }
            else if (socket.status === WebSocket.Open)
            {
                console.log("Socket opened")
            }
            else if (socket.status === WebSocket.Closed)
            {
                console.log("Socket closed")
            }
        }
    }
    onSockStartChanged: {
        sockStart.active = !sockStart.active
        console.log("socket.active",socket.active)
    }
    Component.onCompleted: {
        console.log("Testing WebSocket connection...");
        socketCPP.active = true;
        console.log("status of socket",socketCPP.active);
        if (socketCPP.active === true){
            if (socketCPP.status === WebSocket.Open) {
                socketCPP.sendTextMessage("Test message from QML!");
            }
        }

    }

    InputPanel {
        id: inputPanel
        y: 369
        height: 231
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.leftMargin: 0

        Component.onCompleted: {
            visible = false;
            textInformation.visible = false;
        }

        onVisibleChanged: {
            textInformation.focus = true;
        }

        TextField {
            id: textInformation
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 320
            anchors.leftMargin: 0
            anchors.topMargin: -130
            placeholderText: qsTr("Text Field")
            visible: false
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            font.pointSize: 12
            Component.onCompleted: {
                focus = false;
            }

            Keys.onReturnPressed: {
                if (text.trim() !== "") {
                    console.log("Enter key pressed! Value:", currentField);
                    if (currentField === "valueVoltage") {
                        textInformation.text = text;
                        var Voltage = '{"objectName":"valueVoltage","Voltage": '+textInformation.text+'}'
                        qmlCommand(Voltage);
                        console.log("Voltage Entered:", text, Voltage);
                    } else if (currentField === "valueSubstation") {
                        textInformation.text = text;
                        var Substation = '{"objectName":"valueSubstation","Substation": '+textInformation.text+'}'
                        qmlCommand(Substation);
                        console.log("Substation Entered:", text,Substation);
                    } else if (currentField === "valueDirection") {
                        textInformation.text = text;
                        var Direction = '{"objectName":"valueDirection","Direction": '+textInformation.text+'}'
                        qmlCommand(Direction);
                        console.log("Direction Entered:", text,Direction);
                    } else if (currentField === "valueLineNo") {
                        textInformation.text = text;
                        var LineNo = '{"objectName":"valueLineNo","LineNo": '+textInformation.text+'}'
                        qmlCommand(LineNo);
                        console.log("Line No Entered:", text,LineNo);
                    } else if (currentField === "textTime") {
                        textInformation.text = text;
                        var Time = '{"objectName":"textTime","Time": '+textInformation.text+'}'
                        qmlCommand(Time);
                        console.log("Time Entered:", text,Time);
                    } else if (currentField === "distanceField") {
                        textInformation.text = text;
                        var Distance = '{"objectName":"distanceField","distanceField": '+textInformation.text+'}'
                        qmlCommand(Distance);
                        console.log("Distance Entered:", text, Distance);
                    } else if (currentField === "detailField") {
                        textInformation.text = text;
                        var Detail = '{"objectName":"detailField","detailField": '+textInformation.text+'}'
                        qmlCommand(Detail);
                        console.log("Detail Entered:", text,Detail);
                    } else if (currentField === "sagText") {
                        textInformation.text = text;
                        var Sag = '{"objectName":"sagText","sagText": '+textInformation.text+'}'
                        qmlCommand(Sag);
                        console.log("Sag Entered:", text, Sag);
                    } else if (currentField === "samplingText") {
                        textInformation.text = text;
                        var Sampling = '{"objectName":"samplingText","samplingText": '+textInformation.text+'}'
                        qmlCommand(Sampling);
                        console.log("Sampling Entered:", text,Sampling);
                    } else if (currentField === "distancetostartText") {
                        textInformation.text = text;
                        var distancetostart = '{"objectName":"distancetostartText","distancetostartText": '+textInformation.text+'}'
                        qmlCommand(distancetostart);
                        console.log("Dist. Start Entered:", text,distancetostart);
                    } else if (currentField === "distancetoshowText") {
                        textInformation.text = text;
                        var distancetoshow = '{"objectName":"distancetoshowText","distancetoshowText": '+textInformation.text+'}'
                        qmlCommand(distancetoshow);
                        console.log("Dist. Show Entered:", text,distancetoshow);
                    } else if (currentField === "fulldistanceText") {
                        textInformation.text = text;
                        var fulldistance = '{"objectName":"fulldistanceText","fulldistanceText": '+textInformation.text+'}'
                        qmlCommand(fulldistance);
                        console.log("Full Dist. Entered:", text,fulldistance);
                    } else if (currentField === "currentIPaddress") {
                        textInformation.text = text;
                        var IpAddress = '{"objectName":"currentIPaddress","currentIPaddress": '+textInformation.text+'}'
                        qmlCommand(IpAddress);
                        console.log("IpAddress Entered:", text, IpAddress);
                    } else if (currentField === "detailField") {
                        textInformation.text = text;
                        var Detail = '{"objectName":"detailField","detailField": '+textInformation.text+'}'
                        qmlCommand(Detail);
                        console.log("Sampling Entered:", text,Detail);
                    }
                }
                inputPanel.visible = false;
                visible = false;
            }
        }
    }



}




/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
