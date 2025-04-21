// main.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Монитор задач")
    minimumWidth: 600
    minimumHeight: 400

    property int selectedIndex: -1

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Row {
            id: buttonRow
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            Button {
                text: qsTr("Коннект")
                width: 100
                height: 40
                onClicked: {
                    webSocketClient.connectToServer(serverUrl)
                }
            }
        }

        Row {
            id: headerRow
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            spacing: 1

            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("№") }
            }
            Rectangle {
                width: (parent.width - 102) * 0.3
                Layout.minimumWidth: 150
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("Пользователь") }
            }
            Rectangle {
                width: (parent.width - 102) * 0.7
                Layout.minimumWidth: 300
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("Комментарий") }
            }
            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: "" }
            }
        }

        ScrollView {
            id: scrollArea
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: listView
                width: parent.width
                height: parent.height
                model: trackModel
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
                        Text { anchors.centerIn: parent; text: model.id }
                    }
                    Rectangle {
                        width: (parent.width - 102) * 0.3
                        height: parent.height
                        color: "white"
                        border.color: "gray"
                        Text { 
                            anchors.centerIn: parent; 
                            text: model.users ? model.users.join(", ") : "" 
                        }
                        Component.onCompleted: {
                            console.log("Users for track", model.id, ":", model.users ? model.users.join(", ") : "No users");
                        }
                    }

                    Rectangle {
                        width: (parent.width - 102) * 0.7
                        height: parent.height
                        color: "white"
                        border.color: "gray"
                        TextField {
                            anchors.fill: parent
                            text: model.comment
                            font.pixelSize: 16
                            onEditingFinished: {
                                console.log("Комментарий изменён:", model.comment)
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
                            onCheckStateChanged: {
                                if (checkBox.checked) {
                                    window.selectedIndex = index;
                                    webSocketClient.addUserToTrack(model.id, "userName");
                                } else {
                                    if (window.selectedIndex === index) {
                                        window.selectedIndex = -1;
                                    }
                                    webSocketClient.removeUser("userName");
                                }
                            }
                        }
                    }
                }
            }


        }
    }
}
