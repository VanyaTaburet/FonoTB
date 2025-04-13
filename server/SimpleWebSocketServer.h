#ifndef SIMPLEWEBSOCKETSERVER_H
#define SIMPLEWEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QStringList>
#include <QMap>
#include <QJsonObject>
#include <QSqlDatabase>

class TrackRepository; // Forward declaration

class SimpleWebSocketServer : public QObject
{
    Q_OBJECT

public:
    explicit SimpleWebSocketServer(QObject* parent = nullptr);
    ~SimpleWebSocketServer();

    void startServer();
    void broadcastMessage(const QString& message);
    void updateUserList();
    bool connectToDatabase(); // Подключение к базе данных
    void showAllRecords(TrackRepository& repo); // Отображение всех записей из базы данных

private slots:
    void onNewConnection();
    void onTextMessageReceived(const QString& message);
    void onDisconnected();

private:
    QWebSocketServer* m_server;
    QMap<QWebSocket*, QString> m_clients; // Список всех подключенных клиентов и их имен
    QSqlDatabase m_database;

    void sendUserListToAll();
    QJsonObject parseJson(const QString& message); // Функция для парсинга JSON
};

#endif // SIMPLEWEBSOCKETSERVER_H