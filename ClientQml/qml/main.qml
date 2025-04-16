import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("������� �����")
    minimumWidth: 600
    minimumHeight: 400

    property int selectedIndex: -1

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // ������� ������ � 4 �������� (������������� ������, �� �������������)
        Row {
            id: buttonRow
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            Button {
                text: qsTr("�������")
                width: 100
                height: 40
                onClicked: {
                    webSocketClient.connectToServer(serverUrl)
                }
            }
            /*Button {
                text: qsTr("������ 2")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("������ 3")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("������ 4")
                width: 100
                height: 40
            }*/
        }

        // ��������� ������� (������������� �� ������)
        Row {
            id: headerRow
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            spacing: 1

            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("�") }
            }
            Rectangle {
                width: (parent.width - 102) * 0.3
                Layout.minimumWidth: 150
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("������������") }
            }

            //�������� ��������� ����


            Rectangle {
                width: (parent.width - 102) * 0.7
                Layout.minimumWidth: 300
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: qsTr("�����������") }
            }
            Rectangle {
                width: 50
                height: parent.height
                color: "#e0e0e0"
                Text { anchors.centerIn: parent; text: "" }
            }
        }

        // ������� ��� ������� � ���������� (�������������)
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


                    //�������� ������ ����


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


                                //������� json


                                console.log("����������� ������:", text)
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

                                //�������� json

                                //!!
                            }
                        }
                    }
                }
            }
        }
    }

    // ������ ������ ������
    ListModel {
        id: taskModel
        ListElement { taskNumber: "1"; user: "������������ 1"; comment: "����������� ������"; checked: true }
        ListElement { taskNumber: "2"; user: "������������ 2"; comment: "� ������"; checked: true }
        ListElement { taskNumber: "3"; user: "������������ 3"; comment: "��������"; checked: true }
        ListElement { taskNumber: "4"; user: "������������ 4"; comment: "�������� ������"; checked: true }
        ListElement { taskNumber: "5"; user: "������������ 5"; comment: "��� ���� ������"; checked: true }
    }
}