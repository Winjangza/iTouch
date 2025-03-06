import QtQuick 2.7
import QtCharts 2.2
import QtQuick.Controls 2.15
import QtQuick 2.15;
Item {
    width: 1024
    height: 600
    id: controlAndMonitor
    property var distanceA: distanceRawA //x
    property var plotdataA: voltageRawA //y
    property var distanceB: distanceRawB
    property var plotdataB: voltageRawB
    property var distanceC: distanceRawC
    property var plotdataC: voltageRawC
    property var distancepatternA: distancePatternA
    property var plotdatapatternA: voltagePatternA
    property var distancepatternB: distancePatternB
    property var plotdatapatternB: voltagePatternB
    property var distancepatternC: distancePatternC
    property var plotdatapatternC: voltagePatternC
    property int timestep: 0
    property double movetoleft: cursorleft
    property var pointerX_graphA: distancePointA
    property var pointerY_graphA: 0
    property int globalNum: 0
    property int numberOfTagging: numOfTagging
    property var globalMaxY : 4095;
    property var globalMinY : 0;
    property int lengthOfVoltageA: plotdataA.length
    property var testX_graphA : plotDataAX1;
    property var testY_graphA : plotDataAY1;
    property bool newListDataTagging:newListDataTaggingTables
    property bool isGraphHiddingA: false
    property bool isGraphHiddingB: false
    property bool isGraphHiddingC: false
    property bool isGraphHiddingPatternA: false
    property bool isGraphHiddingPatternB: false
    property bool isGraphHiddingPatternC: false
    property bool isCursorActiveA: false
    property bool isCursorActiveB: false
    property bool isCursorActiveC: false
    property var cursorArrayX_PhaseA : []
    property var cursorArrayY_PhaseA : []
    property var cursorArrayX_PhaseB : []
    property var cursorArrayY_PhaseB : []
    property var cursorArrayX_PhaseC : []
    property var cursorArrayY_PhaseC : []
    property var storeTaggingPhaseA : []
    property var storeTaggingPhaseB : []
    property var storeTaggingPhaseC : []
    property var savedTaggingPhaseA: []
    property var savedTaggingPhaseB: []
    property var savedTaggingPhaseC: []
    property int activeTaggingNumberA: -1
    property int activeTaggingNumberB: -1
    property int activeTaggingNumberC: -1
    property string activeTaggingDetailA: ""
    property string activeTaggingDetailB: ""
    property string activeTaggingDetailC: ""
    property int safeMargin: (axisX.max > 299) ? 53 :
                              (axisX.max < 50 ? 49 :
                              (axisX.max < 100 ? 50 :
                              (axisX.max < 150 ? 52 :
                              (axisX.max < 250 ? 53 : 54))));
    property int graphStartOffset: (axisX.max > 299) ? 102 :
                                   (axisX.max < 250 ? 103:
                                   (axisX.max < 150 ? 104 :
                                   (axisX.max < 100 ? 104 : 105)));
    property var midOfCursor: displayShow
    property var positionOfVoltageA:0
    property var positionOfVoltageB:0
    property var positionOfVoltageC:0

    property bool isPhaseALoaded: false
    property bool isPhaseBLoaded: false
    property bool isPhaseCLoaded: false


    onMidOfCursorChanged: {
        if (typeof midOfCursor !== "undefined" && midOfCursor !== null) {
            console.log("onMidOfCursorChanged:", midOfCursor);
            let graphEndX = chartView.width - safeMargin;
            let targetDistance = midOfCursor / 2;
            let normalizedX = graphStartOffset + ((targetDistance - axisX.min) / (axisX.max - axisX.min)) * (graphEndX - graphStartOffset);
            cursor.x = Math.max(graphStartOffset, Math.min(normalizedX, graphEndX));
            cursor.distance = targetDistance;
            console.log("Updated Cursor Position: X =", cursor.x, "Distance =", cursor.distance.toFixed(2));
            initialTimer.running = true;
            return;
        }
    }

//     สำหรับ RawDataA
    onPlotdataAChanged: {
        console.log("⚡ onPlotdataAChanged Triggered!");

        if (!plotdataA || !distanceA || plotdataA.length !== distanceA.length) {
            console.error("❌ Data mismatch for Phase A!");
            return;
        }

        // ✅ จัดการเฉพาะ "กราฟ"
        cursorArrayX_PhaseA = [];
        cursorArrayY_PhaseA = [];
        seriesRawA.clear();

        for (var i = 0; i < plotdataA.length; i++) {
            if (isFinite(plotdataA[i]) && isFinite(distanceA[i])) {
                seriesRawA.append(distanceA[i], plotdataA[i]);
                cursorArrayX_PhaseA.push(distanceA[i]);
                cursorArrayY_PhaseA.push(plotdataA[i]);
            }
        }

        console.log("✅ Phase A Graph Data Loaded");
        adjustAxes(); // ✅ อัปเดตแกนกราฟ
    }
    onPlotdataBChanged: {
        console.log("⚡ onPlotdataBChanged Triggered!");

        if (!plotdataB || !distanceB || plotdataB.length !== distanceB.length) {
            console.error("❌ Data mismatch for Phase B!");
            return;
        }

        // ✅ จัดการเฉพาะ "กราฟ"
        cursorArrayX_PhaseB = [];
        cursorArrayY_PhaseB = [];
        seriesRawB.clear();

        for (var i = 0; i < plotdataB.length; i++) {
            if (isFinite(plotdataB[i]) && isFinite(distanceB[i])) {
                seriesRawB.append(distanceB[i], plotdataB[i]);
                cursorArrayX_PhaseB.push(distanceB[i]);
                cursorArrayY_PhaseB.push(plotdataB[i]);
            }
        }

        console.log("✅ Phase B Graph Data Loaded");
        adjustAxes(); // ✅ อัปเดตแกนกราฟ
    }

    onPlotdataCChanged: {
        console.log("⚡ onPlotdataCChanged Triggered!");

        if (!plotdataC || !distanceC || plotdataC.length !== distanceC.length) {
            console.error("❌ Data mismatch for Phase C!");
            return;
        }

        // ✅ จัดการเฉพาะ "กราฟ"
        cursorArrayX_PhaseC = [];
        cursorArrayY_PhaseC = [];
        seriesRawC.clear();

        for (var i = 0; i < plotdataC.length; i++) {
            if (isFinite(plotdataC[i]) && isFinite(distanceC[i])) {
                seriesRawC.append(distanceC[i], plotdataC[i]);
                cursorArrayX_PhaseC.push(distanceC[i]);
                cursorArrayY_PhaseC.push(plotdataC[i]);
            }
        }

        console.log("✅ Phase C Graph Data Loaded");
        adjustAxes(); // ✅ อัปเดตแกนกราฟ
    }

//    onPlotdataAChanged: {
//        try {
//            console.log("⚡ onPlotdataAChanged Triggered!");
//            if (!plotdataA || !distanceA || plotdataA.length !== distanceA.length) {
//                console.error("Data mismatch for Phase A!");
//                return;
//            }

//            cursorArrayX_PhaseA = [];
//            cursorArrayY_PhaseA = [];
//            seriesRawA.clear();

//            for (var i = 0; i < plotdataA.length; i++) {
//                if (isFinite(plotdataA[i]) && isFinite(distanceA[i])) {
//                    seriesRawA.append(distanceA[i], plotdataA[i]);
//                    cursorArrayX_PhaseA.push(distanceA[i]);
//                    cursorArrayY_PhaseA.push(plotdataA[i]);
//                }
//            }

//            adjustAxes();
//            console.log("Plot Data Updated for Phase A!");
//        } catch (e) {
//            console.error("Error in onPlotdataAChanged:", e);
//        }
//    }

//    onPlotdataAChanged: {
//        try {
//            if (!plotdataA || !distanceA || plotdataA.length !== distanceA.length) {
//                console.error("Data is missing or lengths do not match!");
//                return;
//            }
//            console.log("PlotdataA Length:", plotdataA.length);
//            console.log("DistanceA Length:", distanceA.length);
//            cursorArrayX_PhaseA = [];
//            cursorArrayY_PhaseA = [];
//            seriesRawA.clear();
//            var hasValidPoints = false;
//            for (var i = 0; i < plotdataA.length; i++) {
//                if (isFinite(plotdataA[i]) && isFinite(distanceA[i])) {
//                    seriesRawA.append(distanceA[i], plotdataA[i]);
//                    cursorArrayX_PhaseA.push(distanceA[i]);
//                    cursorArrayY_PhaseA.push(plotdataA[i]);
//                    hasValidPoints = true;
//                } else {
//                    console.warn(`Skipping invalid point: distanceA[${i}] = ${distanceA[i]}, plotdataA[${i}] = ${plotdataA[i]}`);
//                }
//            }
//            if (!hasValidPoints) {
//                console.warn("No valid points found to plot!");
//                return;
//            }
//            adjustAxes(distanceA, [plotdataA]);
//        } catch (e) {
//            console.error("Error in onPlotdataAChanged:", e);
//        }
//    }


//    onPlotdataAChanged: {
//        try {
//            if (!plotdataA || !distanceA || plotdataA.length !== distanceA.length) {
//                console.error("Data is missing or lengths do not match!");
//                return;
//            }
//            console.log("PlotdataA Length:", plotdataA.length);
//            console.log("DistanceA Length:", distanceA.length);
//            seriesRawA.clear();
//            var hasValidPoints = false;
//            for (var i = 0; i < plotdataA.length; i++) {
//                if (isFinite(plotdataA[i]) && isFinite(distanceA[i])) {
//                    seriesRawA.append(distanceA[i], plotdataA[i]);
//                    hasValidPoints = true;
//                } else {
//                    console.warn(`Skipping invalid point: distanceA[${i}] = ${distanceA[i]}, plotdataA[${i}] = ${plotdataA[i]}`);
//                }
//            }
//            if (!hasValidPoints) {
//                console.warn("No valid points found to plot!");
//                return;
//            }
//            adjustAxes(distanceA, [plotdataA]);
//        } catch (e) {
//            console.error("Error in onPlotdataAChanged:", e);
//        }
//    }

//     สำหรับ RawDataB
    // ✅ ฟังก์ชันโหลดข้อมูลสำหรับ Phase B
//    onPlotdataBChanged: {
//        console.log("⚡ onPlotdataBChanged Triggered!");

//        if (!plotdataB || !distanceB || plotdataB.length !== distanceB.length) {
//            console.error("❌ Data mismatch for Phase B!");
//            return;
//        }

//        cursorArrayX_PhaseB = [];
//        cursorArrayY_PhaseB = [];
//        seriesRawB.clear();
//        storeTaggingPhaseB = [];

//        for (var i = 0; i < plotdataB.length; i++) {
//            if (isFinite(plotdataB[i]) && isFinite(distanceB[i])) {
//                seriesRawB.append(distanceB[i], plotdataB[i]);
//                cursorArrayX_PhaseB.push(distanceB[i]);
//                cursorArrayY_PhaseB.push(plotdataB[i]);

//                let taggingData = {
//                    x: distanceB[i],
//                    y: plotdataB[i],
//                    text: i + 1,
//                    phaseABC: "B",
//                    tagInfo: "Tag B " + (i + 1)
//                };
//                storeTaggingPhaseB.push(taggingData);
//            }
//        }

//        isPhaseBLoaded = true; // ✅ บอกว่า Phase B โหลดแล้ว
//        console.log("✅ Phase B Data Loaded");
//        checkAndUpdateScatterModel(); // ✅ เช็คว่าทุกเฟสมาแล้วหรือยัง
//    }

//    onPlotdataCChanged: {
//        console.log("⚡ onPlotdataCChanged Triggered!");

//        if (!plotdataC || !distanceC || plotdataC.length !== distanceC.length) {
//            console.error("❌ Data mismatch for Phase C!");
//            return;
//        }

//        cursorArrayX_PhaseC = [];
//        cursorArrayY_PhaseC = [];
//        seriesRawC.clear();
//        storeTaggingPhaseC = [];

//        for (var i = 0; i < plotdataC.length; i++) {
//            if (isFinite(plotdataC[i]) && isFinite(distanceC[i])) {
//                seriesRawC.append(distanceC[i], plotdataC[i]);
//                cursorArrayX_PhaseC.push(distanceC[i]);
//                cursorArrayY_PhaseC.push(plotdataC[i]);

//                let taggingData = {
//                    x: distanceC[i],
//                    y: plotdataC[i],
//                    text: i + 1,
//                    phaseABC: "C",
//                    tagInfo: "Tag C " + (i + 1)
//                };
//                storeTaggingPhaseC.push(taggingData);
//            }
//        }

//        isPhaseCLoaded = true; // ✅ บอกว่า Phase C โหลดแล้ว
//        console.log("✅ Phase C Data Loaded");
//        checkAndUpdateScatterModel(); // ✅ เช็คว่าทุกเฟสมาแล้วหรือยัง
//    }


//    onPlotdataBChanged: {
//        try {
//            console.log("⚡ onPlotdataBChanged Triggered!");
//            if (!plotdataB || !distanceB || plotdataB.length !== distanceB.length) {
//                console.error("Data mismatch for Phase B!");
//                return;
//            }

//            cursorArrayX_PhaseB = [];
//            cursorArrayY_PhaseB = [];
//            seriesRawB.clear();

//            for (var i = 0; i < plotdataB.length; i++) {
//                if (isFinite(plotdataB[i]) && isFinite(distanceB[i])) {
//                    seriesRawB.append(distanceB[i], plotdataB[i]);
//                    cursorArrayX_PhaseB.push(distanceB[i]);
//                    cursorArrayY_PhaseB.push(plotdataB[i]);
//                }
//            }

//            adjustAxes(); // ✅ ใช้ฟังก์ชันเดียว
//            console.log("✅ Plot Data Updated for Phase B!");
//        } catch (e) {
//            console.error("Error in onPlotdataBChanged:", e);
//        }
//    }

//    // สำหรับ RawDataC

//    onPlotdataCChanged: {
//        try {
//            console.log("onPlotdataCChanged Triggered!");
//            if (!plotdataC || !distanceC || plotdataC.length !== distanceC.length) {
//                console.error("Data mismatch for Phase C!");
//                return;
//            }

//            cursorArrayX_PhaseC = [];
//            cursorArrayY_PhaseC = [];
//            seriesRawC.clear();

//            for (var i = 0; i < plotdataC.length; i++) {
//                if (isFinite(plotdataC[i]) && isFinite(distanceC[i])) {
//                    seriesRawC.append(distanceC[i], plotdataC[i]);
//                    cursorArrayX_PhaseC.push(distanceC[i]);
//                    cursorArrayY_PhaseC.push(plotdataC[i]);
//                }
//            }

//            adjustAxes(); // ✅ ใช้ฟังก์ชันเดียว
//            console.log("✅ Plot Data Updated for Phase C!");
//        } catch (e) {
//            console.error("Error in onPlotdataCChanged:", e);
//        }
//    }
    // ✅ สำหรับ Pattern A
    onPlotdatapatternAChanged: {
        try {
            console.log("⚡ onPlotdatapatternAChanged Triggered!");

            if (!plotdatapatternA || !distancepatternA || plotdatapatternA.length !== distancepatternA.length) {
                console.error("❌ Data mismatch for Pattern A!");
                return;
            }

            series1.clear(); // ✅ ล้างข้อมูลเก่า

            for (var i = 0; i < plotdatapatternA.length; i++) {
                if (isFinite(plotdatapatternA[i]) && isFinite(distancepatternA[i])) {
                    series1.append(distancepatternA[i], plotdatapatternA[i]);
                }
            }

            adjustAxes(); // ✅ อัปเดตแกนกราฟ
            console.log("✅ Pattern A Data Loaded!");
        } catch (e) {
            console.error("❌ Error in onPlotdatapatternAChanged:", e);
        }
    }

    // ✅ สำหรับ Pattern B
    onPlotdatapatternBChanged: {
        try {
            console.log("⚡ onPlotdatapatternBChanged Triggered!");

            if (!plotdatapatternB || !distancepatternB || plotdatapatternB.length !== distancepatternB.length) {
                console.error("❌ Data mismatch for Pattern B!");
                return;
            }

            series2.clear(); // ✅ ล้างข้อมูลเก่า

            for (var i = 0; i < plotdatapatternB.length; i++) {
                if (isFinite(plotdatapatternB[i]) && isFinite(distancepatternB[i])) {
                    series2.append(distancepatternB[i], plotdatapatternB[i]);
                }
            }

            adjustAxes(); // ✅ อัปเดตแกนกราฟ
            console.log("✅ Pattern B Data Loaded!");
        } catch (e) {
            console.error("❌ Error in onPlotdatapatternBChanged:", e);
        }
    }

    // ✅ สำหรับ Pattern C
    onPlotdatapatternCChanged: {
        try {
            console.log("⚡ onPlotdatapatternCChanged Triggered!");

            if (!plotdatapatternC || !distancepatternC || plotdatapatternC.length !== distancepatternC.length) {
                console.error("❌ Data mismatch for Pattern C!");
                return;
            }

            series3.clear(); // ✅ ล้างข้อมูลเก่า

            for (var i = 0; i < plotdatapatternC.length; i++) {
                if (isFinite(plotdatapatternC[i]) && isFinite(distancepatternC[i])) {
                    series3.append(distancepatternC[i], plotdatapatternC[i]);
                }
            }

            adjustAxes(); // ✅ อัปเดตแกนกราฟ
            console.log("✅ Pattern C Data Loaded!");
        } catch (e) {
            console.error("❌ Error in onPlotdatapatternCChanged:", e);
        }
    }

    // ฟังก์ชันสำหรับปรับแกน
    function adjustAxes() {
        try {
            console.log("⚡ Adjusting Axes...");

            // รวมค่า X และ Y จากทุก Phase
            var allDistances = [...distanceA, ...distanceB, ...distanceC];
            var allPlotData = [...plotdataA, ...plotdataB, ...plotdataC];

            if (allDistances.length === 0 || allPlotData.length === 0) {
                console.warn("⚠ No valid data to adjust axes!");
                return;
            }
            var maxX = Math.max.apply(null, allDistances);
            var maxY = Math.max.apply(null, allPlotData);

            axisX.min = 0;
            axisX.max = maxX;

            axisY.min = 0;
            axisY.max = maxY + 200;

            console.log("Axes Updated: X [0 -", maxX, "] Y [0 -", maxY + 200, "]");
        } catch (e) {
            console.error("Error in adjustAxes:", e);
        }
    }

    function hiddingGraphDataPhaseA() {
        distanceA = [];
        plotdataA = [];
        isGraphHiddingA = true;
    }

    function hiddingGraphDataPhaseB() {
        distanceB = [];
        plotdataB = [];
        isGraphHiddingB = true;
    }

    function hiddingGraphDataPhaseC() {
        distanceC = [];
        plotdataC = [];
        isGraphHiddingC = true;
    }

    function hiddingGraphPatternPhaseA() {
        distancepatternA = [];
        plotdatapatternA = [];
        isGraphHiddingPatternA = true;
    }

    function hiddingGraphPatternPhaseB() {
        distancepatternB = [];
        plotdatapatternB = [];
        isGraphHiddingPatternB = true;
    }

    function hiddingGraphPatternPhaseC() {
        distancepatternC = [];
        plotdatapatternC = [];
        isGraphHiddingPatternC = true;

    }

    function replotDataA() {
        distanceA=distanceRawA
        plotdataA =voltageRawA
        isGraphHiddingA = false;
    }

    function replotDataB() {
        distanceB =distanceRawB
        plotdataB =voltageRawB
        isGraphHiddingB = false;
    }

    function replotDataC() {
        distanceC =distanceRawC
        plotdataC =voltageRawC
        isGraphHiddingC = false;
    }

    function replotPatternA() {
        distancepatternA = distancePatternA
        plotdatapatternA = voltagePatternA
        isGraphHiddingPatternA = false
    }

    function replotPatternB() {
        distancepatternB = distancePatternB
        plotdatapatternB = voltagePatternB
        isGraphHiddingPatternB = false
    }

    function replotPatternC() {
        distancepatternC = distancePatternC
        plotdatapatternC = voltagePatternC
        isGraphHiddingPatternC = false
    }

    function cleardisplay() {
        seriesRawA.clear();
        seriesRawB.clear();
        seriesRawC.clear();
        series1.clear();
        series2.clear();
        series3.clear();
        distanceA.splice(0, distanceA.length);
        plotdataA.splice(0, plotdataA.length);
        distanceB.splice(0, distanceB.length);
        plotdataB.splice(0, plotdataB.length);
        distanceC.splice(0, distanceC.length);
        plotdataC.splice(0, plotdataC.length);
        distancepatternA.splice(0, distancepatternA.length);
        plotdatapatternA.splice(0, plotdatapatternA.length);
        distancepatternB.splice(0, distancepatternB.length);
        plotdatapatternB.splice(0, plotdatapatternB.length);
        distancepatternC.splice(0, distancepatternC.length);
        plotdatapatternC.splice(0, plotdatapatternC.length);
        isGraphClearedA = true;
        isGraphClearedB = true;
        isGraphClearedC = true;
    }

    function clearpattern() {
        distancepatternA = [];
        plotdatapatternA = [];
        distancepatternB = [];
        plotdatapatternB = [];
        distancepatternC = [];
        plotdatapatternC = [];
        isGraphClearedA = true;
        isGraphClearedB = true;
        isGraphClearedC = true;
    }

    function reloadTaggingData() {
        storeTaggingPhaseA = [];
        storeTaggingPhaseB = [];
        storeTaggingPhaseC = [];

        for (var i = 0; i < newlistdatatebleA.count; i++) {
            var item = newlistdatatebleA.get(i);
            var mappedPos = chartView.mapToPosition(Qt.point(item.list_distanceA, item.ampiltudeVol), scatter1);
            var taggingData = {
                x: mappedPos.x,
                y: mappedPos.y,
                text: item.list_numberA,
                phaseABC: item.list_phaseA,
                tagInfo: item.list_detailA
            };

            if (item.list_phaseA === "A") {
                storeTaggingPhaseA.push(taggingData);
            } else if (item.list_phaseA === "B") {
                storeTaggingPhaseB.push(taggingData);
            } else if (item.list_phaseA === "C") {
                storeTaggingPhaseC.push(taggingData);
            }
        }

        console.log("Tagging Data Reloaded");
        console.log("Phase A:", storeTaggingPhaseA.length);
        console.log("Phase B:", storeTaggingPhaseB.length);
        console.log("Phase C:", storeTaggingPhaseC.length);
    }

    Component.onCompleted: {
        reloadTaggingData();
    }

    onVisibleChanged: {
        if (visible) {
            reloadTaggingData();
        }
    }

//    function reloadTaggingData() {
//        console.log("Reloading Tagging Data...");

//        storeTaggingPhaseA = [];
//        storeTaggingPhaseB = [];
//        storeTaggingPhaseC = [];

//        for (var i = 0; i < newlistdatatebleA.count; i++) {
//            var item = newlistdatatebleA.get(i);
//            var mappedPos = chartView.mapToPosition(Qt.point(item.list_distanceA, item.ampiltudeVol), scatter1);
//            var rawX = mappedPos.x;
//            var rawY = mappedPos.y;
//            var rawNumber = item.list_numberA;
//            var phase = item.list_phaseA;
//            var taggingInfo = item.list_detailA;

//            console.log(`Processing Item ${i}: X=${rawX}, Y=${rawY}, Number=${rawNumber}, Phase=${phase}`);

//            var taggingData = { x: rawX, y: rawY, text: rawNumber, phaseABC: phase, tagInfo: taggingInfo };

//            if (phase === "A") {
//                storeTaggingPhaseA.push(taggingData);
//            } else if (phase === "B") {
//                storeTaggingPhaseB.push(taggingData);
//            } else if (phase === "C") {
//                storeTaggingPhaseC.push(taggingData);
//            }
//        }

//        console.log("✅ Reloaded Tagging Data");
//        console.log("🔹 Phase A:", storeTaggingPhaseA.length);
//        console.log("🔹 Phase B:", storeTaggingPhaseB.length);
//        console.log("🔹 Phase C:", storeTaggingPhaseC.length);
//    }
//    Component.onCompleted: {
//        reloadTaggingData();
//    }

//    onVisibleChanged: {
//        if (visible) {
//            reloadTaggingData();
//        }
//    }
    onNewListDataTaggingChanged: {
        console.log("📌 onNewListDataTaggingChanged:", newlistdatatebleA.count);

        scatterModel.clear(); // ✅ ล้างค่าก่อนเติมข้อมูลใหม่

        for (var i = 0; i < newlistdatatebleA.count; i++) {
            var item = newlistdatatebleA.get(i);
            var mappedPos = chartView.mapToPosition(Qt.point(item.list_distanceA, item.ampiltudeVol), scatter1);

            scatterModel.append({
                "x": mappedPos.x,
                "y": mappedPos.y,
                "text": item.list_numberA,
                "status": item.list_statusA,
                "phaseABC": item.list_phaseA,
                "tagInfo": item.list_detailA
            });
        }

        console.log("✅ Scatter Model Updated with", newlistdatatebleA.count, "items");
    }

//    onNewListDataTaggingChanged: {
//        console.log("onNewListDataTaggingChanged:", newlistdatatebleA.count);

////        storeTaggingPhaseA = [];
////        storeTaggingPhaseB = [];
////        storeTaggingPhaseC = [];

//        for (var i = 0; i < newlistdatatebleA.count; i++) {
//            var item = newlistdatatebleA.get(i);
//            var mappedPos = chartView.mapToPosition(Qt.point(item.list_distanceA, item.ampiltudeVol), scatter1);
//            var rawX = mappedPos.x;
//            var rawY = mappedPos.y;
//            var rawNumber = item.list_numberA;
//            var phase = item.list_phaseA;
//            var taggingInfo = item.list_detailA

//            console.log(`Processing_item_listModel ${i}: X=${rawX}, Y=${rawY}, Number=${rawNumber}, Phase=${phase}`);

//            scatterModel.append({
//                "x": rawX,
//                "y": rawY,
//                "text": rawNumber,
//                "status": item.list_statusA,
//                "phaseABC": phase,
//                "tagInfo" : taggingInfo
//            });

////            var taggingData = {x: rawX, y: rawY , text : rawNumber, phaseABC: phase, tagInfo: taggingInfo};
////            console.log("taggingData:",taggingData);
////            if (phase === "A") {
////                storeTaggingPhaseA.push(taggingData);
////            } else if (phase === "B") {
////                storeTaggingPhaseB.push(taggingData);
////            } else if (phase === "C") {
////                storeTaggingPhaseC.push(taggingData);
////            }
//        }

//        console.log("✅ Stored Tagging Data");
//        console.log("🔹 Phase A:", storeTaggingPhaseA);
//        console.log("🔹 Phase B:", storeTaggingPhaseB);
//        console.log("🔹 Phase C:", storeTaggingPhaseC);
//    }

//    onNewListDataTaggingChanged: {
//        if (newlistdatatebleA.count === scatterModel.count) {
//            return;
//        }

//        console.log("onNewListDataTaggingChanged:", newlistdatatebleA.count);

//        // ✅ เคลียร์ข้อมูลก่อนเพื่อไม่ให้ค่าซ้ำซ้อน
//        storeTaggingPhaseA = [];
//        storeTaggingPhaseB = [];
//        storeTaggingPhaseC = [];

//        for (var i = 0; i < newlistdatatebleA.count; i++) {
//            var item = newlistdatatebleA.get(i);
//            var mappedPos = chartView.mapToPosition(Qt.point(item.list_distanceA, item.ampiltudeVol), scatter1);
//            var rawX = mappedPos.x;
//            var rawY = mappedPos.y;
//            var rawNumber = item.list_numberA;
//            var phase = item.list_phaseA;

//            console.log(`Processing_item_listModel ${i}: RawX=${rawX}, RawY=${rawY}, Number=${rawNumber}, Phase=${phase}`);

//            scatterModel.append({
//                "x": rawX,
//                "y": rawY,
//                "text": rawNumber,
//                "status": item.list_statusA,
//                "phaseABC": phase
//            });

//            var taggingData = {"x": rawX, "y": rawY, "text": rawNumber};

//            if (phase === "A") {
//                storeTaggingPhaseA.push(taggingData);
//            } else if (phase === "B") {
//                storeTaggingPhaseB.push(taggingData);
//            } else if (phase === "C") {
//                storeTaggingPhaseC.push(taggingData);
//            }
//        }
//    }

//    onNewListDataTaggingChanged:
//    {
//        if(newlistdatatebleA.count === scatterModel.count){
//            return
//        }
//        console.log("onNewListDataTaggingChanged:", newlistdatatebleA.count);

//        for (var i = 0; i < newlistdatatebleA.count; i++) {
//            var mappedPos = chartView.mapToPosition(Qt.point(newlistdatatebleA.get(i).list_distanceA, newlistdatatebleA.get(i).ampiltudeVol), scatter1);
//            var rawX = mappedPos.x;
//            var rawY = mappedPos.y;
//            var rawNumber = newlistdatatebleA.get(i).list_numberA;

//            console.log(`Processing_item_listModel${i}: RawX=${rawX}, RawY=${rawY}, Number=${rawNumber}`, "Phase" ,newlistdatatebleA.get(i).list_phaseA);

//            scatterModel.append({
//                "x": rawX,
//                "y": rawY,
//                "text": rawNumber,
//                "status": newlistdatatebleA.get(i).list_statusA,
//                "phaseABC" : newlistdatatebleA.get(i).list_phaseA
//            });
//        }
//    }


    // กราฟ
    ChartView {
        id: chartView
        anchors.fill: parent
        anchors.topMargin: 49
        anchors.bottomMargin: 213
        backgroundColor: "#000000"
        legend.labelColor: "white"
        legend.visible: false

        property bool openGL: true
        ScatterSeries {
            id: scatter1
            axisX: axisX
            axisY: axisY
            visible: false
        }
        Repeater {
            id: repeater
            model: scatterModel
            delegate: PointerTagging {
                number: model.text
                dataReceived: model.status
                phase: model.phaseABC
                width: 50
                height: 50
                x: model.x
                y: model.y
            }
        }


        ValueAxis {
            id: axisX
            min: 0
            max: axisX.max
            tickCount: 10
            titleText: "<font color='#ffffff'>Distance (Km)</font>"
            titleFont.bold: true
            titleFont.pixelSize: 16
            labelsVisible: true
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelsFont.pixelSize: 14
        }

        ValueAxis {
            id: axisY
            min: axisY.min
            max: axisY.max
            titleText: "<font color='#ffffff'>Voltage (mV)</font>"
            titleFont.bold: true
            titleFont.pixelSize: 16
            labelsVisible: true
            gridVisible: false
            color: "#ffffff"
            labelsColor: "#ffffff"
            labelsFont.pixelSize: 14
        }

        // Phase A
        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
//            name: "Pattern A"
            color: "#f7cbac"
            width: 3

        }
        LineSeries {
            id: series2
            axisX: axisX
            axisY: axisY
//            name: "Pattern B"
            color: "#bc9121"
            width: 3
        }
        // Phase C
        LineSeries {
            id: series3
            axisX: axisX
            axisY: axisY
//            name: "Pattern C"
            color: "#bed6ed"
            width: 3
        }

        // Phase Data A
        LineSeries {
            id: seriesRawA
            axisX: axisX
            axisY: axisY
            color: "#fd2d1d"
            width: 3
//            useOpenGL: chartView.openGL
        }

        // Phase Data B
        LineSeries {
            id: seriesRawB
            axisX: axisX
            axisY: axisY
//            name: "Data B"
            color: "#fcff3b"
            width: 3
        }
        // Phase Data C
        LineSeries {
            id: seriesRawC
            axisX: axisX
            axisY: axisY
//            name: "Data C"
            color: "#0088ff"
            width: 3
        }
        Rectangle {
            id: cursor
            width: 2
            height: chartView.height - 72
            color: "#ffffff"
            radius: 1
            z: 2
            visible: true

            property double distance: 0.0
            property double voltage: 0.0

            property int graphStartOffset: 105
            property int safeMargin: (axisX.max > 299) ? 53 : (axisX.max < 50 ? 49 : 50)
            property double midDistance: (axisX.min + axisX.max) / 2

            x: graphStartOffset + ((midDistance - axisX.min) / (axisX.max - axisX.min)) * (chartView.width - safeMargin - graphStartOffset)
            y: (chartView.topMargin !== undefined) ? chartView.topMargin : 0

            Component.onCompleted: {
                updateCursorValues();
            }

            Timer {
                id: initialTimer
                interval: 100
                running: false
                repeat: false
                onTriggered: {
                    let positionCursorInit = midOfCursor;
                    let initialPosition = `{"objectName":"positionDistance", "distance": ${positionCursorInit.toFixed(2)}}`;
                    console.log("Initial Position Sent:", initialPosition, "Mid Distance:", midOfCursor);
                    qmlCommand(initialPosition);
                }
            }

            MouseArea {
                id: dragArea
                anchors.fill: parent
                anchors.leftMargin: -20
                anchors.rightMargin: -20
                cursorShape: Qt.OpenHandCursor
                drag.axis: Drag.XAxis
                drag.target: cursor

                onPositionChanged: {
                    let graphEndX = chartView.width - safeMargin;
                    cursor.x = Math.max(graphStartOffset, Math.min(cursor.x, graphEndX));
                    cursor.y = (chartView.topMargin !== undefined) ? chartView.topMargin : 0;
                    let positionData = `{"objectName":"positionDistance", "distance": ${cursor.distance.toFixed(2)}}`;
                    console.log("Sending Cursor Position:", positionData);
                    qmlCommand(positionData);

                    updateCursorVoltage();
                    updateCursorValues();
                    checkCursorProximity();
                }

                onReleased: {
                    console.log("Cursor Released: Distance =", cursor.distance.toFixed(2));
                }
            }
        }



//        Rectangle {
//            id: cursor
//            width: 2
//            height: chartView.height - 72
//            color: "#ffffff"
//            radius: 1
//            z: 2

//            visible: true

//            property double distance: 0.0
//            property double voltage: 0.0

//            x: (chartView.width - 72) / 2
//            y: (chartView.topMargin !== undefined) ? chartView.topMargin : 0

//            Component.onCompleted: {
//                updateCursorValues();
//            }

//            Timer {
//                id: initialTimer
//                interval: 100
//                running: false
//                repeat: false

//                onTriggered: {
//                    var positionCursorInit = midOfCursor / 2
//                    var initialPosition = '{"objectName":"positionDistance", "distance": ' + positionCursorInit.toFixed(2)+'}';
//                    console.log("Initial Position Sent:", initialPosition,midOfCursor,positionCursorInit);
//                    qmlCommand(initialPosition);
//                }
//            }



//            MouseArea {
//                id: dragArea
//                anchors.fill: parent
//                anchors.leftMargin: -14
//                anchors.rightMargin: -17
//                cursorShape: Qt.OpenHandCursor
//                drag.axis: Drag.XAxis
//                drag.target: cursor

//                onPositionChanged: {
//                    const graphStartOffset = 105;
//                    const graphEndX = chartView.width - safeMargin;
//                    cursor.x = Math.max(graphStartOffset, Math.min(cursor.x, graphEndX));
//                    cursor.y = (chartView.topMargin !== undefined) ? chartView.topMargin : 0;
//                    updateCursorValues();

//                    checkCursorProximity()

//                    const positionData = `{"objectName":"positionDistance", "distance": ${cursor.distance.toFixed(2)}}`;
//                    console.log("Sending Cursor Position:", positionData);
//                    qmlCommand(positionData);
//                }

//                onReleased: {
//                    console.log("Cursor Released: Distance =", cursor.distance.toFixed(2));
//                }
//            }
//        }

//        Rectangle {
//            id: cursor
//            width: 1
//            height: 20 // chartView.height
//            color: "#ffffff"
//            anchors.top: chartView.top
//            anchors.bottom: chartView.bottom
//            anchors.bottomMargin: 72
//            x: chartView.width / 2
//            y: chartView.height
//            property double distance: 0.0
//            property double voltage: 0.0 // แก้ไขการรับรู้ของค่า voltage

//            Component.onCompleted: {
//                cursor.distance = axisX.min + (cursor.x / chartView.width) * (axisX.max - axisX.min );
//                cursor.voltage = axisY.min + (cursor.y / chartView.height) * (axisY.max - axisY.min ); // คำนวณค่า voltage
//            }

//            Timer {
//                id: initialTimer
//                interval: 100
//                running: true
//                repeat: false

//                onTriggered: {
//                    var initialPosition = '{"objectName":"positionDistance", "distance": ' + cursor.distance.toFixed(2)+'}';
//                    console.log("Initial Position Sent:", initialPosition);
//                    qmlCommand(initialPosition);
//                }
//            }

//            MouseArea {
//                id: dragArea
//                anchors.fill: parent
//                anchors.topMargin: 0
//                anchors.leftMargin: -25
//                anchors.rightMargin: -25
//                cursorShape: Qt.OpenHandCursor
//                drag.target: cursor
//                property double safeMargin: 0.0
//                property double graphStartOffset: 0.0
//                property double graphEndX: 0.0
//                property double graphEndY: 0.0


//                onPositionChanged: {
//                    safeMargin = 41.53; // ถ้ามากขึ้น cursor จะขยับเข้ามาทางซ้าย
//                    graphStartOffset = 95.25; // ถ้ามากขึ้นจะขยับเข้าใกล้ 0
//                    graphEndX = chartView.width - safeMargin;
//                    cursor.x = Math.max(graphStartOffset, Math.min(cursor.x, graphEndX - cursor.width));

//                    // คำนวณค่า distance และ voltage จากแกน X และ Y
//                    cursor.distance = axisX.min + ((cursor.x - graphStartOffset) / (graphEndX - graphStartOffset)) * (axisX.max - axisX.min);
//                    cursor.voltage = axisY.min + ((cursor.y - chartView.top) / chartView.height) * (axisY.max - axisY.min); // คำนวณค่า voltage จากตำแหน่ง Y

//                    // แสดงค่าใน console
//                    console.log("Cursor position X:", cursor.x, " Distance (Km):", cursor.distance.toFixed(2),
//                                " Y:", cursor.y, " Voltage (mV):", cursor.voltage.toFixed(2));

//                    var positionDistance = '{"objectName":"positionDistance", "distance": ' + cursor.distance.toFixed(2) +'}';
//                    qmlCommand(positionDistance);
//                    checkCursorProximity();
//                }

//                onReleased: {
//                    console.log("Cursor moved to Distance (Km):", cursor.distance.toFixed(2), " Voltage (mV):", cursor.voltage.toFixed(2));
//                }
//            }
//        }
    }
    function updateCursorVoltage() {
        var threshold = 0.01;

        function findClosestVoltage(cursorArrayX, cursorArrayY, phase) {
            var closestIndex = -1;
            var minDiff = Infinity;
            for (var i = 0; i < cursorArrayX.length; i++) {
                let diff = Math.abs(cursorArrayX[i] - cursor.distance);
                if (diff < minDiff) {
                    minDiff = diff;
                    closestIndex = i;
                }
            }

            if (closestIndex !== -1) {
                let voltage = cursorArrayY[closestIndex].toFixed(2) + " mV";
                console.log(`✅ Voltage Updated for ${phase}:`, voltage, "at Distance:", cursor.distance.toFixed(2));
                return voltage;
            }
            return "0.00 mV";
        }

        positionOfVoltageA = findClosestVoltage(cursorArrayX_PhaseA, cursorArrayY_PhaseA, "Phase A");
        positionOfVoltageB = findClosestVoltage(cursorArrayX_PhaseB, cursorArrayY_PhaseB, "Phase B");
        positionOfVoltageC = findClosestVoltage(cursorArrayX_PhaseC, cursorArrayY_PhaseC, "Phase C");
    }

    function updateCursorValues() {
        const graphStartOffset = 105;
        const graphEndX = chartView.width - safeMargin;
        cursor.distance = axisX.min + ((cursor.x - graphStartOffset) / (graphEndX - graphStartOffset)) * (axisX.max - axisX.min);

        console.log("Updated Cursor: Distance =", cursor.distance.toFixed(2));
    }

    function checkCursorProximity() {
        const cursorMappedX = chartView.mapToPosition(Qt.point(cursor.distance, 0), scatter1).x;
        console.log("Mapped Cursor X =", cursorMappedX, "Original Distance =", cursor.distance);

        isCursorActiveA = false;
        isCursorActiveB = false;
        isCursorActiveC = false;
        activeTaggingNumberA = 0;
        activeTaggingNumberB = 0;
        activeTaggingNumberC = 0;
        activeTaggingDetailA = "";
        activeTaggingDetailB = "";
        activeTaggingDetailC = "";

        checkProximity(storeTaggingPhaseA, "A", cursorMappedX);
        checkProximity(storeTaggingPhaseB, "B", cursorMappedX);
        checkProximity(storeTaggingPhaseC, "C", cursorMappedX);

        console.log("Final Active States: A =", isCursorActiveA, "B =", isCursorActiveB, "C =", isCursorActiveC);
    }

    function checkProximity(storeTagging, phase, cursorMappedX) {
        console.log("Checking Proximity for Phase:", phase, "Tagging Count:", storeTagging.length);

        var isCursorActive = false;
        var threshold = 5;
        var closestNumber = null;
        var closestDetail = null;

        if (storeTagging.length === 0) {
            console.log(`No data in ${phase}, reloading from saved data...`);
            if (phase === "A" && savedTaggingPhaseA.length > 0) {
                storeTagging = [...savedTaggingPhaseA];
            }
            if (phase === "B" && savedTaggingPhaseB.length > 0) {
                storeTagging = [...savedTaggingPhaseB];
            }
            if (phase === "C" && savedTaggingPhaseC.length > 0) {
                storeTagging = [...savedTaggingPhaseC];
            }
        }

        for (var i = 0; i < storeTagging.length; i++) {
            var taggingX = storeTagging[i].x;
            var taggingY = storeTagging[i].y;
            var taggingNumber = storeTagging[i].text;
            var taggingDetail = storeTagging[i].tagInfo;

            var minX = taggingX - threshold;
            var maxX = taggingX + threshold;

            console.log(`Checking ${phase} Tagging ${i}: X=${taggingX}, Y=${taggingY}, Number=${taggingNumber}, Detail=${taggingDetail}`);
            console.log(`Valid Range X=[${minX}, ${maxX}]`);

            if (Math.abs(cursorMappedX - taggingX) <= threshold) {
                isCursorActive = true;
                closestNumber = taggingNumber;
                closestDetail = taggingDetail;
                console.log("Cursor is near tagging! Activated Phase:", phase, "Tag:", closestNumber, "Detail:", closestDetail);
                break;
            }
        }

        if (phase === "A") {
            isCursorActiveA = isCursorActive;
            activeTaggingNumberA = closestNumber !== null ? closestNumber : 0;
            activeTaggingDetailA = closestDetail !== null ? closestDetail : "";
        }
        if (phase === "B") {
            isCursorActiveB = isCursorActive;
            activeTaggingNumberB = closestNumber !== null ? closestNumber : 0;
            activeTaggingDetailB = closestDetail !== null ? closestDetail : "";
        }
        if (phase === "C") {
            isCursorActiveC = isCursorActive;
            activeTaggingNumberC = closestNumber !== null ? closestNumber : 0;
            activeTaggingDetailC = closestDetail !== null ? closestDetail : "";
        }

        console.log("Final State:", phase, "isCursorActive =", isCursorActive);
    }


