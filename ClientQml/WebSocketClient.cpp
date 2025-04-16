#include "WebSocketClient.h"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSysInfo>
#include <QProcessEnvironment>

WebSocketClient::WebSocketClient(QObject* parent) : QObject(parent)
{
    qDebug() << "WebSocketClient constructor called";
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    qDebug() << "Signals and slots connected in WebSocketClient";
}

void WebSocketClient::connectToServer(const QString& url)
{
    qDebug() << "Connecting to server:" << url;
    m_webSocket.open(QUrl(url));
}

void WebSocketClient::sendJsonMessage(const QString& type, const QString& name)
{
    QJsonObject json;
    json["type"] = type;
    json["name"] = name;
    QJsonDocument doc(json);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    qDebug() << "Sending JSON message:" << jsonString;
    m_webSocket.sendTextMessage(jsonString);
}

WebSocketClient::~WebSocketClient()
{
    qDebug() << "WebSocketClient destructor called";
}

void WebSocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    emit connected();

    // Получаем имя пользователя
    QString userName = qgetenv("USER");
    if (userName.isEmpty()) {
        userName = qgetenv("USERNAME");
    }
    qDebug() << "User name:" << userName;

    // Отправляем JSON-сообщение
    sendJsonMessage("set_name", userName);
}

void WebSocketClient::onDisconnected()
{
    qDebug() << "WebSocket disconnected";
    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString& message)
{
    qDebug() << "Text message received in WebSocketClient: " << message;
    emit messageReceived(message);
}
