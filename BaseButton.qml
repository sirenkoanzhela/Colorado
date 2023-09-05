import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Rectangle {
    id: background
    property alias buttonColor:background.color

    property string iconSourceEnabled: ""
    property string iconSourceDisabled: ""

    signal baseButtonClicked()

    implicitWidth: 50
    implicitHeight: 50

    color: "transparent" //default
    border.color: enabled ? "white" : "gray"
    border.width: 1

    Image {
        id: icon
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: parent.width - 10
        height: parent.height - 10
        source: enabled ? iconSourceEnabled : iconSourceDisabled
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            baseButtonClicked();
            console.log("Base button was clicked");
        }
    }

}
