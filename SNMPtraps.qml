import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

Item {
    width: 380
    height: 460

    Rectangle {
        id: rectangle
        color: "#e7e6e6"
        border.color: "#ffffff"
        border.width: 2
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0

      Rectangle {
            id: rectangle1
            x: 0
            y: 45
            width: 380
            height: 415
            color: "#00ffffff"
            border.color: "#000000"


                ColumnLayout {
                    x: 7
                    y: 0
                    width: 25
                    height: 408

                    Rectangle {
                        id: rectangle2
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
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

                    Rectangle {
                        id: rectangle3
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle4
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle5
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle6
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle7
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle8
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle9
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle10
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle11
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle12
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle13
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }

                    Rectangle {
                        id: rectangle14
                        color: "#ffffff"
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                    }
                }

            ColumnLayout {
                x: 45
                y: 0
                width: 196
                height: 407

                Text {
                    id: text2
                    text: qsTr("PLC DI ERROR")
                    font.pixelSize: 12
                }

                Text {
                    id: text3
                    text: qsTr("MODULE HI-SPEED PHASE A ERROR")
                    font.pixelSize: 12
                }

                Text {
                    id: text4
                    text: qsTr("MODULE HI-SPEED PHASE B ERROR")
                    font.pixelSize: 12
                }

                Text {
                    id: text5
                    text: qsTr("MODULE HI-SPEED PHASE C ERROR")
                    font.pixelSize: 12
                }

                Text {
                    id: text6
                    text: qsTr("GPS MODULE FAIL")
                    font.pixelSize: 12
                }

                Text {
                    id: text7
                    text: qsTr("SYSTEM INITIAL")
                    font.pixelSize: 12
                }

                Text {
                    id: text8
                    text: qsTr("COMMUNICATION ERROR")
                    font.pixelSize: 12
                }

                Text {
                    id: text10
                    text: qsTr("RELAY START EVENT")
                    font.pixelSize: 12
                }

                Text {
                    id: text11
                    text: qsTr("SURGE START EVENT")
                    font.pixelSize: 12
                }

                Text {
                    id: text9
                    text: qsTr("PERIODIC TEST EVENT")
                    font.pixelSize: 12
                }

                Text {
                    id: text13
                    text: qsTr("MANUAL TEST EVENT")
                    font.pixelSize: 12
                }

                Text {
                    id: text14
                    text: qsTr("LFL FAIL")
                    font.pixelSize: 12
                }

                Text {
                    id: text12
                    text: qsTr("LFL OPERATE")
                    font.pixelSize: 12
                }
            }
        }


            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }


        Text {
            id: text1
            x: 8
            y: 13
            text: qsTr("SNMP TRAPS ENABLING")
            font.pixelSize: 18
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/
