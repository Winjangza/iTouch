import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0
import QtQuick.Extras 1.4

Item {
    visible: true
    width: 1024
    height: 600

    property var eventAlarmData: [
        { date: "2021/07/22", time: "08:18:40", message: "ALARMS EQUIPMENT ERROR", priority: "A" },
        { date: "2021/07/23", time: "09:30:21", message: "TEMPERATURE HIGH WARNING", priority: "B" },
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
                    }
                }
            }

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

    ColumnLayout {
        anchors.fill: parent
        anchors.rightMargin: 45
        anchors.bottomMargin: 20
        anchors.leftMargin: 41
        anchors.topMargin: 75

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
                text: qsTr("EVENT & ALARM \n HISTORY")
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
}
