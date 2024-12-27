import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtWebSockets 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.3
import QtGraphicalEffects 1.0

Item {
    width: 630
    height: 400
    property var rowsData: []
    property int selectedRow: -1
    property bool keyboardVisible: false
    property int originalY: 325
    function adjustPosition() {
        if (keyboardVisible) {
            textFieldContainer.y = originalY - 150;
        } else {
            textFieldContainer.y = originalY;
        }
    }

    Rectangle {
        id: rectangle
        color: "#e7e6e6"
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0

        Rectangle {
            id: rectangle1
            color: "#f2f2f2"
            border.color: "#ffffff"
            border.width: 1
            anchors.fill: parent
            anchors.rightMargin: 56
            anchors.leftMargin: 21
            anchors.topMargin: 8
            anchors.bottomMargin: 347

            Text {
                id: notext
                text: qsTr("NO.")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 511
            }
            Text {
                id: distanceText
                text: qsTr("DISTANCE(KM)")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.leftMargin: 111
                anchors.topMargin: 0
                anchors.rightMargin: 352
            }
            Text {
                id: detailText
                text: qsTr("DETAIL")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.bottomMargin: 0
                anchors.leftMargin: 351
                anchors.topMargin: 0
                anchors.rightMargin: 112
            }
        }
        Rectangle {
            id: rectangledetailDistance
            anchors.fill: parent
            anchors.rightMargin: 20
            anchors.bottomMargin: 120
            anchors.leftMargin: 20
            anchors.topMargin: 60
            color: "#e7e6e6"
            border.width: 2

            Flickable {
                id: scrollArea
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: columnContent.implicitHeight
                clip: true

                Column {
                    id: columnContent
                    spacing: 5
                    width: scrollArea.width

                    Repeater {
                        model: rowsData
                        RowLayout {
                            spacing: 10

                            Rectangle {
                                id: checklistbox
                                color: modelData.selected ? "green" : "#ffffff"
                                radius: 5
                                border.color: "#a6a6a6"
                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 40
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        rowsData[index].selected = !rowsData[index].selected
                                        selectedRow = rowsData[index].selected ? index : -1
                                    }
                                }
                            }

                            Text {
                                text: index + 1
                                font.pixelSize: 18
                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 30
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            TextField {
                                text: modelData.distance
                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 150
                                enabled: modelData.selected
                            }

                            TextField {
                                text: modelData.detail
                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 300
                                enabled: modelData.selected
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            x: 20
            y: 368

            ToolButton {
                text: qsTr("NEW")
                onClicked: {
                    rowsData.push({ selected: false, distance: "New Distance", detail: "New Detail" });
                }
            }

            ToolButton {
                text: qsTr("EDIT")
                onClicked: {
                    if (selectedRow !== -1) {
                        rowsData[selectedRow].selected = true;
                    }
                }
            }

            ToolButton {
                text: qsTr("SAVE")
                onClicked: {
                    if (selectedRow !== -1) {
                        console.log("Row " + (selectedRow + 1) + " saved with data:",
                                    rowsData[selectedRow].distance, rowsData[selectedRow].detail);
                    }
                }
            }

            ToolButton {
                text: qsTr("DELETE")
                onClicked: {
                    if (selectedRow !== -1) {
                        rowsData.splice(selectedRow, 1);
                        selectedRow = -1;
                    }
                }
            }
        }


        RowLayout {
            x: 20
            y: 306
            width: 227
            height: 19

            Text {
                id: text5
                text: qsTr("DISTANCE(KM)")
                font.pixelSize: 16
            }

            Text {
                id: text6
                text: qsTr("DETAIL")
                font.pixelSize: 16
            }
        }

        RowLayout {
            x: 20
            y: 331

            TextField {
                id: textField
                Layout.preferredHeight: 40
                Layout.preferredWidth: 110
                placeholderText: qsTr("Text Field")
            }

            TextField {
                id: textField1
                Layout.preferredHeight: 40
                Layout.preferredWidth: 200
                placeholderText: qsTr("Text Field")
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
