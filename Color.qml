import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15


Rectangle {
    property string colorName: ""
    property string colorHex: ""

    color: colorHex

    Label {
        id: _colorName
        text: colorName
        anchors.centerIn: parent
    }

}