//    function checkProximity(storeTagging, phase) {
//        console.log("Checking Proximity for Phase:", phase, "Tagging Count:", storeTagging.length);
//        var isCursorActive = false;
//        var threshold = 5;
//        var cursorMappedX = chartView.mapToPosition(Qt.point(cursor.distance, 0), scatter1).x;
//        console.log("✅ Mapped Cursor X =", cursorMappedX, "Original Distance =", cursor.distance);

//        for (var i = 0; i < storeTagging.length; i++) {
//            var taggingX = storeTagging[i].x;
//            var taggingY = storeTagging[i].y;

//            var minX = taggingX - threshold;
//            var maxX = taggingX + threshold;
//            var minY = taggingY - threshold;
//            var maxY = taggingY + threshold;

//            console.log(`Checking ${phase} Tagging ${i}: X=${taggingX}, Y=${taggingY}`);
//            console.log(`Valid Range X=[${minX}, ${maxX}], Y=[${minY}, ${maxY}]`);

//            if (cursorMappedX >= minX && cursorMappedX <= maxX) {
//                isCursorActive = true;
//                console.log("Cursor is near tagging! Activated Phase:", phase);
//                break;
//            }
//        }

//        if (phase === "A") isCursorActiveA = isCursorActive;
//        if (phase === "B") isCursorActiveB = isCursorActive;
//        if (phase === "C") isCursorActiveC = isCursorActive;

