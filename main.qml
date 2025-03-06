import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Scrollable Sections with Input Fields")

    ListModel
    {
        id: usersModel
    }

    Flickable 
    {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height
        clip: true

        Column 
        {
            id: column
            width: parent.width
            spacing: 10

            Repeater {
                model: 15
                delegate: Rectangle
                {
                    width: flickable.width
                    height: 150
                    color: "lightgray"

                    Text 
                    {
                        text: (index + 1).toString()
                        anchors {
                            left: parent.left
                            verticalCenter: parent.verticalCenter
                            margins: 10
                        }
                        font.pixelSize: 16
                        color: "black"
                    }

                    Button
                    {
                        width: parent.width * 0.2
                        height: 60
                        anchors 
                        {
                            left: parent.left
                            verticalCenter: parent.verticalCenter
                            margins: 40
                        }
                        text: "Отправить"
                        onClicked: {
                            console.log("Секция " + (index + 1) + ": " + inputField.text)
                            // Добавляем пользователя в модель
                            usersModel.append({ "section": index + 1, "user": inputField.text })
                            updateUserStatus()
                        }
                    }

                    TextField 
                    {
                        id: inputField
                        width: parent.width * 0.5
                        height: 60
                        anchors.centerIn: parent
                        placeholderText: "Введите текст..."
                    }

                    Text
                    {
                        id: userStatus
                        anchors 
                        {
                            bottom: parent.bottom
                            left: parent.left
                            margins: 10
                        }
                        text: "Нет взаимодействия"
                        font.pixelSize: 14
                        color: "black"
                    }

                    function updateUserStatus()
                    {
                        var status = "Взаимодействуют: "
                        for (var i = 0; i < usersModel.count; i++)
                        {
                            if (usersModel.get(i).section === index + 1)
                            {
                                status += " Петуx " + i
                            }
                        }
                        userStatus.text = status === "Взаимодействуют: " ? "Нет взаимодействия" : status.slice(0, -2)
                    }
                }
            }
        }
    }
}

