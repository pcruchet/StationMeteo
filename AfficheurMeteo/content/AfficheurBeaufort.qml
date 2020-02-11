import QtQuick 2.0
import QtQuick.Layouts 1.3

Item
{
    property var tabEtiquette: ["1","2","3","4","5","6","7","8","9","10","11","12"]
    property string textBeaufort: qsTr("")
    property alias echelleBeaufort: echelleBeaufort
    property int vitesseRafale: 0
    property string dixiemeRafale: ".0"

    GridLayout
    {
        rows: 3
        columns: 2
        Layout.row: 5
        Layout.column: 0

        ColumnLayout{
            Layout.margins: 10
            RowLayout
            {
                Text
                {
                    Layout.fillWidth: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pointSize: 15
                    text: qsTr("Beaufort : ")
                }

                Text
                {
                    Layout.fillWidth: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                    font.pointSize: 15
                    text: textBeaufort
                }
            }
            RowLayout
            {
                spacing: 1
                Repeater
                {
                    id: echelleBeaufort
                    model: 12
                    Rectangle
                    {
                        width: 20
                        height: 20
                        border.width: 2
                        x: 20*index
                        y: 0
                        color: "white"
                        Text
                        {
                            text: tabEtiquette[index]
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.pointSize: 10
                            width: 18
                            height: 18
                        }
                    }
                }
            }
            RowLayout{
                Text{
                    Layout.row: 0
                    Layout.column: 0
                    Layout.columnSpan: 2
                    font.pointSize: 15
                    text: "Rafale "
                    Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                }

                GridLayout {
                    id: gridTemperature
                    rows: 2
                    columns: 2
                    Layout.row: 1
                    Layout.column: 0

                    Text {
                        id: textTemperature
                        Layout.row:  1
                        Layout.column: 0
                        Layout.rowSpan: 2
                        text: vitesseRafale
                        font.pointSize: 50
                        Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                        Layout.leftMargin: 30
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
                        text: dixiemeRafale
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        clip: true
                        transformOrigin: Item.TopLeft
                        font.pointSize: 30
                    }
                }
            }
        }
    }
}
