import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0
import QtQml 2.2

Item {
    width: 369
    height: 220
    property double totalDecrease: 0.0
    property bool focustextInformation: inputPanel.visible
    property string textforinformation:  textInformation.text

    onFocustextInformationChanged: {
        if(focustextInformation == false){
            rangeOfDistance.color = "#000000"
        }
    }
    onTextforinformationChanged: {
        if(rangeOfDistance.color == "#ff0000"){
            rangeOfDistance.text = textforinformation
        }
        console.log("onTextforinformationChanged",textforinformation)
    }
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 369
        height: 220
        color: "#e2e2e2"
        border.color: "#c8595959"
        border.width: 1
        ToolButton {
            id: clearalarm
            text: qsTr("CLEAR \n ALARM")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 0
            anchors.rightMargin: 259
            anchors.bottomMargin: 151
        }

        ToolButton {
            id: cleardisplay
            text: qsTr("CLEAR \n DISPLAY")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 75
            anchors.rightMargin: 259
            anchors.bottomMargin: 84
        }

        ToolButton {
            id: cleardisplay1
            text: qsTr("CLEAR \n PATTERN")
            anchors.fill: parent
            font.pointSize: 9
            anchors.leftMargin: 8
            anchors.topMargin: 142
            anchors.rightMargin: 259
            anchors.bottomMargin: 8
        }

        Text {
            id: text5
            text: qsTr("CURSOR(KM)")
            anchors.fill: parent
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 172
            anchors.topMargin: 0
            anchors.rightMargin: 74
            anchors.bottomMargin: 191
        }


        ToolButton {
            id: cursorLeft
            Layout.preferredHeight: 58
//            icon.source: "images/leftArrow.png"
//            icon.width: 45
//            icon.height: 45
            Layout.preferredWidth: 58
            Layout.fillHeight: false
            Layout.fillWidth: false
             contentItem: Image {
                 source: "images/leftArrow.png"
                 width: 70
                 height: 60
             }

            x: 112
            y: 35
            width: 69
            height: 56

            Timer {
                id: holdTimer
                interval: 100
                repeat: true
                property double decrease: 0.1
                property double safeMargin: 41.53
                property double graphStartOffset: 95.25
                property double graphEndX: chartView.width - safeMargin
                property double totalDecrease: 0.0
                onTriggered: {
                    cursor.distance = Math.max(axisX.min, cursor.distance - decrease);
                    cursor.x = graphStartOffset + ((cursor.distance - axisX.min) / (axisX.max - axisX.min)) * (graphEndX - graphStartOffset);

                    totalDecrease += decrease;

                    var decreaseValue = '{"objectName":"decreaseValue","decreaseValue": ' + cursor.distance.toFixed(2) + '}';
                    console.log("decreaseValue:", cursor.distance.toFixed(2), cursor.x.toFixed(2), decreaseValue);
                    qmlCommand(decreaseValue);
                }
            }

            MouseArea {
                anchors.fill: parent
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                onPressed: {
                    holdTimer.start();
                }
                onReleased: {
                    holdTimer.stop();
                    console.log("Total decrease during hold:", totalDecrease.toFixed(2));
                    totalDecrease = 0.0;
                }
            }
        }


        ToolButton {
            id: cursorRight
            Layout.preferredHeight: 58
//            icon.source: "images/rightArrow.png"
//            icon.width: 45
//            icon.height: 45
            Layout.preferredWidth: 58
            Layout.fillHeight: false
            Layout.fillWidth: false
            property bool isRight: false
            contentItem: Image {
                source: "images/rightArrow.png"
                width: 70
                height: 60
            }
            x: 292
            y: 32
            width: 69
            height: 56
            Timer {
                id: holdTimer2
                interval: 100
                repeat: true
                property double decrease: 0.1
                property double safeMargin: 41.53
                property double graphStartOffset: 95.25
                property double graphEndX: chartView.width - safeMargin
                onTriggered: {
                    cursor.distance = Math.max(axisX.min, cursor.distance + decrease);
                    cursor.x = graphStartOffset + ((cursor.distance - axisX.min) / (axisX.max - axisX.min)) * (graphEndX - graphStartOffset);

                    totalDecrease += decrease;

                    var increaseValue = '{"objectName":"increaseValue","increaseValue": ' + cursor.distance.toFixed(2) + '}';
                    console.log("decreaseValue:", cursor.distance.toFixed(2), cursor.x.toFixed(2), increaseValue);
                    qmlCommand(increaseValue);
                }
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    holdTimer2.start();
                }
                onReleased: {
                    holdTimer2.stop();
                    console.log("Total decrease during hold:", totalDecrease.toFixed(2));
                    totalDecrease = 0.0;
                }
            }
        }

        Rectangle {
            id: cursorDistance
            color: "#ffffff"
            radius: 5
            border.color: "#7a7a7a"
            border.width: 1
            anchors.fill: parent
            anchors.leftMargin: 187
            anchors.topMargin: 35
            anchors.rightMargin: 89
            anchors.bottomMargin: 136
            TextField {
                id: rangeOfDistance
                anchors.fill: parent
                anchors.rightMargin: 1
                anchors.leftMargin: 1
                anchors.bottomMargin: 1
                anchors.topMargin: 1
                placeholderText: cursorposition ? cursor.distance.toFixed(2) : updateNewDistance

                onFocusChanged: {
                    if (focus) {
                        Qt.inputMethod.show();
                        rangeOfDistance.focus = false;
                        currentField = "rangedistance";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.text = "";
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.focus = true;
                        rangeOfDistance.color = "#ff0000";
                    }
                }
            }
        }

        ToolButton {
            id: patterntest
            text: qsTr("PATTERN \n TEST")
            anchors.fill: parent
            anchors.rightMargin: 138
            anchors.bottomMargin: 28
            anchors.leftMargin: 138
            anchors.topMargin: 127
        }
        ToolButton {
            id: manualtest
            text: qsTr("MANUAL \n TEST")
            anchors.fill: parent
            anchors.rightMargin: 8
            anchors.bottomMargin: 28
            anchors.leftMargin: 268
            anchors.topMargin: 127
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
