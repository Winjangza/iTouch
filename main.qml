import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.15
import QtQuick3D.Effects 1.15
import QtQuick.Layouts 1.0
import QtWebSockets 1.0

Window {
    id: window
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
    property bool statusA
    property int numberA: 0
    property int num_listA: 0
    property double distanceA: 0
    property string detailA: ""
    property string phaseA: ""
    property bool statusB
    property int numberB: 0
    property int num_listB: 0
    property double distanceB: 0
    property string detailB: ""
    property string phaseB: ""
    property bool statusC
    property int numberC: 0
    property int num_listC: 0
    property double distanceC: 0
    property string detailC: ""
    property string phaseC: ""
    property bool checkedStates: false
    property var listdatatebleA : []
    property var listdatatebleB : []
    property var listdatatebleC : []


    ListModel {
        id:newlistdatatebleA
        property bool list_statusA: false
        property int list_numberA: 0
        property int num_listA: 0
        property double li_st_distanceA: 0
        property string list_detailA: ""
        property string list_phaseA: ""
    }
    ListModel {
        id:newlistdatatebleB
        property bool list_statusB: false
        property int list_numberB: 0
        property int num_listB: 0
        property double li_st_distanceB: 0
        property string list_detailB: ""
        property string list_phaseB: ""
    }
    ListModel {
        id:newlistdatatebleC
        property bool list_statusC: false
        property int list_numberC: 0
        property int num_listC: 0
        property double li_st_distanceC: 0
        property string list_detailC: ""
        property string list_phaseC: ""
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

        }else if (objectName === "getMySqlPhaseA") {
            statusA = JsonObject.status; // แปลงเป็น bool
            numberA = JsonObject.temp_no;
            num_listA = JsonObject.num_list;
            distanceA = JsonObject.Distance;
            detailA = JsonObject.Detail;
            phaseA = JsonObject.Phase;
            console.log("getMySqlPhaseA:", message);

            appendNewDataTableA(message)
        }else if (objectName === "getMySqlPhaseB") {
            statusB = JsonObject.status; // แปลงเป็น bool
            numberB = JsonObject.temp_no;
            num_listB = JsonObject.num_list;
            distanceB = JsonObject.Distance;
            detailB = JsonObject.Detail;
            phaseB = JsonObject.Phase;
            console.log("getMySqlPhaseB:", message);

            appendNewDataTableB(message)
        }else if (objectName === "getMySqlPhaseC") {
            statusC = JsonObject.status; // แปลงเป็น bool
            numberC = JsonObject.temp_no;
            num_listC = JsonObject.num_list;
            distanceC = JsonObject.Distance;
            detailC = JsonObject.Detail;
            phaseC = JsonObject.Phase;
            console.log("getMySqlPhaseC:", message);

            appendNewDataTableC(message)
        }else if (objectName === "updatedataTableA") {
            // อ่านค่า JSON
            statusA = JsonObject.status; // Fallback to `false`
            numberA = JsonObject.temp_no || 0; // Fallback to `0`
            num_listA = JsonObject.num_list || 0;
            distanceA = JsonObject.Distance || 0.0;
            detailA = JsonObject.Detail || "";
            phaseA = JsonObject.Phase || "";

            console.log("updatedataTableA:", message);
            if (num_listA === 0 || distanceA === 0.0 || detailA === "" || phaseA === "") {
                console.warn("Data is incomplete. Skipping appendNewDataTableA:", {
                    num_listA,
                    distanceA,
                    detailA,
                    phaseA,
                });
                return; // หยุดการทำงานถ้าข้อมูลไม่สมบูรณ์
            }
            appendNewDataTableA(message);
        }else if (objectName === "updatedataTableB") {
            statusA = JsonObject.status !== undefined ? JsonObject.status : false; // Fallback to `false`
            numberA = JsonObject.temp_no || 0; // Fallback to `0`
            num_listA = JsonObject.num_list || 0;
            distanceA = JsonObject.Distance || 0.0;
            detailA = JsonObject.Detail || "";
            phaseA = JsonObject.Phase || "";

            console.log("updatedataTableB:", message);

            refreshTableDataB(message);
        }else if (objectName === "updatedataTableC") {
            statusC = JsonObject.status !== undefined ? JsonObject.status : false; // Fallback to `false`
            numberC = JsonObject.temp_no || 0; // Fallback to `0`
            num_listC = JsonObject.num_list || 0;
            distanceC = JsonObject.Distance || 0.0;
            detailC = JsonObject.Detail || "";
            phaseC = JsonObject.Phase || "";

            console.log("updatedataTableC:", message);

            refreshTableDataC(message);
        }else if(objectName === 'deletedcommand'){
            commandID = JsonObject.list_deviceID
            console.log("command from monitor",message , commandID)
            deletedCommand(message)
        }

    }

    function setpropertyIDTable(checkIDtable){
        console.log("setpropertyCheckTable",checkIDtable)
        if(checkIDtable !== 0){
            newlistdatatebleA.num_listA =checkIDtable
            console.log("setpropertyCheckTableA:",checkIDtable,newlistdatatebleA.num_listA)
            newlistdatatebleB.num_listB =checkIDtable
            console.log("setpropertyCheckTableB:",checkIDtable,newlistdatatebleB.num_listB)
            newlistdatatebleC.num_listC =checkIDtable
            console.log("setpropertyCheckTableC:",checkIDtable,newlistdatatebleC.num_listC)
        }
    }

    function refreshTableDataA(message) {
        console.log("debug_refresh_data_A", message);

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;

        if (commandName === "updatedataTableA") {
            var data = JsonObject.data || [JsonObject];
            var tempList = [];

            for (var i = 0; i < data.length; i++) {
                var item = data[i];

                tempList.push({
                    list_statusA: item.statusA || false,
                    list_numberA: item.temp_noA || 0,
                    list_distanceA: item.DistanceA || 0.0,
                    list_detailA: item.DetailA || "",
                    num_listA: item.num_listA || 0,
                });
            }

            for (var j = 0; j < tempList.length; j++) {
                newlistdatatebleA.append(tempList[j]);
            }
        } else {
            console.warn("Invalid or missing `data` property in JSON for Table A.");
        }
    }



    function refreshTableDataB(message) {
        console.log("debug_refresh_data_B", message);
        newlistdatatebleB.clear();

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;

        if (commandName === "updatedataTableB" && Array.isArray(JsonObject.data)) {
            for (var i = 0; i < JsonObject.data.length; i++) {
                var item = JsonObject.data[i];
                newlistdatatebleB.append({
                    "list_statusB": item.statusB || false,   // Fallback to false if undefined
                    "list_numberB": item.temp_noB || 0,      // Fallback to 0
                    "list_distanceB": item.DistanceB || 0.0, // Fallback to 0.0
                    "list_detailB": item.DetailB || "",      // Fallback to empty string
                    "num_listB": item.num_listB || 0,        // Fallback to 0
                });
            }
        } else {
            console.warn("Invalid or missing `data` property in JSON for Table B.");
        }
    }

    function refreshTableDataC(message) {
        console.log("debug_refresh_data_C", message);

        newlistdatatebleC.clear();

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;

        // Check if the command is to update Table C
        if (commandName === "updatedataTableC" && Array.isArray(JsonObject.data)) {
            for (var i = 0; i < JsonObject.data.length; i++) {
                var item = JsonObject.data[i];
                newlistdatatebleC.append({
                    "list_statusC": item.statusC || false,   // Fallback to false if undefined
                    "list_numberC": item.temp_noC || 0,      // Fallback to 0
                    "list_distanceC": item.DistanceC || 0.0, // Fallback to 0.0
                    "list_detailC": item.DetailC || "",      // Fallback to empty string
                    "num_listC": item.num_listC || 0,        // Fallback to 0
                });
            }
        } else {
            console.warn("Invalid or missing `data` property in JSON for Table C.");
        }
    }


    // function refreshTableData(message) {
    //     console.log("debug_refresh_data", message);

    //     newlistdatatebleA.clear();
    //     newlistdatatebleB.clear();
    //     newlistdatatebleC.clear();

    //     var JsonObject = JSON.parse(message); // Parse the JSON string
    //     var commandName = JsonObject.objectName;

    //     if (commandName === "updatedataTableA" && Array.isArray(JsonObject.data)) {
    //         for (var i = 0; i < JsonObject.data.length; i++) {
    //             var item = JsonObject.data[i];
    //             newlistdatatebleA.append({
    //                 "list_status": item.status || false, // Fallback to false if undefined
    //                 "list_number": item.temp_no || 0,   // Fallback to 0
    //                 "list_distance": item.Distance || 0.0, // Fallback to 0.0
    //                 "list_detail": item.Detail || "",  // Fallback to empty string
    //                 "num_list": item.num_list || 0,    // Fallback to 0
    //             });
    //         }
    //     } else {
    //         console.warn("Invalid or missing `data` property in JSON.");
    //     }
    // }

    function appendNewDataTableA(message) {
        console.log("debug_for_mysqlTable_A", message);

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;
        var selectStatus = JsonObject.status;
        var numberPhase = JsonObject.temp_no;
        var distancePhase = JsonObject.Distance;
        var detailPhase = JsonObject.Detail;
        var tablePhase = JsonObject.Phase;
        var numberoflist = JsonObject.num_list;

        console.log("Parsed JsonObject:", JsonObject,numberoflist);

        var getdeviceIndexA = getDeviceIndexA(numberoflist);

        if (getdeviceIndexA === -1) {
            console.log("Item not found, adding new item:", numberoflist,getdeviceIndexA);
            newlistdatatebleA.append({
                "list_statusA": selectStatus,
                "list_numberA": numberPhase,
                "num_listA": numberoflist,
                "list_distanceA": distancePhase,
                "list_detailA": detailPhase,
                "list_phaseA": tablePhase,
            });
        } else {
            console.log("Item found at index:", getdeviceIndexA);
            var existingIndexNum = newlistdatatebleA.get(getdeviceIndexA).num_listA;
            if (String(existingIndexNum) !== String(numberoflist)) {
                console.log("Updating item:", numberoflist);
                newlistdatatebleA.append({
                    "list_statusA": selectStatus,
                    "list_numberA": numberPhase,
                    "num_listA": numberoflist,
                    "list_distanceA": distancePhase,
                    "list_detailA": detailPhase,
                    "list_phaseA": tablePhase,
                });
            }
        }
    }
    function appendNewDataTableB(message) {
        console.log("debug_for_mysqlTable_B", message);

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;
        var selectStatus = JsonObject.status;
        var numberPhase = JsonObject.temp_no;
        var distancePhase = JsonObject.Distance;
        var detailPhase = JsonObject.Detail;
        var tablePhase = JsonObject.Phase;
        var numberoflist = JsonObject.num_list;

        if (commandName === "updateDataDisplay") {
            newlistdatatebleB.clear();
        } else {
            if (tablePhase === "B") {
                newlistdatatebleB.append({
                    "list_statusB": selectStatus,
                    "list_numberB": numberPhase,
                    "num_listB": numberoflist,
                    "list_distanceB": distancePhase,
                    "list_detailB": detailPhase,
                    "list_phaseB": tablePhase
                });
                console.log("debug_new_data_B", message, numberoflist);
            }
        }
    }

    function appendNewDataTableC(message) {
        console.log("debug_for_mysqlTable_C", message);

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;
        var selectStatus = JsonObject.status;
        var numberPhase = JsonObject.temp_no;
        var distancePhase = JsonObject.Distance;
        var detailPhase = JsonObject.Detail;
        var tablePhase = JsonObject.Phase;
        var numberoflist = JsonObject.num_list;

        if (commandName === "updateDataDisplay") {
            newlistdatatebleC.clear();
        } else {
            if (tablePhase === "C") {
                newlistdatatebleC.append({
                    "list_statusC": selectStatus,
                    "list_numberC": numberPhase,
                    "num_listC": numberoflist,
                    "list_distanceC": distancePhase,
                    "list_detailC": detailPhase,
                    "list_phaseC": tablePhase
                });
                console.log("debug_new_data_C", message, numberoflist);
            }
        }
    }


    // function appendNewDataTable(message) {
    //     console.log("debug_for_mysqlTable", message);

    //      var JsonObject = JSON.parse(message);
    //      var commandName = JsonObject.objectName;
    //      var selectStatus = JsonObject.status;
    //      var numberPhase = JsonObject.temp_no;
    //      var distancePhase = JsonObject.Distance;
    //      var detailPhase = JsonObject.Detail;
    //      var tablePhase = JsonObject.Phase;
    //      var numberoflist = JsonObject.num_list;
    //      var getdeviceIndexA = getDeviceIndexA(numberoflist);
    //      var getdeviceIndexB = getDeviceIndexB(numberoflist);
    //      var getdeviceIndexC = getDeviceIndexC(numberoflist);


    //     if (commandName === "updateDataDisplay") {
    //         JsonObject = null;
    //         commandName = null;
    //         selectStatus = null;
    //         numberPhase = null;
    //         distancePhase = null;
    //         detailPhase = null;
    //         tablePhase = null;
    //         numberoflist = null;
    //         getdeviceIndexA = null;
    //         getdeviceIndexB = null;
    //         getdeviceIndexC = null;
    //         newlistdatatebleA.clear();
    //         newlistdatatebleB.clear();
    //         newlistdatatebleC.clear();
    //     }

    //      if (getdeviceIndexA === -1) {
    //          if (tablePhase === "A") {
    //              newlistdatatebleA.append({
    //                  "list_status": selectStatus,
    //                  "list_number": numberPhase,
    //                  "num_list"   : numberoflist,
    //                  "list_distance": distancePhase,
    //                  "list_detail": detailPhase,
    //                  "list_phase": tablePhase
    //              });
    //              console.log("debug_new_data_A", message, numberoflist);
    //          }
    //      }else if (getdeviceIndexB === -1) {
    //          if (tablePhase === "B") {
    //              newlistdatatebleB.append({
    //                  "list_status": selectStatus,
    //                  "list_number": numberPhase,
    //                  "num_list"   : numberoflist,
    //                  "list_distance": distancePhase,
    //                  "list_detail": detailPhase,
    //                  "list_phase": tablePhase
    //              });
    //              console.log("debug_new_data_B", message, numberoflist);
    //          }
    //      }else if (getdeviceIndexC === -1) {
    //          if (tablePhase === "C") {
    //              newlistdatatebleC.append({
    //                  "list_status": selectStatus,
    //                  "list_number": numberPhase,
    //                  "num_list"   : numberoflist,
    //                  "list_distance": distancePhase,
    //                  "list_detail": detailPhase,
    //                  "list_phase": tablePhase
    //              });
    //              console.log("debug_new_data_C", message, numberoflist);
    //          }
    //      }
    // }


    function getDeviceIndexA(num_listA) {
        for (var i = 0; i < newlistdatatebleA.count; i++) {
            var currentItem = newlistdatatebleA.get(i);
            if (!currentItem) {
                console.warn("Item at index", i, "is undefined");
                continue;
            }

            var currentDeviceId = currentItem.num_listA;
            if (String(currentDeviceId) === String(num_listA)) {
                return i;
            }
        }
        console.log("getDeviceIndex_A - num_listA not found:", num_listA);
        return -1;
    }
    function getDeviceIndexB(num_listB) {
        for (var i = 0; i < newlistdatatebleB.count; i++) {
            var currentDeviceId = newlistdatatebleB.get(i).num_listB;
            if (currentDeviceId === num_listB || currentDeviceId === parseInt(num_listB)) {
                return i;
            }
        }
        console.log("getDeviceIndex_B", num_listB,currentDeviceId);
        return -1;
    }
    function getDeviceIndexC(num_listC) {
        for (var i = 0; i < newlistdatatebleC.count; i++) {
            var currentDeviceId = newlistdatatebleC.get(i).num_listC;
            if (currentDeviceId === num_listC || currentDeviceId === parseInt(num_listC)) {
                return i;
            }
        }
        console.log("getDeviceIndex_C", num_listC,currentDeviceId);
        return -1;
    }


    function deletedCommand(message){
        var JsonObject = JSON.parse(message);
            var commandName = JsonObject.objectName;
            if (commandName === "deletedcommand") {
                var deviceIDToDelete = JsonObject.num_list;
                var deviceIndex = getDeviceIndexA(deviceIDToDelete);
                if (deviceIndex !== -1) {
                    newlistdatatebleA.remove(deviceIndex);
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
                             let hasSentTaggingCommands = false;

                             console.log("socketCPP Hello World")
                             var selectUserType = '{"objectName":"UserSelectM","userType": "Master" ,"userStatusMaster": '+usertypeSelectMaster+'}'
                             qmlCommand(selectUserType);
                             if (socketCPP.status == WebSocket.Open && !hasSentTaggingCommands) {

                                 var tableTaggingPhaseA = '{"objectName":"TaggingPhaseA", "tableTaggingPhaseA": "TaggingPhaseA"}';
                                 qmlCommand(tableTaggingPhaseA);

                                 var tableTaggingPhaseB = '{"objectName":"TaggingPhaseB", "tableTaggingPhaseB": "TaggingPhaseB"}';
                                 qmlCommand(tableTaggingPhaseB);

                                 var tableTaggingPhaseC = '{"objectName":"TaggingPhaseC", "tableTaggingPhaseC": "TaggingPhaseC"}';
                                 qmlCommand(tableTaggingPhaseC);

                                 hasSentTaggingCommands = true;
                             }

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
