#include "SimpleWebSocketServer.h"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QFile>

SimpleWebSocketServer::SimpleWebSocketServer(QObject *parent)
    : QObject(parent),
      m_server(new QWebSocketServer(QStringLiteral("Simple WebSocket Server"),
                                    QWebSocketServer::NonSecureMode, this))
{
}

SimpleWebSocketServer::~SimpleWebSocketServer()
{
    m_server->close();
    qDeleteAll(m_clients.keys());
}

void SimpleWebSocketServer::startServer()
{
    // Загружаем настройки из .env
    QString ipAddress = "192.168.31.94"; // Значение по умолчанию
    quint16 port = 1234;                 // Значение по умолчанию

    QFile envFile(".env");
    if (envFile.exists()) {
        QSettings settings(".env", QSettings::IniFormat);
        settings.setIniCodec("UTF-8");

        ipAddress = settings.value("IP", ipAddress).toString();
        port = settings.value("HOST", port).toUInt();

        qDebug() << "Loaded from .env: IP =" << ipAddress << ", Port =" << port;
    } else {
        qDebug() << "No .env file found. Using default settings: IP =" << ipAddress << ", Port =" << port;
    }

    if (m_server->listen(QHostAddress(ipAddress), port)) {
        qDebug() << "Server started at" << ipAddress << ":" << port;
        connect(m_server, &QWebSocketServer::newConnection, this, &SimpleWebSocketServer::onNewConnection);
    } else {
        qDebug() << "Failed to start server!";
    }
}

void SimpleWebSocketServer::onNewConnection()
{
    QWebSocket *socket = m_server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &SimpleWebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &SimpleWebSocketServer::onDisconnected);

    // Пока клиент не установил имя, ему назначаем временное имя
    m_clients[socket] = QString("Unknown");

    qDebug() << "New connection from" << m_clients[socket];

    // Уведомляем всех о новом подключении
    broadcastMessage(QString("%1 has joined the server").arg(m_clients[socket]));

    // Отправляем всем текущий список пользователей
    sendUserListToAll();
}

void SimpleWebSocketServer::onTextMessageReceived(const QString &message)
{
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    if (senderSocket) {
        if (message.startsWith("SET_NAME")) {
            // Обрабатываем установку имени
            QString name = message.mid(9).trimmed(); // Ожидаем, что сообщение будет вида "SET_NAME имя"
            if (!name.isEmpty()) {
                qDebug() << "User changed name to" << name;
                m_clients[senderSocket] = name;
                broadcastMessage(QString("%1 has joined the server").arg(name));
                // Отправляем обновленный список
                sendUserListToAll();
            }
        } else {
            // Передаем сообщение всем подключенным клиентам
            qDebug() << "Received message from" << m_clients[senderSocket] << ": " << message;
            broadcastMessage(QString("%1: %2").arg(m_clients[senderSocket]).arg(message));
        }
    }
}

void SimpleWebSocketServer::onDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        QString userName = m_clients.take(socket);
        qDebug() << userName << "disconnected";

        // Уведомляем всех пользователей о выходе
        broadcastMessage(QString("%1 has left the server").arg(userName));

        // Отправляем обновленный список пользователей
        sendUserListToAll();

        socket->deleteLater();
    }
}

void SimpleWebSocketServer::broadcastMessage(const QString &message)
{
    for (QWebSocket *client : m_clients.keys()) {
        client->sendTextMessage(message);
    }
}

void SimpleWebSocketServer::sendUserListToAll()
{
    QJsonObject jsonMessage;
    QJsonArray userArray;

    // Заполняем массив пользователей
    for (const auto &name : m_clients.values()) {
        userArray.append(name);
    }

    // Формируем JSON-объект
    jsonMessage["type"] = "user_list";
    jsonMessage["users"] = userArray;

    // Преобразуем в строку JSON
    QString userListMessage = QString::fromUtf8(QJsonDocument(jsonMessage).toJson(QJsonDocument::Compact));

    // Отправляем всем клиентам
    broadcastMessage(userListMessage);
}
