import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: "Refactor"

    Text {
        id: helloText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        font.bold: true
        font.pointSize: 42
        text: "Wassup!"
    }

    GridLayout {
        id: gridLayout
        anchors.centerIn: parent
        columns: 3
        rows: 3
        columnSpacing: 10
        rowSpacing: 10

        Text { text: "User 1"; font.bold: true; Layout.alignment: Qt.AlignHCenter }
        Text { text: "User 2"; font.bold: true; Layout.alignment: Qt.AlignHCenter }
        Text { text: "User 3"; font.bold: true; Layout.alignment: Qt.AlignHCenter }

        Button {
            text: "1,1"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,1 Clicked!"
        }
        Button {
            text: "1,2"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,2 Clicked!"
        }
        Button {
            text: "1,3"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,3 Clicked!"
        }

        Button {
            text: "2,1"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,1 Clicked!"
        }
        Button {
            text: "2,2"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,2 Clicked!"
        }
        Button {
            text: "2,3"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,3 Clicked!"
        }
        TextArea {
            id: commentField1
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
        }
        TextArea {
            id: commentField2
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
        }
        TextArea {
            id: commentField3
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
        }
        Button {
            text: "Отправить комментарий"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            onClicked: {
                var comment = commentField1.text;
                if (comment.trim() !== "") {
                    console.log("Комментарий отправлен: " + comment);
                    commentField1.text = "";
                } else {
                    console.log("Поле комментария пустое!");
                }
            }
        }

        Button {
            text: "Отправить комментарий"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            onClicked: {
                var comment = commentField2.text;
                if (comment.trim() !== "") {
                    console.log("Комментарий отправлен: " + comment);
                    commentField2.text = "";
                } else {
                    console.log("Поле комментария пустое!");
                }
            }
        }


        Button {
            text: "Отправить комментарий"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            onClicked: {
                var comment = commentField3.text;
                if (comment.trim() !== "") {
                    console.log("Комментарий отправлен: " + comment);
                    commentField3.text = ""; // Очищаем поле после отправки
                } else {
                    console.log("Поле комментария пустое!");
                }
            }
        }
    }
}

