import QtQuick 2.0

Item {
    id: _parent
    GridView {
        id: _palette

        cellWidth: 100
        cellHeight: 100
        model: container

        visible: false

        delegate: ColorSpectrum {
            id: _сolorSegment

            width: parent.width
            height: parent.height

            topColorName: ""
            topColorHex: ""
            bottomColorName: ""
            bottomColorHex: ""

            radius: 10

            states: [
                State {
                    name: "pressed"
                    PropertyChanges {
                        target: _сolorSegment
                        border.color: "red"
                    }
                }
            ]
        }

    }
    Notification {
        id: _paletteEmpty
        visible: true
        anchors.fill: _parent

        width: _parent.width
        height: _parent.height

        buttonText: "+"
        labelText:  "Click to add new color spectrum"
    }
}