//        console.log("Final State:", phase, "isCursorActive =", isCursorActive);
//    }




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
        width: 650
        height: 220
    }

    Rectangle {
        id: datafilename
        color: "#f2f2f2"
        radius: 5
        border.color: "#9b9b9b"
        anchors.fill: parent
        anchors.rightMargin: 214
        anchors.bottomMargin: 510
        anchors.leftMargin: 615
        anchors.topMargin: 60

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
        anchors.leftMargin: 816
        anchors.topMargin: 60
        anchors.rightMargin: 13
        anchors.bottomMargin: 510

        Text {
            id: textpatternfilename
            text: qsTr("Text")
            anchors.fill: parent
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    Popup {
        id: remotePopup
        width: parent.width * 0.5
        height: parent.height * 0.3
        modal: true
        dim: true
        closePolicy: Popup.NoAutoClose
        anchors.centerIn: parent

        background: Rectangle {
            color: "#ffffff"
            radius: 10
            border.color: "#9b9b9b"
            border.width: 2
        }

        Column {
            spacing: 20
            anchors.centerIn: parent
            Text {
                id: remoteMessage
                text: "REMOTE MODE"
                font.pixelSize: 20
                font.bold: true
                color: "#000000"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Button {
                text: "OK"
                onClicked: remotePopup.close()
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
