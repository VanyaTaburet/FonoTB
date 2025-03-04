import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: "Refactor"

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4facfe" }
            GradientStop { position: 1.0; color: "#00f2fe" }
        }
    }

    Text {
        id: helloText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        font.bold: true
        font.pointSize: 42
        text: "Wassup!"
        color: "white"
    }

    GridLayout {
        id: gridLayout
        anchors.centerIn: parent
        columns: 3
        rows: 3
        columnSpacing: 10
        rowSpacing: 10

        Text { text: "User 1"; font.bold: true; Layout.alignment: Qt.AlignHCenter; color: "white" }
        Text { text: "User 2"; font.bold: true; Layout.alignment: Qt.AlignHCenter; color: "white" }
        Text { text: "User 3"; font.bold: true; Layout.alignment: Qt.AlignHCenter; color: "white" }

        Button {
            text: "1,1"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,1 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "1,2"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,2 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "1,3"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 1,3 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "2,1"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,1 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        // Кнопка 2,2
        Button {
            text: "2,2"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,2 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        // Кнопка 2,3
        Button {
            text: "2,3"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 2,3 Clicked!"
            background: Rectangle {
                color: parent.down ? "#20B2AA" : "#40E0D0"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        // TextArea для комментариев
        TextArea {
            id: commentField1
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "#4facfe"
                border.width: 2
            }
        }

        TextArea {
            id: commentField2
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "#4facfe"
                border.width: 2
            }
        }

        TextArea {
            id: commentField3
            placeholderText: "Введите ваш комментарий..."
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            wrapMode: TextArea.Wrap
            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "#4facfe"
                border.width: 2
            }
        }

        Button {
            text: "Отправить"
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
            background: Rectangle {
                color: parent.down ? "#4facfe" : "#00f2fe"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "Отправить"
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
            background: Rectangle {
                color: parent.down ? "#4facfe" : "#00f2fe"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "Отправить"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            onClicked: {
                var comment = commentField3.text;
                if (comment.trim() !== "") {
                    console.log("Комментарий отправлен: " + comment);
                    commentField3.text = "";
                } else {
                    console.log("Поле комментария пустое!");
                }
            }
            background: Rectangle {
                color: parent.down ? "#4facfe" : "#00f2fe"
                radius: 10
                border.color: "black"
                border.width: 2
            }
            contentItem: Text {
                text: parent.text
                font.bold: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}

