import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.VirtualKeyboard 2.15

Item {
    width: 300
    height: 380

    property int marginCountA: 0
    property bool focustextInformation: inputPanel.visible
    property string textforinformation:  textInformation.text

    onFocustextInformationChanged: {
        if(focustextInformation == false){
            textFieldMarginNumber.color = "#000000"
        }
    }
    onTextforinformationChanged: {
        if(textFieldMarginNumber.color == "#ff0000"){
            textFieldMarginNumber.text = textforinformation
        }
        console.log("onTextforinformationChanged",textforinformation)
    }
    Rectangle {
        id: rectangle
        color: "#f2f2f2"
        border.color: "#c7c7c7"
        border.width: 2
        anchors.fill: parent
        anchors.bottomMargin: -30

        Text {
            id: text1
            x: 8
            y: 14
            text: qsTr("PHASE A")
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        RowLayout {
            id: rowLayout
            height: 33
            anchors.top: text1.bottom
            anchors.leftMargin: 116
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: -25
            spacing: 10

            Text {
                id: text2
                color: "#244d77"
                text: qsTr("MARGIN")
                font.pixelSize: 16
            }

            TextField {
                id: textFieldMarginNumber
                Layout.preferredHeight: 33
                Layout.preferredWidth: 101
                placeholderText: qsTr("Enter Count")
                inputMethodHints: Qt.ImhDigitsOnly

                onAccepted: {
                    let value = parseInt(text);
                    if (!isNaN(value) && value >= 0) {
                        marginCountA = value;

                    }
                }

                onFocusChanged: {
                    if (focus) {
                        Qt.inputMethod.show();
                        textFieldMarginNumber.focus = false;
                        currentField = "marginNumber";
                        inputPanel.visible = true;
                        textInformation.visible = true;
                        textInformation.text = "";
                        textInformation.inputMethodHints = Qt.ImhFormattedNumbersOnly;
                        textInformation.focus = true;
                        textFieldMarginNumber.color = "#ff0000";
                    }
                }

                Keys.onReturnPressed: Qt.inputMethod.hide();
            }
        }

        ScrollView {
            id: scrollView
            anchors.top: rowLayout.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            clip: true

            contentHeight: columnContainer.height

            Column {
                id: columnContainer
                spacing: 10
                width: scrollView.width

                Repeater {
                    model: newlistMarginA

                    delegate: RowLayout {
                        width: parent.width
                        spacing: 10

                        Text {
                            id: textMargin
                            text: "Margin " + model.list_marginA
                            font.pixelSize: 18
                        }

                        TextField {
                            id: textFieldMargin
                            Layout.preferredHeight: 33
                            Layout.preferredWidth: 101
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            placeholderText: qsTr("Value") ? model.valueMarginA : qsTr("Value")
                            text: model.valueMarginA

                            onTextChanged: {
                                newlistMarginA.set(index, {
                                    "list_marginA": model.list_marginA,
                                    "valueMarginA": text,
                                    "unitMaginA": model.unitMaginA,
                                    "statusMaginA": model.statusMaginA
                                });
                            }
                        }

                        Text {
                            id: voltageUnit
                            text: "mV"/*model.unitMaginA*/
                            font.pixelSize: 18
                        }
                    }
                }
            }
        }

    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
