// WebSocketClient.h
#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include "Track.h"

class WebSocketClient : public QObject {
    Q_OBJECT

public:
    explicit WebSocketClient(QObject* parent = nullptr);
    ~WebSocketClient();

    Q_INVOKABLE void connectToServer(const QString& url);
    void sendJsonMessage(const QString& type, const QString& name);

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& message);
    void tracksUpdated(const std::vector<Track>& tracks);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);

private:
    void sendName();
    void getTracks();

    QWebSocket m_webSocket;
    std::vector<Track> tracks;
};

#endif // WEBSOCKETCLIENT_H
