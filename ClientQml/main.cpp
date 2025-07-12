// main.cpp
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QProcessEnvironment>
#include "WebSocketClient.h"
#include "TrackModel.h"

void loadEnvFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open .env file:" << filePath;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) {
            continue; // Ïðîïóñêàåì ïóñòûå ñòðîêè è êîììåíòàðèè
        }

        QStringList parts = line.split('=', Qt::SkipEmptyParts);
        if (parts.size() == 2) {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            qputenv(key.toUtf8(), value.toUtf8());
        }
    }
}

// Ôóíêöèÿ äëÿ ïåðåíàïðàâëåíèÿ ñîîáùåíèé qDebug â ôàéë
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    static QFile logFile("application.log");
    if (!logFile.isOpen()) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    QTextStream out(&logFile);
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    switch (type) {
    case QtDebugMsg:
        out << timeStamp << " - DEBUG: " << msg << "\n";
        break;
    case QtInfoMsg:
        out << timeStamp << " - INFO: " << msg << "\n";
        break;
    case QtWarningMsg:
        out << timeStamp << " - WARNING: " << msg << "\n";
        break;
    case QtCriticalMsg:
        out << timeStamp << " - CRITICAL: " << msg << "\n";
        break;
    case QtFatalMsg:
        out << timeStamp << " - FATAL: " << msg << "\n";
        abort();
    }
    out.flush();
}

void sendMessageOnExit(WebSocketClient* client) {
    qDebug() << "Application is closing. Sending message to server.";
    client->removeUser(); // Îòïðàâêà ñîîáùåíèÿ íà ñåðâåð
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    qInstallMessageHandler(customMessageHandler); // Óñòàíàâëèâàåì îáðàáîò÷èê ñîîáùåíèé

    // Çàãðóçêà ïåðåìåííûõ èç .env ôàéëà
    loadEnvFile(".env");

    QQmlApplicationEngine engine;
    TrackModel trackModel;
    WebSocketClient* client = new WebSocketClient();
    engine.rootContext()->setContextProperty("webSocketClient", client);

    // ×òåíèå ïåðåìåííîé îêðóæåíèÿ
    QString serverUrl = qgetenv("WEBSOCKET_SERVER_URL");
    if (serverUrl.isEmpty()) {
        serverUrl = "ws://localhost:1234"; // Çíà÷åíèå ïî óìîë÷àíèþ
    }
    engine.rootContext()->setContextProperty("serverUrl", serverUrl);
    engine.rootContext()->setContextProperty("trackModel", &trackModel);

    QObject::connect(client, &WebSocketClient::tracksUpdated, &trackModel, &TrackModel::setTracks);
    QObject::connect(client, &WebSocketClient::trackUsersUpdated, &trackModel, &TrackModel::updateTrackUsers);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    qDebug() << "Loading QML file:" << url;
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML file:" << url;
        return -1;
    }

    // Ïîäêëþ÷àåì ñèãíàë aboutToQuit ê ñëîòó sendMessageOnExit
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&client]() {
        sendMessageOnExit(client);
        });

    return app.exec();
}
