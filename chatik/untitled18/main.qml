import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtWebSockets 1.0

Window {
    id: mainWindow
    width: 400
    height: 300
    visible: true
    title: qsTr("WebSocket Example")

    WebSocket {
        id: webSocket
        url: "ws://localhost:12345"
        active: true

        onTextMessageReceived: function(message) {
            console.log("Received message:", message);
            Qt.callLater(function() {
                commentsModel.append({"text": message});
            });
        }

        onStatusChanged: {
            if (status === WebSocket.Open) {
                console.log("WebSocket соединение открыто");
            } else if (status === WebSocket.Closed) {
                console.log("WebSocket соединение закрыто");
            }
        }
    }

    ListModel {
        id: commentsModel
    }

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        TextField {
            id: commentInput
            placeholderText: "Введите ваш комментарий"
            width: parent.width
        }

        Button {
            text: "Отправить"
            onClicked: {
                if (commentInput.text.length > 0) {
                    webSocket.sendTextMessage(commentInput.text);
                    commentInput.text = "";
                }
            }
        }

        ListView {
            model: commentsModel
            delegate: Text {
                text: model.text
            }
            height: 200
            width: parent.width
        }
    }
}
