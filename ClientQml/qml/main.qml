import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("РњРѕРЅРёС‚РѕСЂ Р·Р°РґР°С‡")
    minimumWidth: 600
    minimumHeight: 400

    property int selectedIndex: -1

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // Р’РµСЂС…РЅСЏСЏ РїР°РЅРµР»СЊ СЃ 4 РєРЅРѕРїРєР°РјРё (С„РёРєСЃРёСЂРѕРІР°РЅРЅР°СЏ РІС‹СЃРѕС‚Р°, РЅРµ СЂР°СЃС‚СЏРіРёРІР°РµС‚СЃСЏ)
        Row {
            id: buttonRow
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            Button {
                text: qsTr("РљРѕРЅРЅРµРєС‚")
                width: 100
                height: 40
                onClicked: {
                    webSocketClient.connectToServer(serverUrl)
                }
            }
            /*Button {
                text: qsTr("РљРЅРѕРїРєР° 2")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("РљРЅРѕРїРєР° 3")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("РљРЅРѕРїРєР° 4")
                width: 100
                height: 40
            }*/
        }

        // Р—Р°РіРѕР»РѕРІРѕРє С‚Р°Р±Р»РёС†С‹ (СЂР°СЃС‚СЏРіРёРІР°РµС‚СЃСЏ РїРѕ С€РёСЂРёРЅРµ)
        Row {
            id: headerRow
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            spacing: 1

            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("в„–") }
            }
            Rectangle {
                width: (parent.width - 102) * 0.3
                Layout.minimumWidth: 150
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ") }
            }

            //РґРѕР±Р°РІРёС‚СЊ Р·Р°РіРѕР»РѕРІРѕРє РїР»РµСЏ


            Rectangle {
                width: (parent.width - 102) * 0.7
                Layout.minimumWidth: 300
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("РљРѕРјРјРµРЅС‚Р°СЂРёР№") }
            }
            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: "" }
            }
        }

        // РћР±Р»Р°СЃС‚СЊ РґР»СЏ С‚Р°Р±Р»РёС†С‹ СЃ РїСЂРѕРєСЂСѓС‚РєРѕР№ (СЂР°СЃС‚СЏРіРёРІР°РµС‚СЃСЏ)
        ScrollView {
            id: scrollArea
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: listView
                width: parent.width
                height: parent.height
                model: taskModel
                clip: true
                boundsBehavior: Flickable.StopAtBounds

                delegate: Row {
                    width: listView.width
                    height: 40
                    spacing: 1

                    Rectangle {
                        width: 50
                        height: parent.height
                        color: "white"
                        border.color: "gray"
                        Text { anchors.centerIn: parent; text: taskNumber }
                    }
                    Rectangle {
                        width: (parent.width - 102) * 0.3
                        height: parent.height
                        color: "white"
                        border.color: "gray"
                        Text { anchors.centerIn: parent; text: user }
                    }


                    //РґРѕР±Р°РІРёС‚СЊ РєРЅРѕРїРєСѓ РїР»РµР№


                    Rectangle {
                        width: (parent.width - 102) * 0.7
                        height: parent.height
                        color: "white"
                        border.color: "gray"
                        TextField {
                            anchors.fill: parent
                            text: comment
                            font.pixelSize: 16
                            onEditingFinished: {


                                //РѕС‚РїР°РІРєР° json


                                console.log("РљРѕРјРјРµРЅС‚Р°СЂРёР№ РёР·РјРµРЅС‘РЅ:", text)
                            }
                        }
                    }
                    Rectangle {
                        width: 50
                        height: parent.height
                        color: "white"
                        border.color: "gray"

                        CheckBox {
                            id: checkBox
                            anchors.centerIn: parent
                            checked: window.selectedIndex === index
                            onClicked: {
                                if (checked) {
                                    window.selectedIndex = index;
                                } else if (window.selectedIndex === index) {
                                    window.selectedIndex = -1;
                                }
                                //!!

                                //РѕС‚РїСЂР°РІРєР° json

                                //!!
                            }
                        }
                    }
                }
            }
        }
    }

    // РџСЂРёРјРµСЂ РјРѕРґРµР»Рё РґР°РЅРЅС‹С…
    ListModel {
        id: taskModel
        ListElement { taskNumber: "1"; user: "РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ 1"; comment: "Р’С‹РїРѕР»РЅСЏРµС‚СЃСЏ Р·Р°РґР°С‡Р°"; checked: true }
        ListElement { taskNumber: "2"; user: "РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ 2"; comment: "Р’ СЂР°Р±РѕС‚Рµ"; checked: true }
        ListElement { taskNumber: "3"; user: "РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ 3"; comment: "РћР¶РёРґР°РЅРёРµ"; checked: true }
        ListElement { taskNumber: "4"; user: "РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ 4"; comment: "РўРµСЃС‚РѕРІР°СЏ Р·Р°РґР°С‡Р°"; checked: true }
        ListElement { taskNumber: "5"; user: "РџРѕР»СЊР·РѕРІР°С‚РµР»СЊ 5"; comment: "Р•С‰Рµ РѕРґРЅР° Р·Р°РґР°С‡Р°"; checked: true }
    }
}
