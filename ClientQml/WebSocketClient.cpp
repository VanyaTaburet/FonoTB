#include "WebSocketClient.h"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSysInfo>
#include <QProcessEnvironment>
#include <QJsonArray>

struct Track {
    QString id;
    QString name;
    QString comment;
    QString date;
    std::vector<QString> users;
};

std::vector<Track> tracks;

void addToJson(QJsonObject&) {}

template<typename T, typename... Args>
void addToJson(QJsonObject& obj, const QString& key, const T& value, const Args&... args) {
    obj.insert(key, QJsonValue::fromVariant(QVariant::fromValue(value)));
    addToJson(obj, args...);
}

template<typename... Args>
QJsonDocument make_json(const QString& typeValue, const Args&... args) {
    static_assert(sizeof...(args) % 2 == 0, "Arguments must be in key-value pairs");

    QJsonObject obj;
    obj.insert("type", typeValue);
    addToJson(obj, args...);

    return QJsonDocument(obj);
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

        for (const QJsonValue& value : jsonTracks) {
            QJsonObject obj = value.toObject();
            Track track;
            track.id = obj["id"].toString();
            track.name = obj["name"].toString();
            track.comment = obj["comment"].toString();
            track.date = obj["date"].toString();
            tracks.push_back(track);
        }

        qDebug() << "Tracks list updated. Total tracks:" << tracks.size();
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
