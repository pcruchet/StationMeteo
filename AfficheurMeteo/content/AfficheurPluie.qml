import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {

    property int cumulDePluie: 0
    property string cumulDixiemePluie: ".0"
    GridLayout {
        id: gridPluie
        rows: 3
        columns: 2
        Layout.row: 1
        Layout.column: 0

        Text {
            id: textPluie
            Layout.row:  1
            Layout.column: 0
            Layout.rowSpan: 2
            text: cumulDePluie
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
            text: "Cumul de pluie"
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
        }

        Text {
            Layout.row: 1
            Layout.column: 1
            text: qsTr("mm/h")
            font.pointSize: 30
        }

        Text {
            id: textDixiemePluie
            Layout.row: 2
            Layout.column: 1
            text: cumulDixiemePluie
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            clip: true
            transformOrigin: Item.TopLeft
            font.pointSize: 50
        }
    }

}
