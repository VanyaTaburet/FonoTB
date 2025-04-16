// WebSocketClient.cpp
#include "WebSocketClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QJsonDocument make_json(const QString& type, const QString& key = QString(), const QString& value = QString()) {
    QJsonObject json;
    json["type"] = type;
    if (!key.isEmpty() && !value.isEmpty()) {
        json[key] = value;
    }
    return QJsonDocument(json);
}


WebSocketClient::WebSocketClient(QObject* parent) : QObject(parent) {
    qDebug() << "WebSocketClient constructor called";
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    qDebug() << "Signals and slots connected in WebSocketClient";
}

void WebSocketClient::connectToServer(const QString& url) {
    qDebug() << "Connecting to server:" << url;
    m_webSocket.open(QUrl(url));
}

void WebSocketClient::sendJsonMessage(const QString& type, const QString& name) {
    QJsonObject json;
    json["type"] = type;
    json["name"] = name;
    QJsonDocument doc(json);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    qDebug() << "Sending JSON message:" << jsonString;
    m_webSocket.sendTextMessage(jsonString);
}

WebSocketClient::~WebSocketClient() {
    qDebug() << "WebSocketClient destructor called";
}

void WebSocketClient::onConnected() {
    qDebug() << "WebSocket connected";
    emit connected();
    sendName();
    getTracks();
}

void WebSocketClient::onDisconnected() {
    qDebug() << "WebSocket disconnected";
    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString& message) {
    qDebug() << "Text message received in WebSocketClient: " << message;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    if (jsonObject["type"] == "tracks_list") {
        QJsonArray jsonTracks = jsonObject["tracks"].toArray();
        tracks.clear();
        std::vector<Track> newTracks;

        for (const QJsonValue& value : jsonTracks) {
            QJsonObject obj = value.toObject();
            Track track;
            track.id = obj["id"].toString();
            track.name = obj["name"].toString();
            track.comment = obj["comment"].toString();
            track.date = obj["date"].toString();
            newTracks.push_back(track);
        }

        qDebug() << "Tracks list updated. Total tracks:" << newTracks.size();
        emit tracksUpdated(newTracks);
    }
    else if (jsonObject["type"] == "track_users_list") {
        QJsonArray jsonTrackUsers = jsonObject["track_users"].toArray();

        for (const QJsonValue& value : jsonTrackUsers) {
            QJsonObject obj = value.toObject();
            QString trackId = obj["track_id"].toString();
            QJsonArray jsonUsers = obj["users"].toArray();
            std::vector<QString> users;

            for (const QJsonValue& userValue : jsonUsers) {
                users.push_back(userValue.toString());
            }

            for (Track& track : tracks) {
                if (track.id == trackId) {
                    track.users = users;
                    break;
                }
            }
        }

        qDebug() << "Track users list updated.";
    }

    emit messageReceived(message);
}

void WebSocketClient::sendName() {
    QString userName = qgetenv("USER");
    if (userName.isEmpty()) {
        userName = qgetenv("USERNAME");
    }
    qDebug() << "User name:" << userName;

    QJsonDocument jsonDoc = make_json("set_name", "name", userName);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Sending JSON message:" << jsonString;

    m_webSocket.sendTextMessage(jsonString);
}

void WebSocketClient::getTracks() {
    QJsonDocument jsonDoc = make_json("get_tracks");
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "Sending JSON message:" << jsonString;

    m_webSocket.sendTextMessage(jsonString);
}
