import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtWebSockets 1.0

Window {
    id: mainWindow
    width: 1000
    height: 500
    visible: true
    title: qsTr("Real-Time Cursors")
    property string userId: Math.random().toString(36).substring(7)

    WebSocket {
        id: webSocket
        url: "ws://localhost:12345"
        active: true
        onTextMessageReceived: function(message) {
            console.log("Received message:", message);
            var data = JSON.parse(message);
            if (data.areaId === "hoverArea1") {
                updateUserList(data, userListModel1);
            } else if (data.areaId === "hoverArea2") {
                updateUserList(data, userListModel2);
            } else if (data.areaId === "hoverArea3") {
                updateUserList(data, userListModel3);
            }
        }
        function updateUserList(data, userListModel) {
            var index = userListModel.findUser(data.id);
            if (data.active) {
                if (index === -1) {
                    userListModel.append({ id: data.id, name: data.name });
                }
            } else {
                if (index !== -1) {
                    userListModel.remove(index);
                }
            }
        }
    }
    component HoverArea: Rectangle {
        required property string areaId
        required property ListModel userListModel
        width: 200
        height: 100
        color: "lightgray"
        anchors.margins: 20

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                var message = JSON.stringify({
                    id: userId,
                    name: "User " + userId.substring(0, 5),
                    active: true,
                    areaId: parent.areaId
                });
                webSocket.sendTextMessage(message);
            }
            onExited: {
                var message = JSON.stringify({
                    id: userId,
                    name: "User " + userId.substring(0, 5),
                    active: false,
                    areaId: parent.areaId
                });
                webSocket.sendTextMessage(message);
            }
        }

        Rectangle {
               width: 120
               height: 100
               color: "gray"
               anchors.left: parent.right
               anchors.verticalCenter: parent.verticalCenter
               anchors.margins: 100

               ListView {
                   anchors.fill: parent
                   model: userListModel
                   delegate: Text {
                       text: model.name
                       font.pixelSize: 16
                       padding: 5
                   }
               }
           }
    }


    ListModel
    {
        id: userListModel1;
        function findUser(id)
        {
            return findUserInModel(id, this);
        }
    }
    ListModel
    {
        id:  userListModel2;
        function findUser(id)
        {
            return findUserInModel(id, this);
        }
    }
    ListModel
    {
        id: userListModel3;
        function findUser(id)
        {
            return findUserInModel(id, this);
        }
    }

    function findUserInModel(id, model)
    {
        for (var i = 0; i < model.count; i++)
        {
            if (model.get(i).id === id) {
                return i;
            }
        }
        return -1;
    }

    HoverArea {
        id: hoverArea1
        areaId: "hoverArea1"
        userListModel: userListModel1
        anchors.left: parent.left
        anchors.top: parent.top
    }

    HoverArea {
        id: hoverArea2
        areaId: "hoverArea2"
        userListModel: userListModel2
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }

    HoverArea {
        id: hoverArea3
        areaId: "hoverArea3"
        userListModel: userListModel3
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
}
