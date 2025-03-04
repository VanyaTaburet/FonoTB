import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: "QtQuickApplication19"

    Text {
        id: helloText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        font.bold: true
        font.pointSize: 42
        text: "Hello World!"
    }

 
    GridLayout {
        id: gridLayout
        anchors.centerIn: parent
        columns: 3  
        rows: 3     
        Text { text: "Column 1"; font.bold: true; Layout.alignment: Qt.AlignHCenter }
        Text { text: "Column 2"; font.bold: true; Layout.alignment: Qt.AlignHCenter }
        Text { text: "Column 3"; font.bold: true; Layout.alignment: Qt.AlignHCenter }

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

        Button {
            text: "3,1"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 3,1 Clicked!"
        }
        Button {
            text: "3,2"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 3,2 Clicked!"
        }
        Button {
            text: "3,3"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 60
            Layout.alignment: Qt.AlignHCenter
            onClicked: helloText.text = "Button 3,3 Clicked!"
        }
    }

    Button {
        id: myButton
        text: "Click Me"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        onClicked: {
            helloText.text = "Button Clicked!"
        }
    }
}

