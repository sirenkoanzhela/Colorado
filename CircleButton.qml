import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Rectangle {
    id: background
    property alias buttonColor:background.color
    property alias buttonText: label.text
    signal circleButtonClicked()

    implicitWidth: 50
    implicitHeight: 50

    radius: width / 2
    color: "transparent" //default
    border.color: enabled ? "white" : "gray"
    border.width: 1

    Text {
        id: label
        anchors.centerIn: parent
        text:  "CB" //default
        color: enabled ? "white" : "gray"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            circleButtonClicked();
            console.log("CircleButton clicked");
        }
    }

}
