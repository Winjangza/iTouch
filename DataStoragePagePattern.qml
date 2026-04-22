import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Styles 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import QtQuick.Controls 2.13
// import QtQuick.Controls.Material 2.4
import QtQuick.Shapes 1.15
import QtQuick.Controls.Material 2.4
// import "main.qml" as Globals

Item {
    id: _item
    width: 920
    height: 475
    // Material.theme: Material.Dark
    // Material.accent: "#E91E63"
    property bool focustextInformation: inputPanel.visible
    property string textforinformation:  textInformation.text

    property string selectedFilename: ""
    property string selectedEventDatetime: ""
    property var modelMarginA: null
    property var modelMarginB: null
    property var modelMarginC: null

    // visible: userLevelGlobalVars.count > 0 && (userLevelGlobalVars.get(0).userLevel >= 1 && userLevelGlobalVars.get(0).userLevel <= 3)
//    property int contorlAndMonitorPercentPlot: contorlAndMonitor.percentPlot
    property bool isEditableUser: userLevelGlobalVars.count > 0 &&
                                  (userLevelGlobalVars.get(0).userLevel === 1 || userLevelGlobalVars.get(0).userLevel === 2)
    property int percent: contorlAndMonitorPercentPlot
    function modelToArray(m) {
        const out = [];
        if (!m) return out;
        for (let i = 0; i < m.count; ++i) {
            // m.get(i) คืน object ของ roles ใน element นั้น ๆ (พร้อม stringify ได้)
            out.push(m.get(i));
        }
        return out;
    }
    onFocustextInformationChanged: {
        console.log("focustextInformation",focustextInformation)
        if(focustextInformation == false){
            fileNamePattern.color = "#000000"
        }
    }
    onTextforinformationChanged: {
        console.log("textforinformation",textforinformation)
        if(fileNamePattern.color == "#ff0000"){
            fileNamePattern.text = textforinformation
        }
//        console.log("onTextforinformationChanged",textforinformation)

    }


    // Column {
    //     anchors.top: progressContainer.bottom
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     spacing: 10

    //     Button {
    //         text: "Show ProgressBar"
    //         visible: !progressContainer.isVisible
    //         onClicked: progressContainer.isVisible = true
    //     }

    //     Button {
    //         text: "Hide ProgressBar"
    //         visible: progressContainer.isVisible
    //         onClicked: progressContainer.isVisible = false
    //     }
    // }



    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: rectangle
            color: "#00ffffff"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 386
            Layout.preferredHeight: 475

            Rectangle {
                id: progressContainer
                x: 59
                y: 42
                width: 243
                height: 42
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
                    color: "#3bc425"
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
            RowLayout {
                y: 90
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 8
                anchors.rightMargin: 8
                spacing: 1

                ToolButton {
                    id: toolButtonNew
                    text: qsTr("NEW")
                    Layout.preferredWidth: 85
                    Layout.preferredHeight: 47
                    Layout.fillWidth: true

                    visible: isEditableUser

                    onClicked: {
                        var ButtonpatternData = JSON.stringify({
                            objectName: "ButtonPattern",
                            category: "Pattern",
                            Onclicked: toolButtonNew.text,
                            filename: fileNamePattern.text
                        });
                        dataStoragePagePatternSearch.clearDatapattern();
                        dataStoragePagePatternSearch.clearTableRequested();
                        qmlCommand(ButtonpatternData);
                    }

                    contentItem: Image {
                        width: 40
                        height: 20
                        source: "images/button.png"

                        Text {
                            id: _text
                            text: qsTr("NEW")
                            anchors.fill: parent
                            font.pixelSize: 17
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

//                        Text {
//                            id: _text2
//                            text: qsTr("NEW")
//                            anchors.fill: parent
//                            font.pixelSize: 17
//                            horizontalAlignment: Text.AlignHCenter
//                            verticalAlignment: Text.AlignVCenter
//                        }
                    }
                }


                ToolButton {
                    id: toolButtonOpen
                    text: qsTr("OPEN")
                    Layout.preferredWidth: 85
                    Layout.preferredHeight: 47
                    Layout.fillWidth: true
                    visible: isEditableUser

                    onClicked: {
                        if (selectedFilename !== "" && selectedEventDatetime !== "") {
                            var ButtonpatternData = JSON.stringify({
                                objectName: "ButtonPattern",
                                category : "Pattern",
                                Onclicked: toolButtonOpen.text,
                                filename: selectedFilename,
                                event_datetime: selectedEventDatetime
                            });
                            qmlCommand(ButtonpatternData);
                        }
                    }

                    contentItem: Image {
                        width: 40
                        height: 20
                        source: "images/button.png"
                        Text {
                            id: _text1
                            text: qsTr("OPEN")
                            anchors.fill: parent
                            font.pixelSize: 17
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }


                ToolButton {
                    id: toolButtonSave
                    text: qsTr("SAVE")
                    Layout.preferredWidth: 85
                    Layout.preferredHeight: 47
                    Layout.fillWidth: true
                    visible: isEditableUser

                    onClicked: {
                        if (!selectedFilename || !selectedEventDatetime) {
                            console.warn("Missing filename or event_datetime");
                            return;
                        }

                        // แปลง ListModel -> Array ของ element objects
                        const toArray = (m) => {
                            const out = [];
                            if (!m) return out;
                            for (let i = 0; i < m.count; ++i) {
                                out.push(m.get(i));   // ได้ object ของ role ใน element นั้น พร้อม stringify ได้เลย
                            }
                            return out;
                        };

                        const payloadObj = {
                            objectName: "ButtonPattern",
                            category : "Pattern",
                            Onclicked: toolButtonSave.text,
                            filename: selectedFilename,
                            event_datetime: selectedEventDatetime,

                            // ถ้าคุณต้องการ “ใช้ค่าจำนวนจากตัวแปร” (amontOfMargin*) ก็ใช้ต่อไปได้
                            // ถ้าอยาก fallback เป็นจำนวน element จริงในโมเดล ให้ใช้ ?: แบบนี้
                            countMarginA: (typeof amontOfMarginA !== "undefined") ? amontOfMarginA : (newlistMarginA ? newlistMarginA.count : 0),
                            countMarginB: (typeof amontOfMarginB !== "undefined") ? amontOfMarginB : (newlistMarginB ? newlistMarginB.count : 0),
                            countMarginC: (typeof amontOfMarginC !== "undefined") ? amontOfMarginC : (newlistMarginC ? newlistMarginC.count : 0),

                            // ส่งรายการทุก element ในแต่ละโมเดล
                            marginAItems: toArray(newlistMarginA),
                            marginBItems: toArray(newlistMarginB),
                            marginCItems: toArray(newlistMarginC),

                            // ส่ง “property ระดับโมเดล” (ที่คุณประกาศไว้บน ListModel เอง) ด้วย
                            modelValueMarginA: newlistMarginA ? newlistMarginA.valueMarginA : 0,
                            modelValueMarginB: newlistMarginB ? newlistMarginB.valueMarginB : 0,
                            modelValueMarginC: newlistMarginC ? newlistMarginC.valueMarginC : 0
                        };

                        const ButtonpatternData = JSON.stringify(payloadObj);
                        dataStoragePagePatternSearch.clearTableRequested();
                        qmlCommand(ButtonpatternData);
                        console.log("ButtonpatternData:", ButtonpatternData);
                    }

                    contentItem: Image {
                        width: 40
                        height: 20
                        source: "images/button.png"
                        Text {
                            id: _text3
                            text: qsTr("SAVE")
                            anchors.fill: parent
                            font.pixelSize: 17
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }


                ToolButton {
                    id: toolButtonDelete
                    text: qsTr("DELETE")
                    Layout.preferredWidth: 85
                    Layout.preferredHeight: 47
                    Layout.fillWidth: true
                    visible: isEditableUser

                    onClicked: {
                        if (selectedFilename !== "" && selectedEventDatetime !== "") {
                            var ButtonpatternData = JSON.stringify({
                                objectName: "ButtonPattern",
                                category : "Pattern",
                                Onclicked: toolButtonDelete.text,
                                filename: selectedFilename,
                                event_datetime: selectedEventDatetime
                            });
                            dataStoragePagePatternSearch.clearTableRequested();
                            qmlCommand(ButtonpatternData);
                        }
                    }

                    contentItem: Image {
                        width: 40
                        height: 20
                        source: "images/button.png"
                        Text {
                            id: _text4
                            text: qsTr("DELETE")
                            anchors.fill: parent
                            font.pixelSize: 17
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

            TextField {
                id: fileNamePattern
                height: 40
                width: parent.width - 100
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 160
                focus: false
                font.pixelSize: 18
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                selectionColor: "#403e3e"
                hoverEnabled: false
                placeholderText: "File Name"
                placeholderTextColor: "#797676"
                color: "#000000"

                background: Rectangle {
                    radius: 8
                    color: "#F5F5F5"
                    border.color: "#000"
                    border.width: 2
                }

                onFocusChanged: {
                    if (focus) {
                        Qt.inputMethod.show();
                        fileNamePattern.background.border.color = "#000";
                        fileNamePattern.focus = false;
                        currentField = "newFileNamePattern";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.text = "";
                        textInformation.inputMethodHints = Qt.ImhPreferUppercase;
                        textInformation.focus = true;
                        fileNamePattern.color = "#ff0000";
                    }
                }
            }
        }
        DataStoragePagePatternSearch {
            id: dataStoragePagePatternSearch
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 530
            onRowSelected: (filename, event_datetime) => {
                selectedFilename = filename;
                selectedEventDatetime = event_datetime;
//                console.log("Selected:", selectedFilename, selectedEventDatetime);
            }
        }

    }
}





