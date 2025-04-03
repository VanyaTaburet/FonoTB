#include "SimpleWebSocketServer.h"
#include <QWebSocket>
#include <QDebug>

SimpleWebSocketServer::SimpleWebSocketServer(QObject *parent) : QObject(parent),
    m_webSocketServer(nullptr)
{
}

SimpleWebSocketServer::~SimpleWebSocketServer()
{
    for (QWebSocket *client : qAsConst(m_clients)) {
        client->close();
        client->deleteLater();
    }
}

void SimpleWebSocketServer::startServer()
{
    m_webSocketServer = new QWebSocketServer(QStringLiteral("Simple WebSocket Server"),
                                             QWebSocketServer::NonSecureMode, this);

    if (m_webSocketServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << "WebSocket server started on port 1234";
        connect(m_webSocketServer, &QWebSocketServer::newConnection,
                this, &SimpleWebSocketServer::onNewConnection);
    } else {
        qDebug() << "Failed to start WebSocket server!";
    }
}

void SimpleWebSocketServer::onNewConnection()
{
    QWebSocket *clientSocket = m_webSocketServer->nextPendingConnection();
    m_clients.append(clientSocket);

    connect(clientSocket, &QWebSocket::textMessageReceived,
            this, &SimpleWebSocketServer::onTextMessageReceived);
    connect(clientSocket, &QWebSocket::disconnected,
            this, &SimpleWebSocketServer::onDisconnected);

    qDebug() << "New WebSocket connection established.";
}

void SimpleWebSocketServer::onTextMessageReceived(const QString &message)
{
    qDebug() << "Message received: " << message;

    // Пример: Эхо-сообщение
    for (QWebSocket *client : qAsConst(m_clients)) {
        client->sendTextMessage(message);  // Эхо-сообщение отправляем обратно
    }
}

void SimpleWebSocketServer::onDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        m_clients.removeAll(client);
        client->deleteLater();
        qDebug() << "Client disconnected.";
    }
}
