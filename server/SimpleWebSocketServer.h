#ifndef SIMPLEWEBSOCKETSERVER_H
#define SIMPLEWEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QHash>
#include <QSqlDatabase>
#include <QMap>
#include <QStringList>

class TrackRepository; // Forward declaration

class SimpleWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit SimpleWebSocketServer(QObject* parent = nullptr);
    ~SimpleWebSocketServer();

    void startServer();
    void showAllRecords(TrackRepository& repo);
    void sendTrackUsersToAll();

private slots:
    void onNewConnection();
    void onTextMessageReceived(const QString& message);
    void onDisconnected();

private:
    void broadcastMessage(const QString& message);
    void sendUserListToAll();
    bool connectToDatabase();
    QJsonObject parseJson(const QString& message);

    QWebSocketServer* m_server;
    QHash<QWebSocket*, QString> m_clients;
    QSqlDatabase m_database;
    QMap<QString, QStringList> m_trackUsers; // Добавляем новый член класса
};

#endif // SIMPLEWEBSOCKETSERVER_H

