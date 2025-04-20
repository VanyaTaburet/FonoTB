#include "SimpleWebSocketServer.h"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QFile>

#include "TrackRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QUuid>


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
	
    if (!connectToDatabase()) {
        return ; // Выход из приложения, если подключение не удалось
    }

    //connectToDatabase(); // Добавлено

    QString ipAddress = "192.168.3.8";
    quint16 port = 1234;

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

    m_clients[socket] = QString("Unknown");

    qDebug() << "New connection from" << m_clients[socket];

    broadcastMessage(QString("%1 has joined the server").arg(m_clients[socket]));

    sendUserListToAll();
}

// Функция для парсинга JSON
QJsonObject SimpleWebSocketServer::parseJson(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON received:" << message;
        return QJsonObject();
    }
    return jsonDoc.object();
}

void SimpleWebSocketServer::onTextMessageReceived(const QString& message) {
    QWebSocket* senderSocket = qobject_cast<QWebSocket*>(sender());
    if (!senderSocket) {
        qWarning() << "Received message from an unknown sender.";
        return;
    }

    qDebug() << "Message received from client:" << message;

    QJsonObject jsonMessage = parseJson(message);
    if (jsonMessage.isEmpty()) {
        qWarning() << "Failed to parse message. Invalid JSON format.";
        return;
    }

    QString type = jsonMessage["type"].toString();
    qDebug() << "Message type:" << type;

    if (type == "set_name") {
        QString name = jsonMessage["name"].toString().trimmed();
        if (!name.isEmpty()) {
            qDebug() << "User changed name to" << name;
            m_clients[senderSocket] = name;
            broadcastMessage(QString("%1 has joined the server").arg(name));
            sendUserListToAll();
        }
        else {
            qWarning() << "Received empty name in set_name message.";
        }
    }
    else if (type == "message") {
        QString userMessage = jsonMessage["message"].toString();
        qDebug() << "Received message from" << m_clients[senderSocket] << ": " << userMessage;
        broadcastMessage(QString("%1: %2").arg(m_clients[senderSocket]).arg(userMessage));
    }
    else if (type == "get_tracks") {
        qDebug() << "Received request for all tracks from" << m_clients[senderSocket];

        QJsonArray tracksArray;
        TrackRepository repo(m_database); // Передаем объект базы данных в репозиторий
        qDebug() << "send Database query";
        auto tracks = repo.getAllTracks();

        qDebug() << "Fetched" << tracks.size() << "tracks from repository.";

        for (const auto& track : tracks) {
            if (track.size() < 4) {
                qWarning() << "Invalid track data format:" << track;
                continue;
            }

            QJsonObject trackObject;
            trackObject["id"] = track[0];
            trackObject["name"] = track[1];
            trackObject["date"] = track[2];
            trackObject["comment"] = track[3];
            tracksArray.append(trackObject);

            qDebug() << "Processed track:" << trackObject;
        }

        QJsonObject response;
        response["type"] = "tracks_list";
        response["tracks"] = tracksArray;

        QString responseStr = QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact));
        qDebug() << "Sending tracks list response to client:" << responseStr;

        senderSocket->sendTextMessage(responseStr);
    }
    else if (type == "debug_create_track") {
        qDebug() << "Received request to create a new track";

        QString sysname = jsonMessage["sysname"].toString();
        QString comment = jsonMessage["comment"].toString();

        TrackRepository repo(m_database);
        if (repo.addTrack(sysname, comment)) {
            qDebug() << "Track successfully created";
            QJsonObject response;
            response["type"] = "debug_create_track_response";
            response["status"] = "success";
            senderSocket->sendTextMessage(QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact)));
        }
        else {
            qDebug() << "Failed to create track";
            QJsonObject response;
            response["type"] = "debug_create_track_response";
            response["status"] = "failure";
            senderSocket->sendTextMessage(QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact)));
        }
    }
    else if (type == "add_user_to_track") {
        qDebug() << "Received request to add user to track";

        QString trackId = jsonMessage["track_id"].toString();
        QString user = jsonMessage["user"].toString();

        if (!trackId.isEmpty() && !user.isEmpty()) {
            if (!m_trackUsers[trackId].contains(user)) {
                m_trackUsers[trackId].append(user);
                qDebug() << "User" << user << "added to track" << trackId;
            }
            else {
                qDebug() << "User" << user << "already exists in track" << trackId;
            }

            QJsonObject response;
            response["type"] = "track_users_list";
            QJsonArray trackUsersArray;
            for (auto it = m_trackUsers.begin(); it != m_trackUsers.end(); ++it) {
                QJsonObject trackUsers;
                trackUsers["track_id"] = it.key();
                trackUsers["users"] = QJsonArray::fromStringList(it.value());
                trackUsersArray.append(trackUsers);
            }
            response["track_users"] = trackUsersArray;

            QString responseStr = QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact));
            broadcastMessage(responseStr);
        }
        else {
            qDebug() << "Failed to add user to track";
            QJsonObject response;
            response["type"] = "add_user_to_track";
            response["status"] = "failure";
            senderSocket->sendTextMessage(QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact)));
        }
    }

    else if (type == "remove_user") {
        qDebug() << "Received request to remove user";

        QString userId = jsonMessage["user"].toString();

        if (!userId.isEmpty()) {
            bool userFound = false;
            for (auto it = m_trackUsers.begin(); it != m_trackUsers.end(); ++it) {
                if (it.value().removeAll(userId) > 0) {
                    userFound = true;
                    qDebug() << "User" << userId << "removed from track" << it.key();
                }
            }

            QJsonObject response;
            response["type"] = "track_users_list";
            QJsonArray trackUsersArray;
            for (auto it = m_trackUsers.begin(); it != m_trackUsers.end(); ++it) {
                QJsonObject trackUsers;
                trackUsers["track_id"] = it.key();
                trackUsers["users"] = QJsonArray::fromStringList(it.value());
                trackUsersArray.append(trackUsers);
            }
            response["track_users"] = trackUsersArray;

            QString responseStr = QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact));
            broadcastMessage(responseStr);
        }
        else {
            qDebug() << "Failed to remove user";
            QJsonObject response;
            response["type"] = "remove_user";
            response["status"] = "failure";
            senderSocket->sendTextMessage(QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact)));
        }
    }
    else if (type == "get_track_users") {
        qDebug() << "Received request for track users";

        QJsonArray trackUsersArray;
        for (auto it = m_trackUsers.begin(); it != m_trackUsers.end(); ++it) {
            QJsonObject trackObject;
            trackObject["track_id"] = it.key();
            trackObject["users"] = QJsonArray::fromStringList(it.value());
            trackUsersArray.append(trackObject);
        }

        QJsonObject response;
        response["type"] = "track_users_list";
        response["track_users"] = trackUsersArray;

        QString responseStr = QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact));
        qDebug() << "Sending track users list response to client:" << responseStr;

        senderSocket->sendTextMessage(responseStr);
    }
    else {
        qWarning() << "Unknown message type:" << type;
    }
}






