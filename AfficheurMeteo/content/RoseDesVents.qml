import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import "afficheur.js" as Outils



Item {


    property int angleDuVent: 0
    property int vitesse: 0
    property string dixiemeVent: ".0"

    GridLayout {
        rows: 1
        columns: 2

        Image {
            id: boussole
            width: 400
            height: 400
            Layout.row: 0
            Layout.column: 0
            source: "boussole.jpg"

            Image {
                id: aiguille
                width: 80
                height: 150
                x: 155
                y:140
                source: "fleche.jpg"
                transform: Rotation
                {
                    origin.x: 40
                    origin.y: 52
                    angle : angleDuVent
                }
            }
        } // boussole


    }

}

