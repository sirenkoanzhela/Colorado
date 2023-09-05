import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property alias notificationText: notificationLabel.text
    property alias buttonText: roundButton.buttonText


    implicitWidth: 300
    implicitHeight: width / 2
    color: "transparent"
    border.color: "white"

    Column {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        topPadding: 18
        spacing: 15
        Label {
            id: notificationLabel
            text: "Notification Text Here"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20

            wrapMode: Text.WordWrap

            font.pixelSize: 16
            color: "white"
        }

        CircleButton {
            id: roundButton
            anchors.horizontalCenter: notificationLabel.horizontalCenter
        }
    }
}
