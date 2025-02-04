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
    width: 1024
    height: 600
    property string serverAddress: "127.0.0.1"
    property var socketPort: 1234
    property string socketUrl: "ws://"+ serverAddress + ":" + socketPort.toString()
    property bool sockStart: false
    property var objectName: []
    property string userTypeMaster: "MASTER"
    property string userTypeSlave: "SLAVE"
    property var keyboardLayout: inputPanel.keyboard.layout
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
    property bool isTableCleared: false;
    property double editDistanceA: 0
    property string editDetailA: ""
    property int listMarginA: 0
    property string marginA: ""
    property int valueMarginA: 0
    property string unitMaginA: ""
    property bool statusMaginA

    property double valueThresholdA: 0.0
    property double valueThresholdB: 0.0
    property double valueThresholdC: 0.0

    property double voltageInfo: 0.0
    property string substationInfo: ""
    property string directionInfo: ""
    property int linenoInfo: 0

    property double time: 0.0
    property bool updateMonday
    property bool updateTuesday
    property bool updateWednesday
    property bool updateThursday
    property bool updateFriday
    property bool updateSaturday
    property bool updateSunday
    property var distanceRawA: []
    property var voltageRawA: []
    property var distanceRawB: []
    property var voltageRawB: []
    property var distanceRawC: []
    property var voltageRawC: []
    property var distancePatternA: []
    property var voltagePatternA: []
    property var distancePatternB: []
    property var voltagePatternB: []
    property var distancePatternC: []
    property var voltagePatternC: []
    property var arr: []
    property string cursorposition: ""
    property double cursorleft: 0.0
    property double cursorright: 0.0
    property double updateNewDistance: 0.0
    property int taggingpointData: 0
    property string globalPhase: ""
    property bool globalStatus
    property int globalTempNum: 0
    property double globalDistance: 0.0
    property string globalDetail: ""
    property double positionX:0.0
    property double positionY:0.0
    property bool statusSystem
    property var dataPoinDatatA: []
    property var dataPointA: []  //var arrRawA
    property var arrRawA: []
    property var arrRawB: []
    property var arrRawC: []
    property var sagfactor
    property var sampling
    property var displayStart
    property var displayShow
    property var fulldistances

    ListModel {
        id:newlistdatatebleA
        property bool list_statusA: false
        property int list_numberA: 0
        property int num_listA: 0
        property double list_distanceA: 0.0
        property string list_detailA: ""
        property string list_phaseA: ""
    }
    ListModel {
        id:newlistdatatebleB
        property bool list_statusB: false
        property int list_numberB: 0
        property int num_listB: 0
        property double list_distanceB: 0.0
        property string list_detailB: ""
        property string list_phaseB: ""
    }
    ListModel {
        id:newlistdatatebleC
        property bool list_statusC: false
        property int list_numberC: 0
        property int num_listC: 0
        property double list_distanceC: 0.0
        property string list_detailC: ""
        property string list_phaseC: ""
    }

    ListModel {
        id:newlistMarginA
        property int listMarginA: 0
        property string marginA: ""
        property int valueMarginA: 0
        property string unitMaginA: ""
        property bool statusMaginA: false
    }
    //         property string globalPhaseA: ""
    //         property bool globalStatusA: false
    //         property int globalTempNumA: 0
    //         property double globalDistanceA: 0.0
    //         property string globalDetailA: ""
    //         property int globalPositionX: 0 // Add X
    //         property int globalPositionY: 0 // Add Y

    //    function getTaggingData(positionX,positiony,globalTempNum) {
    //        var JsonObject = JSON.parse(data);
    //        var commandName = JsonObject.objectName;
    //        var pointerX = positionX;
    //        var pointerY = positiony;
    //        var globalNum = globalTempNum;
    //    }
        // Instance of ControlAndMonitor

    ListModel {
         id: taggingA
         property var listofTagging: []
         property int globalTempNumA: 0
         property int globalPositionX: 0 // Add X
         property int globalPositionY: 0 // Add Y
     }

    function getTaggingData(positionX, positionY, globalTempNum) {
        var pointerX = positionX;
        var pointerY = positionY;
        var globalNum = globalTempNum;

        // Append data into the listofTagging property of taggingA
        taggingA.append({
            "globalTempNumA": globalNum,
            "globalPositionX": pointerX,
            "globalPositionY": pointerY
        });

        console.log("Tagging data sent:", positionX, positionY, globalTempNum);
    }


    color: "#f2f2f2"
    title: qsTr("Hello World")
    StackView {
        id: stackView
        anchors.fill: parent
        anchors.topMargin: 0
        anchors.rightMargin: 0
        initialItem: "qrc:/Mainpage.qml"
    }
    MainBar {
        id: mainBar
        x: 0
        y: 0
        width: 1024
        height: 52
    }

    function qmlSubmitTextFiled(message){
//        console.log("receviceSocket:", message);
        var JsonObject = JSON.parse(message);
        var objectName = JsonObject.objectName;
        if(message === true){
            statusSystem = message
//            console.log("receviceSocket:", message, statusSystem);
        }

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
            statusA = JsonObject.status;
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
            statusC = JsonObject.status;
            numberC = JsonObject.temp_no;
            num_listC = JsonObject.num_list;
            distanceC = JsonObject.Distance;
            detailC = JsonObject.Detail;
            phaseC = JsonObject.Phase;
            console.log("getMySqlPhaseC:", message);

            appendNewDataTableC(message)
        }else if (objectName === "updatedataTableA") {

            statusA = JsonObject.status;
            numberA = JsonObject.temp_no || 0;
            num_listA = JsonObject.num_list || 0;
            distanceA = JsonObject.Distance || 0.0;
            detailA = JsonObject.Detail || "";
            phaseA = JsonObject.Phase || "";
            console.log("refreshTableDataA:", message);

            refreshTableDataA(message);
        }else if (objectName === "updatedataTableB") {
            statusA = JsonObject.status !== undefined ? JsonObject.status : false;
            numberA = JsonObject.temp_no || 0;
            num_listA = JsonObject.num_list || 0;
            distanceA = JsonObject.Distance || 0.0;
            detailA = JsonObject.Detail || "";
            phaseA = JsonObject.Phase || "";

            console.log("updatedataTableB:", message);

            refreshTableDataB(message);
        }else if (objectName === "updatedataTableC") {
            statusC = JsonObject.status !== undefined ? JsonObject.status : false;
            numberC = JsonObject.temp_no || 0;
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
        }else if (objectName === 'editDataPhaseA') {
            console.log("editDataPhaseA", message);
            num_listA = JsonObject.IndexNum || 0;
            distanceA = JsonObject.Distance || 0.0;
            detailA = JsonObject.Detail || "";
            phaseA = JsonObject.Phase || "";
        }else if (objectName === 'marginCountA') {
            console.log("QMLmarginCountA:", message);
            listMarginA = JsonObject.no || 0;
            marginA = JsonObject.marginNo || "";
            valueMarginA = JsonObject.valueOfMargin || 0.0;
            unitMaginA = JsonObject.unit || "";
            appendNewMarginlistA(message);
        }else if (objectName === 'getThreshold') {
            console.log("getUpdateThreshold:", message);
            valueThresholdA = JsonObject.thresholdInitA || 0.0;
            valueThresholdB = JsonObject.thresholdInitB || 0.0;
            valueThresholdC = JsonObject.thresholdInitC || 0.0;
        }else if (objectName === 'getSettingInfo') {
            console.log("getSettingInfo:", message);
            voltageInfo = JsonObject.voltage || 0.0;
            substationInfo = JsonObject.substation || 0.0;
            directionInfo = JsonObject.direction || 0.0;
            linenoInfo = JsonObject.line_no || 0.0;
        }else if (objectName === 'getPeriodicInfo') {
            time = JsonObject.Time || 0.0;
            updateMonday = JsonObject.Monday;
            updateTuesday = JsonObject.Tuesday;
            updateWednesday = JsonObject.Wednesday;
            updateThursday = JsonObject.Thursday;
            updateFriday = JsonObject.Friday;
            updateSaturday = JsonObject.Saturday;
            updateSunday = JsonObject.Sunday;
            console.log("getPeriodicInfo:", message,updateMonday, updateTuesday, updateWednesday, JsonObject.Monday);
        }else if (objectName === 'dataPlotingA') {
            arrRawA = JsonObject.dataPlotingA || [];
            distanceRawA = JsonObject.distance;
            voltageRawA = JsonObject.voltage;
            console.log("Debug_RawdataA:", message , arrRawA, distanceRawA, voltageRawA);

//            if (Array.isArray(arrRawA) && arrRawA.length > 0) {
//                var distancesDataA = [];
//                var voltagesDataA = [];
//                for (var a = 0; a < arrRawA.length; a++) {
//                    var dataPoinDatatA = arrRawA[a];
//                    // ตรวจสอบว่า distance และ voltage มีค่าหรือไม่ (ไม่เป็น null หรือ undefined)
//                    if (dataPoinDatatA.distance != null && dataPoinDatatA['voltage '] != null) {
//                        distancesDataA.push(dataPoinDatatA.distance);
//                        voltagesDataA.push(dataPoinDatatA['voltage ']); // หากชื่อฟิลด์มีช่องว่างที่ท้าย
//                    }
//                }

//                // เก็บค่าที่ได้ไว้ในตัวแปร
//                distanceRawA = distancesDataA;
//                voltageRawA = voltagesDataA;

////                console.log("RawData array:", voltageRawA, distanceRawA);
//            } else {
//                console.log("RawData array is empty or invalid");
//            }
        }else if (objectName === 'dataPlotingB') {
            arrRawB = JsonObject.dataPlotingB || [];
            distanceRawB = JsonObject.distance;
            voltageRawB = JsonObject.voltage;
            console.log("Debug_RawdataA:", message , arrRawB, distanceRawB, voltageRawB);
//            console.log("RawdataB:", message);
//            var arrRawB = JsonObject.packageRawDataB || [];
//            if (arrRawB.length > 0) {
//                var distancesDataB = [];
//                var voltagesDataB = [];

//                for (var b = 0; b < arrRawB.length; b++) {
//                    var dataPoinDatatB = arrRawB[b];

//                    if (dataPoinDatatB.distance !== undefined && dataPoinDatatB.voltage !== undefined) {
//                        distancesDataB.push(dataPoinDatatB.distance);
//                        voltagesDataB.push(dataPoinDatatB.voltage);
//                    }
//                }
//                distanceRawB = distancesDataB;
//                voltageRawB = voltagesDataB; // เปลี่ยนจาก distancesDataB เป็น voltagesDataB
//            } else {
//                console.log("RawData array is empty or invalid");
//            }
        } else if (objectName === 'dataPlotingC') {
            console.log("RawdataC:", message);
            arrRawC = JsonObject.dataPlotingC || [];
            distanceRawC = JsonObject.distance;
            voltageRawC = JsonObject.voltage;
            console.log("Debug_RawdataA:", message , arrRawC, distanceRawC, voltageRawC);
//            var arrRawC = JsonObject.packageRawDataC || [];
//            if (arrRawC.length > 0) {
//                var distancesDataC = [];
//                var voltagesDataC = [];

//                for (var c = 0; c < arrRawC.length; c++) {
//                    var dataPoinDatatC = arrRawC[c]; // เปลี่ยนจาก arrRawB[c] เป็น arrRawC[c]

//                    if (dataPoinDatatC.distance !== undefined && dataPoinDatatC.voltage !== undefined) {
//                        distancesDataC.push(dataPoinDatatC.distance);
//                        voltagesDataC.push(dataPoinDatatC.voltage);
//                    }
//                }
//                distanceRawC = distancesDataC;
//                voltageRawC = voltagesDataC; // เปลี่ยนจาก distancesDataC เป็น voltagesDataC
//            } else {
//                console.log("RawData array is empty or invalid");
//            }

        }else if (objectName === 'patthernA') {
            console.log("patthernA_check_debug:", message);
            var arrA = JsonObject.data || [];
            if (arrA.length > 0) {
                var distancesA = [];
                var voltagesA = [];

                for (var i = 0; i < arrA.length; i++) {
                    dataPointA = arrA[i];

                    if (dataPointA.distance !== undefined && dataPointA.voltage !== undefined) {
                        distancesA.push(dataPointA.distance);
                        voltagesA.push(dataPointA.voltage);
                    }
                }
                distancePatternA = distancesA;
                voltagePatternA= voltagesA;
            } else {
                console.log("RawData array is empty or invalid");
            }
        }else if (objectName === 'patthernB') {
            console.log("patthernB_check_debug:", message);
            var arrB = JsonObject.data || [];
            if (arrB.length > 0) {
                var distancesB = [];
                var voltagesB = [];

                for (var j = 0; j < arrB.length; j++) {
                    var dataPointB = arrB[j];

                    if (dataPointB.distance !== undefined && dataPointB.voltage !== undefined) {
                        distancesB.push(dataPointB.distance);
                        voltagesB.push(dataPointB.voltage);
                    }
                }
                distancePatternB = distancesB;
                voltagePatternB = voltagesB;
            } else {
                console.log("RawData array is empty or invalid");
            }
        } else if (objectName === 'patthernC') {
            console.log("patthernC_check_debug:", message);
            var arrC = JsonObject.data || [];
            if (arrC.length > 0) {
                var distancesC = [];
                var voltagesC = [];

                for (var k = 0; k < arrC.length; k++) {
                    var dataPointC = arrC[k];

                    if (dataPointC.distance !== undefined && dataPointC.voltage !== undefined) {
                        distancesC.push(dataPointC.distance);
                        voltagesC.push(dataPointC.voltage);
                    }
                }
                distancePatternC = distancesC;
                voltagePatternC = voltagesC;
                console.log("Graph cleared successfully.", distancePatternC, voltagePatternC, arrC.length);
            } else {
                console.log("RawData array is empty or invalid");
            }
        }else if (objectName === 'clearpatternPhaseA') {
            console.log("Clear graph Phase A command received");
            distancePatternA = [];
            voltagePatternA = [];
        } else if (objectName === 'clearpatternPhaseB') {
            console.log("Clear graph Phase B command received");
            distancePatternB = [];
            voltagePatternB = [];
        } else if (objectName === 'clearpatternPhaseC') {
            console.log("Clear graph Phase C command received");
            distancePatternC = [];
            voltagePatternC = [];
        }else if (objectName === 'clearGraphDataPhaseA') {
            console.log("Clear graph Phase A command received");
            distanceRawA = [];
            voltageRawA = [];
        } else if (objectName === 'clearGraphDataPhaseB') {
            console.log("Clear graph Phase B command received");
            distanceRawB = [];
            voltageRawB = [];
        } else if (objectName === 'clearGraphDataPhaseC') {
            console.log("Clear graph Phase C command received");
            distanceRawC = [];
            voltageRawC = [];
        }else if (objectName === 'positonCursor') {
            console.log("positonCursor:", message, JsonObject.distance);
            cursorposition = parseFloat(JsonObject.distance).toFixed(2);
            console.log("Formatted position:", cursorposition);
        }else if (objectName === 'decreaseValue') {
            console.log("decreaseValue:", message, JsonObject.decreaseValue);
            cursorleft =  JsonObject.decreaseValue;
        }else if (objectName === 'increaseValue') {
            console.log("increaseValue:", message, JsonObject.increaseValue);
            cursorright =  JsonObject.increaseValue;
        }else if (objectName === 'updateCursor') {
            console.log("updateCursor:", message, JsonObject.distance);
            updateNewDistance =  JsonObject.distance;
        }else if (objectName === 'taggingdata') {
            console.log("taggingdata:", message, JsonObject.Distance, JsonObject.status, JsonObject.temp_no,JsonObject.Phase);
            globalPhase =  JsonObject.Phase;
            if(globalPhase = "A"){
                globalDistance = JsonObject.Distance;
                globalStatus = JsonObject.status;
                globalTempNum = JsonObject.temp_no;
                positionX = JsonObject.Distance;
                positionY = 150.00;
                getTaggingData(positionX,positionY,globalTempNum)
//                getTaggingData(message)
            }
        }else if (objectName === 'GetSettingDisplay') {
                sagfactor       = JsonObject.sagFactorInit;
                sampling        = JsonObject.samplingRateInit;
                displayStart    = JsonObject.distanceToStartInit;
                displayShow     = JsonObject.distanceToShowInit;
                fulldistances    = JsonObject.fulldistancesInit;
            console.log("displaySetting:", message, sagfactor, sampling, displayStart, displayShow, fulldistances);
        }
    }


    function setpropertyIDTableA(checkIDtable) {
        console.log("setpropertyCheckTable:", checkIDtable);

        clearAllProperties();

        if (checkIDtable !== 0) {
            newlistdatatebleA.num_listA = checkIDtable;
            console.log("setpropertyCheckTableA:", checkIDtable, newlistdatatebleA.num_listA);
        }
    }

    function taggingpoint(checklist,statuslist){
        console.log("taggingpoint",checklist, statuslist)
        var tagging = '{"objectName":"taggingdata", "checklist":'+checklist+', "statuslist":'+statuslist+'}';
        qmlCommand(tagging);
    }

    function setpropertyCheckA(check){
        console.log("setpropertyCheck",check)
        if(check === true){
            checkedStates = check
        }else if(check === false){
            checkedStates = check
        }
    }
    function setpropertyIDTableB(checkIDtable) {
        console.log("setpropertyCheckTable", checkIDtable);

        clearAllProperties();

        if (checkIDtable !== 0) {
            newlistdatatebleB.num_listB = checkIDtable;
            console.log("setpropertyCheckTableA:", checkIDtable, newlistdatatebleB.num_listB);
        }
    }

    function setpropertyCheckB(check){
        console.log("setpropertyCheck",check)
        if(check === true){
            checkedStates = check
        }else if(check === false){
            checkedStates = check
        }
    }


    function clearAllProperties() {
        console.log("Clearing all properties...");
        newlistdatatebleA.num_listA = 0;
        console.log("Cleared num_listA:", newlistdatatebleA.num_listA);
//        newlistdatatebleB.num_listB = 0;
//        console.log("Cleared num_listB:", newlistdatatebleB.num_listB);
//        newlistdatatebleC.num_listC = 0;
//        console.log("Cleared num_listC:", newlistdatatebleC.num_listC);
    }

    function refreshTableDataA(message) {
        console.log("debug_refresh_data_A", message);

        var JsonObject = JSON.parse(message);
        var commandName = JsonObject.objectName;
        var selectStatus = JsonObject.status;
        var numberPhase = JsonObject.temp_no;
        var distancePhase = JsonObject.Distance;
        var detailPhase = JsonObject.Detail;
        var tablePhase = JsonObject.Phase;
        var numberoflist = JsonObject.num_list;

        console.log("Type of distancePhase:", typeof distancePhase, "Value:", distancePhase);

        if (commandName === "updatedataTableA") {
            if (!isTableCleared) {
                newlistdatatebleA.clear();
                isTableCleared = true;
            }

            newlistdatatebleA.append({
                "list_statusA": selectStatus,
                "list_numberA": numberPhase,
                "num_listA": numberoflist,
                "list_distanceA": String(distancePhase), // Convert to string
                "list_detailA": detailPhase,
                "list_phaseA": tablePhase,
            });

        } else {
            console.warn("Invalid or unexpected `objectName` in JSON for Table A.");
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
                    "list_statusB": item.statusB || false,
                    "list_numberB": item.temp_noB || 0,
                    "list_distanceB": item.DistanceB || 0.0,
                    "list_detailB": item.DetailB || "",
                    "num_listB": item.num_listB || 0,
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

    function appendNewMarginlistA(message) {
          console.log("debug_for_MarginA", message);
          var JsonObject = JSON.parse(message);
          var commandName = JsonObject.objectName;
          var listMarginA = JsonObject.no;
          var numMarginA = JsonObject.marginNo;
          var valueMarginA = JsonObject.valueOfMargin;
          var unitMaginA = JsonObject.unit;

          console.log("Parsed JsonObject:", JsonObject,listMarginA);

          var getdeviceIndexA = getDeviceIndexA(listMarginA);

          if (getdeviceIndexA === -1) {
              console.log("Item not found, adding new item:", listMarginA,getdeviceIndexA);
              newlistMarginA.append({
                  "list_marginA": listMarginA,
                  "valueMarginA": numMarginA,
                  "unitMaginA": valueMarginA,
                  "statusMaginA": unitMaginA,
              });
          } else {
              console.log("Item found at index:", getdeviceIndexA,listMarginA);
              var existingIndexNum = newlistMarginA.get(getdeviceIndexA).listMarginA;
              if (String(existingIndexNum) !== String(listMarginA)) {
                  console.log("Updating item:", listMarginA);
                  newlistMarginA.append({
                       "list_marginA": listMarginA,
                       "valueMarginA": numMarginA,
                       "unitMaginA": valueMarginA,
                       "statusMaginA": unitMaginA,
                  });
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
//                console.log("onTextMessageReceived",message);
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
                                 var threshold = "getCurrentThreshold";
                                 qmlCommand(threshold);
                                 var settingInfo = "SettingGeneral";
                                 qmlCommand(settingInfo);
                                 var getpreiodicInfo = "getpreiodicInfo";
                                 qmlCommand(getpreiodicInfo);
//                                 var startPloting = '{"objectName":"startPloting", "threshold": 1500, "sagFactor": 0.983, "samplingRate": 10, "distanceToStart": 0, "distanceToShow": 8500}';
//                                 qmlCommand(startPloting);
//                                 var getDisplaySetting = "getDisplay";
//                                 qmlCommand(getDisplaySetting);
//                                 var getRawData=  "testRawData";
//                                 qmlCommand(getRawData);
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
            textInformation.focus = false;
        }

        onVisibleChanged: {
            if (inputPanel.visible && !textInformation.focus) {
                textInformation.focus = true;
            }
        }

        Connections {
            target: Qt.inputMethod
            function onVisibleChanged() {
                if (Qt.inputMethod.visible) {
                    console.log("Keyboard shown");
                    inputPanel.visible = true;
                    textInformation.visible = true;
                    if (!textInformation.focus) {
                        textInformation.focus = true;
                    }
                } else {
                    console.log("Keyboard hidden");
                    inputPanel.visible = false;
                    textInformation.visible = false;
                    textInformation.focus = false;
                }
            }
        }

        // TextField สำหรับพิมพ์ข้อความ
        TextField {
            id: textInformation
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 320
            anchors.leftMargin: 0
            anchors.topMargin: -130
            placeholderText: qsTr("Text Field")
            visible: false  // กำหนดให้เริ่มต้นซ่อน
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            font.pointSize: 12

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
                        var Time = '{"objectName":"updatetextTime","Time": '+textInformation.text+'}'
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
                    } else if (currentField === "settingIPaddress") {
                        textInformation.text = text;
                        var IpAddress = '{"objectName":"settingIPaddress","settingIPaddress": '+textInformation.text+'}'
//                        qmlCommand(IpAddress);
                        console.log("IpAddress Entered:", text, IpAddress);
                    } else if (currentField === "settinggateway") {
                        textInformation.text = text;
                        var GateWays = '{"objectName":"settinggateway","settinggateway": '+textInformation.text+'}'
//                        qmlCommand(GateWays);
                        console.log("IpAddress Entered:", text, IpAddress);
                    }else if (currentField === "detailField") {
                        textInformation.text = text;
//                        var Detail = '{"objectName":"detailField","detailField": ' + JSON.stringify(textInformation.text) + '}';
                        var Detail = '{"objectName":"detailField","detailField": ' + textInformation.text + '}';
//                        qmlCommand(Detail);
                        console.log("Detail Entered:", text, Detail);
                    }else if (currentField === "marginNumberA") {
                        textInformation.text = text;
                        var marginA = '{"objectName":"marginCountA", "valueMarginA":'+textInformation.text +', "PHASE": "A"}';
                        qmlCommand(marginA);
                        console.log("MarginNumberA Entered:", text, marginA);
                    }else if (currentField === "textPhaseA") {
                        textInformation.text = text;
                        var thresholdA = '{"objectName":"textPhaseA", "thresholdA":'+textInformation.text +', "PHASE": "A"}';
                        qmlCommand(thresholdA);
                        console.log("thresholdA Entered:", text, thresholdA);
                    }else if (currentField === "textPhaseB") {
                        textInformation.text = text;
                        var thresholdB = '{"objectName":"textPhaseB", "thresholdB":'+textInformation.text +', "PHASE": "B"}';
                        qmlCommand(thresholdB);
                        console.log("thresholdB Entered:", text, thresholdB);
                    }else if (currentField === "textPhaseC") {
                        textInformation.text = text;
                        var thresholdC = '{"objectName":"textPhaseC", "thresholdC":'+textInformation.text +', "PHASE": "C"}';
                        qmlCommand(thresholdC);
                        console.log("thresholdC Entered:", text, thresholdC);
                    }else if (currentField === "rangedistance") {
                        textInformation.text = text;
                        var range = '{"objectName":"rangedistance", "rangedistance":'+textInformation.text +'}';
                        qmlCommand(range);
                        console.log("range Entered:", text, range);
                    }else if (currentField === "textUserName") {
                        textInformation.text = text;
                        var User = '{"objectName":"UserName", "textUserName":'+textInformation.text +'}';
                        qmlCommand(User);
                        console.log("range Entered:", text, User);
                    }else if (currentField === "textPassword") {
                        textInformation.text = text;
                        var Password = '{"objectName":"Password", "textPassword":'+textInformation.text +'}';
                        qmlCommand(Password);
                        console.log("range Entered:", text, Password);
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
    D{i:0;formeditorZoom:0.75}
}
##^##*/