void SimpleWebSocketServer::onDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        QString userName = m_clients.take(socket);
        qDebug() << userName << "disconnected";

        broadcastMessage(QString("%1 has left the server").arg(userName));

        sendUserListToAll();

        socket->deleteLater();
    }
}

void SimpleWebSocketServer::broadcastMessage(const QString& message)
{
    for (QWebSocket* client : m_clients.keys()) {
        client->sendTextMessage(message);
    }
}


void SimpleWebSocketServer::sendUserListToAll()
{
    QJsonObject jsonMessage;
    QJsonArray userArray;

    for (const auto &name : m_clients.values()) {
        userArray.append(name);
    }

    jsonMessage["type"] = "user_list";
    jsonMessage["users"] = userArray;

    QString userListMessage = QString::fromUtf8(QJsonDocument(jsonMessage).toJson(QJsonDocument::Compact));

    broadcastMessage(userListMessage);
}

bool SimpleWebSocketServer::connectToDatabase() {
    QFile envFile(".env");
    if (!envFile.exists()) {
        qCritical() << "No .env file found. Cannot load database settings.";
        return false;
    }

    QSettings settings(".env", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    QString host = settings.value("DB_HOST", "localhost").toString();
    int port = settings.value("DB_PORT", 5432).toInt();
    QString dbName = settings.value("DB_NAME", "").toString();
    QString user = settings.value("DB_USER", "").toString();
    QString password = settings.value("DB_PASSWORD", "").toString();

    if (dbName.isEmpty() || user.isEmpty()) {
        qCritical() << "Missing required database settings in .env file.";
        return false;
    }

    qDebug() << "Database Settings:";
    qDebug() << "DBHost:" << host;
    qDebug() << "DBPort:" << port;
    qDebug() << "DBName:" << dbName;
    qDebug() << "DBUser:" << user;

    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        qCritical() << "The QPSQL driver is unavailable!";
        return false;
    }

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open()) {
        qCritical() << "Database connection error:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Database connection successful. Ready to work.";
    m_database = m_db; // Сохраняем объект базы данных в члене класса
    return true;
}

void SimpleWebSocketServer::showAllRecords(TrackRepository& repo)
{
    auto tracks = repo.getAllTracks(); // Получаем все треки из базы данных
    if (tracks.isEmpty()) {
        qDebug() << "There are no records in the database.";
        return;
    }

    qDebug() << "\nList of all entries:";
    qDebug() << "ID\tTitle\tDate\tСomment";
    qDebug() << "----------------------------------------";
    for (const auto& track : tracks) {
        qDebug() << track[0] << "\t" << track[1].left(10) << "\t"
                 << track[2] << "\t" << track[3];
    }
}