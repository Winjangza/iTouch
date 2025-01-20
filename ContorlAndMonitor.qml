import QtQuick 2.7
import QtCharts 2.0
import QtQuick.Controls 2.15

Item {
    width: 1024
    height: 600
    id: controlAndMonitor

    property var distance: distanceRaw
    property var plotdata: voltageRaw
    property int timestep: 0
    property double movetoleft: cursorleft
    property real pointerX: 0
    property real pointerY: 0
    property int globalNum: 0
    property int number: 0
    property bool dataReceived: false

//    onPlotdataChanged: {
//        try {
//            console.log("Extracted voltages:", plotdata);
//            console.log("Extracted distances:", distance);

//            if (plotdata && distance && plotdata.length === distance.length) {
//                for (var i = 0; i < plotdata.length; i++) {
//                    var Amplitude = plotdata[i];
//                    var currentDistance = distance[i];

//                    if (!isFinite(Amplitude) || !isFinite(currentDistance)) {
//                        console.log("Invalid data at index:", i, "Amplitude:", Amplitude, "Distance:", currentDistance);
//                        continue;
//                    }
//                    timestep++;
//                    series1.append(currentDistance, Amplitude);
//                }
//                var validDistances = distance.filter(isFinite);
//                if (validDistances.length > 0) {
//                    axisX.min = Math.min.apply(null, validDistances);
//                    axisX.max = Math.max.apply(null, validDistances);
//                }

//                var validPlotdata = plotdata.filter(isFinite);
//                if (validPlotdata.length > 0) {
//                    axisY.min = Math.min.apply(null, validPlotdata);
//                    axisY.max = Math.max.apply(null, validPlotdata);
//                }
//            } else {
//                coensole.log("Mismatch in data length or data is missing");
//            }
//        } catch (e) {
//            console.log("Error:", e);
//        }
//    }
    onPlotdataChanged: {
        try {
            console.log("Extracted voltages:", plotdata);
            console.log("Extracted distances:", distance);

            if (plotdata && distance && plotdata.length === distance.length) {
                for (var i = 0; i < plotdata.length; i++) {
                    var Amplitude = plotdata[i];
                    var currentDistance = distance[i];

                    if (!isFinite(Amplitude) || !isFinite(currentDistance)) {
                        console.log("Invalid data at index:", i, "Amplitude:", Amplitude, "Distance:", currentDistance);
                        continue;
                    }

                    timestep++;
                    series1.append(currentDistance, Amplitude);

                    var positionX = currentDistance;
                    var positionY = Amplitude;

                    getTaggingData(positionX, positionY, 11);
                }

                var validDistances = distance.filter(isFinite);
                if (validDistances.length > 0) {
                    axisX.min = Math.min.apply(null, validDistances);
                    axisX.max = Math.max.apply(null, validDistances);
                }

                var validPlotdata = plotdata.filter(isFinite);
                if (validPlotdata.length > 0) {
                    axisY.min = Math.min.apply(null, validPlotdata);
                    axisY.max = Math.max.apply(null, validPlotdata);
                }
            } else {
                console.log("Mismatch in data length or data is missing");
            }
        } catch (e) {
            console.log("Error:", e);
        }
    }



    ChartView {
        id: chartView
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.topMargin: 44
        anchors.bottomMargin: 213
        backgroundColor: "#000000"
        legend.labelColor: "white"
        ValueAxis {
            id: axisX
            min: 0
            max: 100
            tickCount: 10
            titleText: "<font color='#ffffff'>Distance (Km)<12>"
            titleFont.bold: true
            titleFont.pixelSize: 12
            labelsVisible: true
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelsFont.pixelSize: 10

        }
        ValueAxis {
            id: axisY
            min: 0
            max: 3000
            titleText: "<font color='#ffffff'>Voltage (mV)<12>"
            titleFont.bold: true
            titleFont.pixelSize: 12
            labelsVisible: true
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelsFont.pixelSize: 10
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
            name: "Phase A"
            color: "#ff0000"
        }

        Rectangle {
            id: cursor
            width: 1
            height: 20 //chartView.height
            color: "#ffffff"
            anchors.top: chartView.top
            anchors.bottom: chartView.bottom
            anchors.bottomMargin: 72
            x: chartView.width / 2
            property double distance: 0.0

            Component.onCompleted: {
                cursor.distance = axisX.min + (cursor.x / chartView.width) * (axisX.max - axisX.min );
            }

            Timer {
                id: initialTimer
                interval: 100
                running: true
                repeat: false

                onTriggered: {
                    var initialPosition = '{"objectName":"distance", "distance": ' + cursor.distance.toFixed(2)+'}';
                    console.log("Initial Position Sent:", initialPosition);
                    qmlCommand(initialPosition);
                }
            }
            MouseArea {
                id: dragArea
                anchors.fill: parent
                anchors.leftMargin: -25
                anchors.rightMargin: -25
                cursorShape: Qt.OpenHandCursor
                drag.target: cursor
                property double safeMargin: 0.0
                property double graphStartOffset: 0.0
                property double graphEndX: 0.0

                onPositionChanged: {
                    safeMargin = 41.53; //ถ้ามากขึ้นcusorมันจะขยับเข้ามาทางซ้าย
                    graphStartOffset = 95.25;//ถ้ามากขึ้นมันจะขยับเข้าใกล้0
                    graphEndX = chartView.width - safeMargin;
                    cursor.x = Math.max(graphStartOffset, Math.min(cursor.x, graphEndX - cursor.width));
                    cursor.distance = (axisX.min + ((cursor.x - graphStartOffset) / (graphEndX - graphStartOffset)) * (axisX.max - axisX.min));
                    var positionDistance = '{"objectName":"distance", "distance": ' + cursor.distance.toFixed(2) +'}';
                    qmlCommand(positionDistance);
                }
                onReleased: {
                    console.log("Cursor moved to Distance (Km):", cursor.distance.toFixed(2),movetoleft,cursorleft );
                }
            }
        }


        Repeater {
            model: taggingA.listofTagging
            delegate: Item {
                x: model.globalPositionX
                y: model.globalPositionY
                ToolButton {
                    id: taggingPointer
                    anchors.centerIn: parent
                    contentItem: Image {
                        source: "images/pinPointerTagging.png"
                        width: 30
                        height: 30
                        onStatusChanged: {
                            if (status === Image.Ready) {
                                console.log("Image loaded successfully!");
                            } else if (status === Image.Error) {
                                console.log("Image failed to load!");
                            }
                        }
                    }
                    background: Rectangle {
                        color: "#00000000"
                    }
                }
                Text {
                    text: model.globalTempNumA
                    anchors.horizontalCenter: taggingPointer.horizontalCenter
                    anchors.top: taggingPointer.bottom
                    color: "white"
                    font.pixelSize: 12
                }
            }
        }
    }


    Cursorcontrol {
        id: cursorcontrol
        anchors.fill: parent
        anchors.bottomMargin: 0
        anchors.leftMargin: 651
        anchors.topMargin: 380
    }

    DataStatusInfo {
        id: dataStatusInfo
        x: 0
        y: 380
    }

    Rectangle {
        id: datafilename
        color: "#f2f2f2"
        radius: 5
        border.color: "#9b9b9b"
        anchors.fill: parent
        anchors.rightMargin: 209
        anchors.bottomMargin: 503
        anchors.leftMargin: 620
        anchors.topMargin: 67

        Text {
            id: textdatafilename
            text: qsTr("Text")
            anchors.fill: parent
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
        id: patternfilename
        color: "#bfbfbf"
        radius: 5
        border.color: "#9b9b9b"
        anchors.fill: parent
        anchors.leftMargin: 821
        anchors.topMargin: 67
        anchors.rightMargin: 8
        anchors.bottomMargin: 503

        Text {
            id: textpatternfilename
            text: qsTr("Text")
            anchors.fill: parent
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

}
