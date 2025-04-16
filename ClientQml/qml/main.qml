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

        // Верхняя панель с 4 кнопками (фиксированная высота, не растягивается)
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
            /*Button {
                text: qsTr("Кнопка 2")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("Кнопка 3")
                width: 100
                height: 40
            }
            Button {
                text: qsTr("Кнопка 4")
                width: 100
                height: 40
            }*/
        }

        // Заголовок таблицы (растягивается по ширине)
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

            //добавить заголовок плея


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

        // Область для таблицы с прокруткой (растягивается)
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


                    //добавить кнопку плей


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


                                //отпавка json


                                console.log("Комментарий изменён:", text)
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

                                //отправка json

                                //!!
                            }
                        }
                    }
                }
            }
        }
    }

    // Пример модели данных
    ListModel {
        id: taskModel
        ListElement { taskNumber: "1"; user: "Пользователь 1"; comment: "Выполняется задача"; checked: true }
        ListElement { taskNumber: "2"; user: "Пользователь 2"; comment: "В работе"; checked: true }
        ListElement { taskNumber: "3"; user: "Пользователь 3"; comment: "Ожидание"; checked: true }
        ListElement { taskNumber: "4"; user: "Пользователь 4"; comment: "Тестовая задача"; checked: true }
        ListElement { taskNumber: "5"; user: "Пользователь 5"; comment: "Еще одна задача"; checked: true }
    }
}