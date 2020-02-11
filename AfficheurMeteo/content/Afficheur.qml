import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {

    property string zone: ""
    property int temperature: 0
    property string dixieme: ".0"
    property int humidite: 0


    GridLayout
    {
        rows:1
        columns: 2

         GridLayout
         {
            id: gridTemperature
            rows: 3
            columns: 2
            Layout.leftMargin: 50

            Text {
                id: textZone
                Layout.row:  0
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.topMargin: 5
                text: zone
                font.pointSize: 20
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            }

            Text {
                id: textTemperature
                Layout.row:  1
                Layout.column: 0
                Layout.rowSpan: 2
                text: temperature
                font.pointSize: 100
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom

            }
            Text {
                id: textUnite
                Layout.row: 1
                Layout.column: 1
                text: qsTr("°C")
                font.pointSize: 30
            }
            Text {
                id: textDixieme
                Layout.row: 2
                Layout.column: 1
                text: dixieme
                Layout.alignment: Qt.AlignLeft
                clip: true
                transformOrigin: Item.TopLeft
                font.pointSize: 50
            }
        }

        GridLayout {
            id: gridHumidite
            rows: 3
            columns: 2
            Layout.leftMargin: 20

            Text
            {
                id: textHumidite
                Layout.row:  1
                Layout.column: 0
                Layout.rowSpan: 2
                text: humidite
                font.pointSize: 100
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            }
            Text
            {
                id: textPourcent
                Layout.row: 1
                Layout.column: 1
                text: qsTr("%")
                font.pointSize: 30
            }
        }
    }
}

