import QtQuick 2.0
import QtQuick.Layouts 1.3

Item
{
    property int vitesse: 0
    property string dixiemeVent: qsTr(".0")

    GridLayout {
        id: gridTemperature
        rows: 3
        columns: 2
        Layout.row: 1
        Layout.column: 0

        Text {
            id: textTemperature
            Layout.row:  1
            Layout.column: 0
            Layout.rowSpan: 2
            text: vitesse
            font.pointSize: 100
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            Layout.leftMargin: 50
        }

        Text{
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 2
            font.pointSize: 20
            Layout.topMargin: 5
            text: "Vitesse du vent"
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
        }

        Text {
            Layout.row: 1
            Layout.column: 1
            text: qsTr("m/s")
            font.pointSize: 30
        }

        Text {
            id: textDixiemeVent
            Layout.row: 2
            Layout.column: 1
            text: dixiemeVent
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            clip: true
            transformOrigin: Item.TopLeft
            font.pointSize: 50
        }
    }
}



