import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15


Item {
    id: panel

    signal colorSelected(int threadIndex, int colorIndex)
    property int currentColor: -1

    Item {
        id: threadList
        anchors.fill: parent
        anchors.leftMargin: 50
        GridView {
            width: 1600
            height: colorSectorsCollection.rowCount() * 50 + 20 * 4
            interactive: false

            cellWidth: width
            cellHeight: 50

            model: colorSectorsCollection

            delegate: ColorThread {
                id: thread
                rowIndex: index
            }

        }

    }

}
//{

  //ListView {
  //   model: threadModel
  //   delegat: ColorThread {}
 // }
