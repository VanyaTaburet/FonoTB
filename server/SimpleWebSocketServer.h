#ifndef SIMPLEWEBSOCKETSERVER_H
#define SIMPLEWEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QStringList>
#include <QMap>

class SimpleWebSocketServer : public QObject
{
    Q_OBJECT

public:
    explicit SimpleWebSocketServer(QObject *parent = nullptr);
    ~SimpleWebSocketServer();

    void startServer();
    void broadcastMessage(const QString &message);
    void updateUserList();

private slots:
    void onNewConnection();
    void onTextMessageReceived(const QString &message);
    void onDisconnected();

private:
    QWebSocketServer *m_server;
    QMap<QWebSocket*, QString> m_clients; // Список всех подключенных клиентов и их имен
    void sendUserListToAll();
};

#endif // SIMPLEWEBSOCKETSERVER_H
