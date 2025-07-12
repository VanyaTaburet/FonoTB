#include "SimpleHttpFileServer.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>

SimpleHttpFileServer::SimpleHttpFileServer(QObject* parent)
    : QTcpServer(parent)
{
    // Nothing extra
}

void SimpleHttpFileServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &SimpleHttpFileServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &SimpleHttpFileServer::onDisconnected);
}

void SimpleHttpFileServer::onReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    QByteArray requestData = socket->readAll();
    QString request(requestData);

    // Ïðîñòåéøèé ïàðñåð ïåðâîé ñòðîêè HTTP GET çàïðîñà
    QStringList lines = request.split("\r\n");
    if (lines.isEmpty())
        return;

    QStringList requestParts = lines[0].split(' ');
    if (requestParts.size() < 2)
        return;

    QString method = requestParts[0];
    QString path = requestParts[1];

    if (method == "GET") {
        handleRequest(socket, path);
    }
}

void SimpleHttpFileServer::handleRequest(QTcpSocket* socket, const QString& path)
{
    // Ïðèìåð: /track_001.wav
    QString fileName = path;
    if (fileName.startsWith('/'))
        fileName = fileName.mid(1);

    // Áåçîïàñíîñòü: íå äà¸ì âûõîäèòü â ðîäèòåëüñêèå äèðåêòîðèè
    if (fileName.contains("..")) {
        sendNotFound(socket);
        return;
    }

    // Ïóñòü ìóçûêà ëåæèò â ./tracks/
    QString filePath = QDir("tracks").filePath(fileName);
    sendFile(socket, filePath);
}

void SimpleHttpFileServer::sendFile(QTcpSocket* socket, const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        sendNotFound(socket);
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    // Îïðåäåëÿåì Content-Type (òîëüêî äëÿ .wav, ìîæíî ðàñøèðèòü)
    QString contentType = "audio/wav";
    if (filePath.endsWith(".mp3", Qt::CaseInsensitive))
        contentType = "audio/mpeg";

    QByteArray response;
    response.append("HTTP/1.1 200 OK\r\n");
    response.append("Content-Type: " + contentType.toUtf8() + "\r\n");
    response.append("Content-Length: " + QByteArray::number(data.size()) + "\r\n");
    response.append("Connection: close\r\n");
    response.append("\r\n");
    response.append(data);

    socket->write(response);
    socket->disconnectFromHost();
}

void SimpleHttpFileServer::sendNotFound(QTcpSocket* socket)
{
    QByteArray response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found";
    socket->write(response);
    socket->disconnectFromHost();
}

void SimpleHttpFileServer::onDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
        socket->deleteLater();
}