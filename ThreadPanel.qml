import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15


Item {
    id: panel

    property int currentColor: -1

    Item {
        id: threadList
        anchors.fill: parent
        anchors.leftMargin: 50
        ListView {
            anchors.fill: parent
            interactive: false
            spacing: 20

            model: colorSectorsCollection

            delegate: ColorThread {
                rowIndex: index
            }

        }
    }
}
