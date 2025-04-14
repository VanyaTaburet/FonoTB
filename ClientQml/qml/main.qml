import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("WebSocket Client")

    Column {
        anchors.centerIn: parent

        Text {
            text: qsTr("WebSocket Client")
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: qsTr("Connect")
            onClicked: {
                webSocketClient.connectToServer(serverUrl)
            }
        }

        // Добавьте другие элементы интерфейса здесь
    }
}
