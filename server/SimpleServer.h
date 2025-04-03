#ifndef SIMPLEWEBSOCKETSERVER_H
#define SIMPLEWEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>
#include <QString>

class SimpleWebSocketServer : public QObject
{
    Q_OBJECT

public:
    explicit SimpleWebSocketServer(QObject *parent = nullptr);
    ~SimpleWebSocketServer();

    void startServer();

private slots:
    void onNewConnection();
    void onTextMessageReceived(const QString &message);
    void onDisconnected();

private:
    QWebSocketServer *m_webSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // SIMPLEWEBSOCKETSERVER_H
