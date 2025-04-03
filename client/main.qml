import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Task Monitor")

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            id: buttonRow
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Connect"
                onClicked: {
                    console.log("QML: The Connect button is pressed.");
                    webSocketClient.onConnectButtonClicked();
                }
            }
        }

        // Other UI elements here...

    }

    // Example data model.
    ListModel {
        id: taskModel
        ListElement { taskNumber: "1"; user: "User 1"; comment: "Task in progress" }
        ListElement { taskNumber: "2"; user: "User 2"; comment: "Work in progress" }
        ListElement { taskNumber: "3"; user: "User 3"; comment: "Pending" }
    }

    // Handling user list update from C++
    function updateUserList(userList) {
        console.log("QML: Updating user list.");
        taskModel.clear();
        for (var i = 0; i < userList.length; i++) {
            taskModel.append({taskNumber: i + 1, user: userList[i], comment: "No comment"});
        }
    }

    // Correct syntax for signal handling
    Connections {
        target: webSocketClient
        function onUserListUpdated(userList) {
            updateUserList(userList);
        }
    }
}
