#ifndef SERVEURMETEO_H
#define SERVEURMETEO_H

#include <QObject>

#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QtWebSockets>


class ServeurMeteo : public QObject
{
    Q_OBJECT
public:
    explicit ServeurMeteo(quint16 _port, QObject *parent = nullptr);
    ~ServeurMeteo();
    void EnvoyerMessageTexte(QString message);

signals:

private slots:
    void onNewConnection();
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // SERVEURMETEO_H
