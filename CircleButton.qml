import QtQuick 2.15
import QtQuick.Controls 2.15


BaseButton {
    //property string text: "!"

    width: 60
    height: 60

    radius: width / 2
    //text: text

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Button clicked")
        }
    }
}
