#include "serveurmeteo.h"
#include <QDebug>

ServeurMeteo::ServeurMeteo(quint16 _port, QObject *parent) : QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Station Météo"),
                                            QWebSocketServer::NonSecureMode, this))
{
    dernierMessage.clear();
    if (m_pWebSocketServer->listen(QHostAddress::Any, _port))
    {
        connect(m_pWebSocketServer,&QWebSocketServer::newConnection,this,&ServeurMeteo::onNewConnection);
    }
}

ServeurMeteo::~ServeurMeteo()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(),m_clients.end());
}

void ServeurMeteo::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket,&QWebSocket::disconnected,this,&ServeurMeteo::socketDisconnected);
    m_clients << pSocket ;
    qDebug() << "Connexion d'un client";
    emit nouvelleConnexionClient();
}

void ServeurMeteo::EnvoyerMessageTexte(QString message)
{
    QWebSocket *pClient ;
    qDebug() << message;
    foreach (pClient, m_clients) {
        pClient->sendTextMessage(message);
    }
    dernierMessage = message;
}

void ServeurMeteo::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
