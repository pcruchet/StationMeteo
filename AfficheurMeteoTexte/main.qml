import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtWebSockets 1.1

import "vent.js" as Vent

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Afficheur Météo")

    WebSocket {
        id: socket
        url: "ws://192.168.1.99:7777"
        onTextMessageReceived: {
            console.log(message);
            var obj=JSON.parse(message);
            var laZone = obj.Station;
            switch(laZone)
            {
            case 71:
                tempExt.text = obj.Temperature;
                humExt.text  = obj.Humidite;
                vitVent.text = obj.Vitesse;
                dirVent.text = Vent.obtenirDirectionDuVent(obj.Direction);
                rafVent.text = obj.Rafale;
                laPluie.text = obj.Pluie;
                break;
            case 169:
                tempSerre.text = obj.Temperature;
                humSerre.text  = obj.Humidite;
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


    Text {
        id: temperatureExterieure
        x: 20
        y: 50
        text: qsTr("Température extérieure :")
        font.pixelSize: 12
    }

    Text {
        id: tempExt
        x: 160
        y: 50
        text: qsTr("0.0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: uniteDegre
        x: 190
        y: 50
        text: qsTr(" °C")
        font.pixelSize: 12
    }


    Text {
        id: humiditeExterieure
        x: 20
        y: 70
        text: qsTr("Humidité extérieure : ")
        font.pixelSize: 12
    }

    Text {
        id: humExt
        x: 160
        y: 70
        text: qsTr("0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: unitePourcent
        x: 180
        y: 70
        text: qsTr(" %")
        font.pixelSize: 12
    }

    Text {
        id: temperatureSerre
        x: 20
        y: 90
        text: qsTr("Température serre :")
        font.pixelSize: 12
    }

    Text {
        id: tempSerre
        x: 160
        y: 90
        text: qsTr("0.0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: uniteDegre2
        x: 190
        y: 90
        text: qsTr(" °C")
        font.pixelSize: 12
    }


    Text {
        id: humiditeSerre
        x: 20
        y: 110
        text: qsTr("Humidité serre : ")
        font.pixelSize: 12
    }

    Text {
        id: humSerre
        x: 160
        y: 110
        text: qsTr("0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: unitePourcent2
        x: 180
        y: 110
        text: qsTr(" %")
        font.pixelSize: 12
    }

    Text {
        id: vitesseDuVent
        x: 20
        y: 150
        text: qsTr("Vitesse du vent : ")
        font.pixelSize: 12
    }

    Text {
        id: vitVent
        x: 160
        y: 150
        text: qsTr("0.0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: unitevent
        x: 180
        y: 150
        text: qsTr("    km/h")
        font.pixelSize: 12
    }

    Text {
        id: dirVent
        x: 240
        y: 150
        text: qsTr("")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: rafaleDuVent
        x: 20
        y: 170
        text: qsTr("Rafale : ")
        font.pixelSize: 12
    }

    Text {
        id: rafVent
        x: 160
        y: 170
        text: qsTr("0.0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: uniteVent2
        x: 180
        y: 170
        text: qsTr("    km/h")
        font.pixelSize: 12
    }

    Text {
        id: cumulPluie
        x: 20
        y: 210
        text: qsTr("Cumul de pluie dernière heure : ")
        font.pixelSize: 12
    }

    Text {
        id: laPluie
        x: 200
        y: 210
        text: qsTr("0.0")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: unitePluie
        x: 220
        y: 210
        text: qsTr("    mm/h")
        font.pixelSize: 12
    }
}
