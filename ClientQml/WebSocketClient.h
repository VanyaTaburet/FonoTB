#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject* parent = nullptr);
    ~WebSocketClient();

public slots:
    void connectToServer(const QString& url);
    void sendJsonMessage(const QString& type, const QString& name);

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& message);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);

private:
    QWebSocket m_webSocket;
};

#endif // WEBSOCKETCLIENT_H

