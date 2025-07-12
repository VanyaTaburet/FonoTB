#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class SimpleHttpFileServer : public QTcpServer
{
    Q_OBJECT
public:
    SimpleHttpFileServer(QObject* parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void handleRequest(QTcpSocket* socket, const QString& request);
    void sendFile(QTcpSocket* socket, const QString& filePath);
    void sendNotFound(QTcpSocket* socket);
};