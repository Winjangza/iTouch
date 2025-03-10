import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0
import QtQml 2.2
import QtQuick.Controls.Material 2.4

Item {
    width: 1024
    height: 600
    property bool isOnDataStoragePage: false
    property string currentPage: "MainPage"
    property string currentDataTime: datetime

//    property string mainBarMasterSelect
//    property string mainBarSlaveSelect
//    property bool checkUser: checkUser  datetime
    property string typrUser: !usertypeSelect ? mainBarSlaveSelect : mainBarMasterSelect

    ListModel{
        id: listmodel
        ListElement {index:0; source: "qrc:/Mainpage.qml"; name:"MainPage" }
        ListElement {index:1; source: "qrc:/Eventspage.qml"; name:"EventandAlrams" }
        ListElement {index:2; source: "qrc:/DataStoragePage.qml"; name:"DataStorage" }
        ListElement {index:3; source: "qrc:/SettingPage.qml"; name:"Setting" }
        ListElement {index:4; source: "qrc:/LoginPage.qml"; name:"Login" }
    }

    ListView {
        id: listView
        currentIndex: 0
        onCurrentIndexChanged: {
            if (!((currentIndex == 0) || (currentIndex == -1))){
                stackView.push(listmodel.get(currentIndex).source)
                stackView.currentItem.objectName=listmodel.get(currentIndex).name
            }
            else if (currentIndex == 0)
            {
                stackView.pop(null)
                stackView.currentItem.objectName="Home"
            }
            else
            {

            }
        }
        model: listmodel
    }

    Rectangle {
        id: mainbar
        x: 0
        y: 0
        width: 1024
        height: 62
        color: "#f2f2f2"
        border.color: "#2eaaaaaa"
        border.width: 2

        LedStatus {
            id: ledStatus
            x: 8
            y: 11

        }
        Rectangle {
            id: dataandtime
            x: 839
            y: 8
            width: 177
            height: 42
            color: "#f2f2f2"
            radius: 5
            border.color: "#759e9e9e"
            border.width: 2

            Text {
                id: textdataandtime
                text: currentDataTime
                anchors.fill: parent
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 0
            }
        }
        Text {
            id: mode
            x: 51
            y: 5
            width: 85
            height: 48
            color: "#7e7e7e"
            text: qsTr("MODE")
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
        }

        Rectangle {
            id: master
            x: 142
            y: 5
            width: 73
            height: 48
            color: "#ffffff"
            radius: 8
            border.color: "#ababab"
            border.width: 2

            Text {
                id: userType
                text: typrUser
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
        }

        Rectangle {
            id: admin
            x: 221
            y: 5
            width: 73
            height: 48
            color: "#f2f2f2"
            radius: 8
            border.color: "#ababab"
            border.width: 2
            Text {
                id: text3
                text: qsTr("ADMIN")
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 0
                anchors.topMargin: 0

                Rectangle {
                    id: lockadmin
                    x: 80
                    y: 0
                    width: 73
                    height: 48
                    color: "#fae6d7"
                    radius: 8
                    border.color: "#ababab"
                    border.width: 2
                    Text {
                        id: text4
                        text: qsTr("LOCKED\nBY ADMIN")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }

        RowLayout {
            x: 446
            y: 0
            width: 385
            height: 62
            ToolButton {
                id: backtoMainpage
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: false
                contentItem: Label {
                    text: qsTr("MAIN \n PAGE")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 9
                }
                onClicked: {
                    while (stackView.depth > 1) {
                        stackView.pop()
                    }
                    currentPage = "MainPage"
                    backtoMainpage.visible = false
                    eventsalarms.visible = true
                    dataStorage.visible = true
                    imageSetting.visible = true
                    imageUnlock.visible = true
                    console.log("Returned to MainPage from " + currentPage)
                }
            }

            ToolButton {
                id: eventsalarms
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: true
                contentItem: Label {
                    text: qsTr("EVENTS \n ALARMS")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 8
                }
                onClicked: {
                    stackView.push("qrc:/Eventspage.qml")
                    currentPage = "Eventspage"
                    eventsalarms.visible = false
                    backtoMainpage.visible = true
                    dataStorage.visible = true
                    imageSetting.visible = true
                    imageUnlock.visible = true
                    console.log("Navigated to Eventspage")
                }
            }

            ToolButton {
                id: dataStorage
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: true
                contentItem: Label {
                    text: qsTr("DATA \n STORAGE")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 9
                }
                onClicked: {
                    stackView.push("qrc:/DataStoragePage.qml")
                    currentPage = "DataStoragePage"
                    dataStorage.visible = false
                    backtoMainpage.visible = true
                    eventsalarms.visible = true
                    imageSetting.visible = true
                    imageUnlock.visible = true
                    console.log("Navigated to DataStoragePage")
                }
            }

            ToolButton {
                id: imageSetting
                Layout.preferredHeight: 58
                icon.source: "images/settings.png"
                icon.width: 32
                icon.height: 32
                Layout.preferredWidth: 58
                Layout.fillHeight: false
                Layout.fillWidth: false
                property bool isOnSettingPage: false
                visible: true
                onClicked: {
                    if (!isOnSettingPage) {
                        stackView.push("qrc:/SettingPage.qml")
                        currentPage = "Setting"
                        imageSetting.visible = false
                        backtoMainpage.visible = true
                        eventsalarms.visible = true
                        dataStorage.visible = true
                        imageUnlock.visible = true
                        console.log("Navigated to DataStoragePage")
                    }
                }
            }

            ToolButton {
                id: imageUnlock
                Layout.preferredWidth: 58
                Layout.fillHeight: false
                Layout.fillWidth: false
                Layout.preferredHeight: 58
                icon.source: "images/unlock.png"
                icon.width: 200
                icon.height: 200
                visible: true
                property bool isLogInPage: false

                onClicked: {
                    if(!isLogInPage){
                        stackView.push("qrc:/LoginPage.qml")
                        imageUnlock.visible = false
                        backtoMainpage.visible = true
                        eventsalarms.visible = true
                        dataStorage.visible = true
                        imageSetting.visible = true
                    }
                }
            }

        }
        ToolButton {
            id: capture
            x: 378
            y: 0
            width: 62
            height: 62
            Layout.preferredHeight: 58
            icon.width: 32
            icon.height: 32
            Layout.preferredWidth: 58
            Layout.fillHeight: false
            Layout.fillWidth: false
            contentItem: Image {
                width: 50
                height: 50
                source: "images/capture.png"
                fillMode: Image.PreserveAspectFit
                smooth: true
            }
            onClicked: {
                window.getScreenshot();
                console.log("Capture screen")
            }
        }
    }


}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
