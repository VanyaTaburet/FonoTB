import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    visible: true
    width: 800
    height: 600
    title: "Comments and Audio Controls"

    Rectangle {
        anchors.fill: parent
        color: "#2E2E2E"
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Repeater {
            model: 5
            delegate: Rectangle {
                width: 600
                height: 120
                color: "#3D3D3D"
                radius: 10
                border.color: "#4facfe"
                border.width: 2

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text {
                        text: "Fono " + (index + 1)
                        font.bold: true
                        font.pointSize: 16
                        color: "#FFFFFF"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    TextArea {
                        id: commentField
                        placeholderText: "Введите ваш комментарий..."
                        Layout.fillWidth: true
                        Layout.preferredHeight: 60
                        wrapMode: TextArea.Wrap
                        background: Rectangle {
                            color: "#4D4D4D"
                            radius: 5
                            border.color: "#4facfe"
                            border.width: 1
                        }
                        color: "#FFFFFF"
                    }

                    Button {
                        text: "Отправить"
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 40
                        onClicked: {
                            var comment = commentField.text;
                            if (comment.trim() !== "") {
                                console.log("Комментарий отправлен для User " + (index + 1) + ": " + comment);
                                commentField.text = "";
                            } else {
                                console.log("Поле комментария пустое для User " + (index + 1));
                            }
                        }
                        background: Rectangle {
                            color: parent.down ? "#4facfe" : "#00f2fe"
                            radius: 5
                            border.color: "black"
                            border.width: 1
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
                        id: startButton
                        text: "Слушать"
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 40
                        onClicked: {
                            console.log("Начало прослушивания для User " + (index + 1));
                            startButton.visible = false;
                            stopButton.visible = true;
                            audioAnimation.start();
                        }
                        background: Rectangle {
                            color: parent.down ? "#4facfe" : "#00f2fe"
                            radius: 5
                            border.color: "black"
                            border.width: 1
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
                        id: stopButton
                        text: "Завершить"
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 40
                        visible: false
                        onClicked: {
                            console.log("Завершение прослушивания для User " + (index + 1));
                            stopButton.visible = false;
                            startButton.visible = true;
                            audioAnimation.stop();
                            slider.width = 0;
                        }
                        background: Rectangle {
                            color: parent.down ? "#4facfe" : "#00f2fe"
                            radius: 5
                            border.color: "black"
                            border.width: 1
                        }
                        contentItem: Text {
                            text: parent.text
                            font.bold: true
                            color: "black"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Rectangle {
                        id: audioVisualization
                        width: 100
                        height: 20
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Rectangle {
                            id: slider
                            width: 0
                            height: 4
                            color: "#4facfe"
                            radius: 2
                            anchors.verticalCenter: parent.verticalCenter

                            SequentialAnimation on width {
                                id: audioAnimation
                                running: false
                                loops: Animation.Infinite
                                NumberAnimation { to: parent.width; duration: 200000; easing.type: Easing.Linear }
                                NumberAnimation { to: 0; duration: 0; }
                            }
                        }
                    }
                }
            }
        }
    }
}
