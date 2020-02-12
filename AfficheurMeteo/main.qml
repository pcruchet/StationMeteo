import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtWebSockets 1.1
import "content"
import "content/afficheur.js" as Outils
import "content/AfficheurBeaufort.js" as Beaufort



Window {
    visible: true
    width: 1000
    height: 600
    property alias roseDesVents: roseDesVents
    property alias afficheurVent: afficheurVent
    property alias afficheurBeaufort: afficheurBeaufort
    property alias afficheurSerre: afficheurSerre
    property alias afficheurExterieur: afficheurExterieur

    title: qsTr("Afficheur Météo")

    WebSocket {
        id: socket
        url: "ws://192.168.1.22:7777"
        onTextMessageReceived: {
            console.log(message);
            var obj=JSON.parse(message);
            var laZone = obj.Station;
            var lesDixiemes = ""
            switch(laZone)
            {
            case 71:
                afficheurExterieur.humidite =  obj.Humidite;
                afficheurExterieur.temperature = Outils.obtenirTemperature(obj.Temperature);
                lesDixiemes = Outils.obtenirDixieme(obj.Temperature);
                afficheurExterieur.dixieme = Outils.ajouterPoint(lesDixiemes);
                roseDesVents.angleDuVent = obj.Direction;
                afficheurVent.vitesse = Outils.obtenirTemperature(obj.Vitesse);
                lesDixiemes = Outils.obtenirDixieme(obj.Vitesse);
                afficheurVent.dixiemeVent = Outils.ajouterPoint(lesDixiemes);

                Beaufort.obtenirAppelationVent(obj.Vitesse);
                Beaufort.afficherEchelleBeaufort(12,"white");
                var valBeaufort = Beaufort.obtenirBeaufort(obj.Vitesse)
                Beaufort.afficherEchelleBeaufort(valBeaufort,"red");
                afficheurBeaufort.textBeaufort = Beaufort.obtenirAppelationVent(valBeaufort)
                afficheurBeaufort.vitesseRafale=Outils.obtenirTemperature(obj.Rafale);
                lesDixiemes = Outils.obtenirDixieme(obj.Rafale);
                afficheurBeaufort.dixiemeRafale=Outils.ajouterPoint(lesDixiemes);
                break;
            case 169:
                afficheurSerre.humidite =  obj.Humidite;
                afficheurSerre.temperature = Outils.obtenirTemperature(obj.Temperature);
                lesDixiemes = Outils.obtenirDixieme(obj.Temperature);
                afficheurSerre.dixieme = Outils.ajouterPoint(lesDixiemes);
                break;
            }
        }
        onStatusChanged: if (socket.status === WebSocket.Error) {
                             console.log("Erreur: " + socket.errorString)
                         } else if (socket.status === WebSocket.Open) {
                             console.log("Connecté au serveur");
                         } else if (socket.status === WebSocket.Closed) {
                             console.log("Déconnecté par le serveur")
                         }
        active: true
    }

    GridLayout{
        id: gridMeteo
        anchors.fill: parent

        rows: 3
        columns: 2

        Rectangle{
            height: 195
            width:600
            color: "bisque"
            Layout.row: 0
            Layout.column: 0
            border.color: "black"
            border.width: 5
            radius: 5

            Afficheur{
                id: afficheurExterieur
                Layout.fillHeight: true
                zone: qsTr("Extérieur")
            }
        }

        Rectangle{
            height: 195
            width:600

            color: "beige"
            Layout.row: 1
            Layout.column: 0
            border.color: "black"
            border.width: 5
            radius: 5

            Afficheur{
                id: afficheurSerre
                zone: qsTr("Serre")
            }
        }

        Rectangle{
            height: 195
            width:600
            color: "azure"
            Layout.row: 2
            Layout.column: 0
            border.color: "black"
            border.width: 5
            radius: 5


            AfficheurBeaufort
            {
                id: afficheurBeaufort
                width: 300
            }
            AfficheurVent
            {
                id: afficheurVent
                anchors.left: afficheurBeaufort.right
            }




        }

        Rectangle{
            height: 195
            width:390

            color: "burlywood"
            Layout.row: 0
            Layout.column: 1
            border.color: "black"
            border.width: 5
            radius: 5

            AfficheurPluie{
                id: cumulPluie
            }

        }
        RoseDesVents{
            id: roseDesVents
            Layout.row: 1
            Layout.column: 1
            Layout.rowSpan: 2
            height: 400
            width: 400
        }




    }


}
