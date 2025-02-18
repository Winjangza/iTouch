import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.15
import QtQuick.VirtualKeyboard.Styles 2.15
import QtQuick.VirtualKeyboard.Settings 2.15
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4

Item {
    visible: true
    width: 1024
    height: 600

<<<<<<< HEAD


    TabView {
        x: 0
        y: 65
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.topMargin: 62

        Tab {
            title: "EVENT & ALARM"
            height: 10
            width: 20
            Flickable {
                id: flickable
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                Rectangle {
                    id: viewsLogEvent
                    color: "#e7e6e6"
                    border.color: "#ffffff"
                    anchors.fill: parent
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    TableView {
                        id: recordDatabase
                        anchors.fill: parent
                        anchors.rightMargin: 0
                        anchors.topMargin: 0
                        anchors.bottomMargin: 0
                        clip: true
                        model: eventAlarmLog
                        TableViewColumn { role: "datetEventandAlram"; title: "DATE"; width: 150;}
                        TableViewColumn { role: "timeEventandAlram"; title: "TIME"; width: 160 }
                        TableViewColumn { role: "logDetail"; title: "ALARM/EVENT"; width: 440 }
                        TableViewColumn { role: "statusEventandAlram"; title: "STATUS"; width: 300}
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
            }
        }
        Tab {
            title: "EVENT & ALARM \n HISTORY"
            Rectangle { color: "#e7e6e6" }
            Flickable {
                id: flickableHistory
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                Rectangle {
                    id: viewsLogEventHistory
                    color: "#e7e6e6"
                    border.color: "#ffffff"
                    anchors.fill: parent
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    TableView {
                        id: recordDatabaseHistory
                        anchors.fill: parent
                        anchors.rightMargin: 0
                        anchors.topMargin: 0
                        anchors.bottomMargin: 0
                        clip: true
                        model: eventAlarmHistoryLog
                        TableViewColumn { role: "datetEventandAlram"; title: "DATE"; width: 150;}
                        TableViewColumn { role: "timeEventandAlram"; title: "TIME"; width: 160 }
                        TableViewColumn { role: "logDetail"; title: "ALARM/EVENT"; width: 440 }
                        TableViewColumn { role: "statusEventandAlram"; title: "STATUS"; width: 300}
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
            }

        }
        style: TabViewStyle {
            tab: Rectangle {
                implicitWidth: 200
                implicitHeight: 65
                color: styleData.selected ? "white" : "#d3d3d3"
                border.color: "black"
                radius: 5
                Text {
                    text: styleData.title
                    anchors.centerIn: parent
//                    font.bold: true
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: styleData.selected ? "black" : "#555"
                }
            }
        }

    }
    Rectangle {
        id: rectangle
        x: 408
        y: 64
        width: 609
        height: 60
        color: "#e7e6e6"
        radius: 10
        border.width: 2
        Rectangle {
            id: filterCheck
            color: "#f2f2f2"
            radius: 5
            border.color: "#abaaaa"
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.topMargin: 16
            anchors.rightMargin: 562
            anchors.bottomMargin: 16
            property bool isActive: false

            MouseArea {
                anchors.fill: parent
                anchors.topMargin: 0
                anchors.rightMargin: 0
                onClicked: {
                    filterCheck.isActive = !filterCheck.isActive
                    filterCheck.color = filterCheck.isActive ? "#00FF00" : "#f2f2f2"
                    if (!filterCheck.isActive) {
                        fliterrelay.isActive = false
                        fliterrelay.color = "#f2f2f2"

                        fliterperiodics.isActive = false
                        fliterperiodics.color = "#f2f2f2"

                        flitermanual.isActive = false
                        flitermanual.color = "#f2f2f2"
=======
    property var eventAlarmData: [
        { date: "2021/07/22", time: "08:18:40", message: "ALARMS EQUIPMENT ERROR", priority: "A" },
        { date: "2021/07/23", time: "09:30:21", message: "TEMPERATURE HIGH WARNING", priority: "D" },
    ]

    property var eventAlarmHistoryData: [
        { date: "2021/07/21", time: "10:20:30", message: "HISTORY EQUIPMENT ERROR", priority: "H" },
        { date: "2021/07/20", time: "07:15:00", message: "HISTORY SYSTEM CHECK", priority: "C" },
    ]

    property var currentTableData: eventAlarmData // Default table data

        Rectangle {
            id: rectangle
            x: 395
            y: 65
            width: 555
            height: 61
            color: "#e7e6e6"
            radius: 10
            border.width: 1
            Image {
                id: image
                anchors.fill: parent
                source: "images/filter.png"
                anchors.leftMargin: 53
                anchors.topMargin: 12
                anchors.bottomMargin: 12
                anchors.rightMargin: 430
                fillMode: Image.PreserveAspectFit
            }
            Text {
                id: text1
                text: qsTr("RELAY START")
                anchors.fill: parent
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 167
                anchors.topMargin: 16
                anchors.rightMargin: 291
                anchors.bottomMargin: 16
            }

            Text {
                id: text2
                text: qsTr("PERIODIC START")
                anchors.fill: parent
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 308
                anchors.topMargin: 16
                anchors.rightMargin: 138
                anchors.bottomMargin: 16
            }

            Text {
                id: text3
                text: qsTr("MANUAL TEST")
                anchors.fill: parent
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 438
                anchors.topMargin: 16
                anchors.rightMargin: 14
                anchors.bottomMargin: 16
            }
            Rectangle {
                id: filterCheck
                color: "#f2f2f2"
                radius: 5
                border.color: "#abaaaa"
                anchors.fill: parent
                anchors.leftMargin: 16
                anchors.topMargin: 16
                anchors.rightMargin: 508
                anchors.bottomMargin: 16
                property bool isActive: false

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        filterCheck.isActive = !filterCheck.isActive
                        filterCheck.color = filterCheck.isActive ? "#00FF00" : "#f2f2f2"
                        if (!filterCheck.isActive) {
                            fliterrelay.isActive = false
                            fliterrelay.color = "#f2f2f2"

                            fliterperisodics.isActive = false
                            fliterperisodics.color = "#f2f2f2"

                            flitermanual.isActive = false
                            flitermanual.color = "#f2f2f2"
                        }
>>>>>>> 66920cd1f75da6a70642d264c64958bc09f89ab8
                    }
                }
            }

<<<<<<< HEAD
        Rectangle {
            id: fliterrelay
            color: fliterrelay.isActive ? "#00FF00" : "#f2f2f2"
            radius: 5
            border.color: "#abaaaa"
            anchors.fill: parent
            anchors.topMargin: 16
            anchors.rightMargin: 471
            anchors.bottomMargin: 16
            anchors.leftMargin: 107
            property bool isActive: false
            enabled: filterCheck.isActive
            MouseArea {
                anchors.fill: parent
                anchors.rightMargin: 0
                enabled: filterCheck.isActive
                onClicked: {
                    fliterrelay.isActive = !fliterrelay.isActive;
                    fliterrelay.color = fliterrelay.isActive ? "#00FF00" : "#f2f2f2";
                    fliterRelayStart(fliterrelay.isActive);
                }
            }
        }

        Rectangle {
            id: fliterperiodics
            color: fliterperiodics.isActive ? "#00FF00" : "#f2f2f2"
            radius: 5
            border.color: "#a6a6a6"
            anchors.fill: parent
            anchors.topMargin: 16
            anchors.rightMargin: 245
            anchors.bottomMargin: 16
            anchors.leftMargin: 333
            property bool isActive: false

            enabled: filterCheck.isActive

            MouseArea {
                anchors.fill: parent
                enabled: filterCheck.isActive
                onClicked: {
                    fliterperiodics.isActive = !fliterperiodics.isActive;
                    fliterperiodics.color = fliterperiodics.isActive ? "#00FF00" : "#f2f2f2";
                    fliterPeriodicStart(fliterperiodics.isActive);
=======
            Rectangle {
                id: fliterrelay
                color: "#f2f2f2"
                radius: 5
                border.color: "#abaaaa"
                anchors.fill: parent
                anchors.topMargin: 16
                anchors.rightMargin: 387
                anchors.bottomMargin: 16
                anchors.leftMargin: 137
                property bool isActive: false

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (filterCheck.isActive) {
                            fliterrelay.isActive = !fliterrelay.isActive
                            fliterrelay.color = fliterrelay.isActive ? "#00FF00" : "#f2f2f2"
                        }else {
                            console.log("Please enable Filter Check first!")
                        }
                    }
>>>>>>> 66920cd1f75da6a70642d264c64958bc09f89ab8
                }
            }

            Rectangle {
                id: fliterperisodics
                color: "#f2f2f2"
                radius: 5
                border.color: "#a6a6a6"
                anchors.fill: parent
                anchors.topMargin: 16
                anchors.rightMargin: 253
                anchors.bottomMargin: 16
                anchors.leftMargin: 271
                property bool isActive: false

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (filterCheck.isActive) {
                            fliterperisodics.isActive = !fliterperisodics.isActive
                            fliterperisodics.color = fliterperisodics.isActive ? "#00FF00" : "#f2f2f2"
                        } else {
                            console.log("Please enable Filter Check first!")
                        }
                    }
                }
            }

            Rectangle {
                id: flitermanual
                color: "#f2f2f2"
                radius: 5
                border.color: "#a9a9a9"
                anchors.fill: parent
                anchors.topMargin: 16
                anchors.rightMargin: 107
                anchors.bottomMargin: 16
                anchors.leftMargin: 417
                property bool isActive: false

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (filterCheck.isActive) {
                            flitermanual.isActive = !flitermanual.isActive
                            flitermanual.color = flitermanual.isActive ? "#00FF00" : "#f2f2f2"
                        } else {
                            console.log("Please enable Filter Check first!")
                        }
                    }
                }
            }

        }
<<<<<<< HEAD

        Rectangle {
            id: flitermanual
            color: flitermanual.isActive ? "#00FF00" : "#f2f2f2"
            radius: 5
            border.color: "#a9a9a9"
            anchors.fill: parent
            anchors.topMargin: 16
            anchors.rightMargin: 116
            anchors.bottomMargin: 16
            anchors.leftMargin: 465
            property bool isActive: false

            enabled: filterCheck.isActive

            MouseArea {
                anchors.fill: parent
                enabled: filterCheck.isActive
                onClicked: {
                    flitermanual.isActive = !flitermanual.isActive;
                    flitermanual.color = flitermanual.isActive ? "#00FF00" : "#f2f2f2";
                    fliterManualStart(flitermanual.isActive);
                }
            }
        }

        Rectangle {
            id: flitersurageStart
            color: flitersurageStart.isActive ? "#00FF00" : "#f2f2f2"
            radius: 5
            border.color: "#a9a9a9"
            anchors.fill: parent
            anchors.topMargin: 16
            anchors.rightMargin: 361
            anchors.bottomMargin: 16
            anchors.leftMargin: 217
            property bool isActive: false

            enabled: filterCheck.isActive

            MouseArea {
                anchors.fill: parent
                enabled: filterCheck.isActive
                onClicked: {
                    flitersurageStart.isActive = !flitersurageStart.isActive;
                    flitersurageStart.color = flitersurageStart.isActive ? "#00FF00" : "#f2f2f2";
                    fliterSurageStart(flitersurageStart.isActive);
                }
            }
        }


        Image {
            id: image
            x: 53
            y: 12
            anchors.fill: parent
            source: "images/filter.png"
            anchors.leftMargin: 53
            anchors.topMargin: 12
            anchors.bottomMargin: 12
            anchors.rightMargin: 519
            fillMode: Image.PreserveAspectFit
        }

        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.leftMargin: 144

            Text {
                id: text1
                text: qsTr("RELAY START")
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: false
            }

            Text {
                id: text4
                text: qsTr("SURAGE TEST")
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: true
            }

            Text {
                id: text2
                text: qsTr("PERIODIC START")
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: false
            }

            Text {
                id: text3
                text: qsTr("MANUAL TEST")
                font.pixelSize: 11
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillWidth: true
            }

        }

    }

=======

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.rightMargin: 45
        anchors.bottomMargin: 20
        anchors.leftMargin: 41
        anchors.topMargin: 65

        TabBar {
            id: tabBar
            Layout.preferredHeight: 50

            TabButton {
                width: 175
                height: 60
                text: qsTr("EVENT && ALARM")
                font.pointSize: 9
                onClicked: {
                    currentTableData = eventAlarmData;
                }
            }
            TabButton {
                width: 175
                height: 60
                text: qsTr("EVENT && ALARM \n HISTORY")
                font.pointSize: 9
                onClicked: {
                    currentTableData = eventAlarmHistoryData;
                }
            }
        }

        Flickable {
            id: flickable
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            contentHeight: columnContent.implicitHeight
            contentWidth: parent.width

            Column {
                id: columnContent
                x: 0
                y: -2
                spacing: 5
                width: flickable.width

                Repeater {
                    model: currentTableData
                    Rectangle {
                        width: parent.width
                        height: 50
                        color: index % 2 === 0 ? "#FFFBEA" : "white"
                        border.color: "lightgray"

                        RowLayout {
                            anchors.fill: parent
                            spacing: 10
                            Text {
                                text: modelData.date
                                color: "black"
                                font.bold: true
                            }
                            Text {
                                text: modelData.time
                                color: "black"
                                font.bold: true
                            }
                            Text {
                                text: modelData.message
                                color: "black"
                                font.bold: true
                                elide: Text.ElideRight
                                horizontalAlignment: Text.AlignLeft
                                width: parent.width / 2
                            }
                            Text {
                                text: modelData.priority
                                color: modelData.priority === "A" ? "red" : "blue"
                                font.bold: true
                                horizontalAlignment: Text.AlignRight
                            }
                        }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
        }
    }
>>>>>>> 66920cd1f75da6a70642d264c64958bc09f89ab8
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}D{i:38}
}
##^##*/

