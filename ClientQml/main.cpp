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
            continue; // Пропускаем пустые строки и комментарии
        }

        QStringList parts = line.split('=', QString::SkipEmptyParts);
        if (parts.size() == 2) {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            qputenv(key.toUtf8(), value.toUtf8());
        }
    }
}

// Функция для перенаправления сообщений qDebug в файл
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

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    qInstallMessageHandler(customMessageHandler); // Устанавливаем обработчик сообщений

    // Загрузка переменных из .env файла
    loadEnvFile(".env");

    QQmlApplicationEngine engine;
    TrackModel trackModel;
    WebSocketClient* client = new WebSocketClient();
    engine.rootContext()->setContextProperty("webSocketClient", client);

    // Чтение переменной окружения
    QString serverUrl = qgetenv("WEBSOCKET_SERVER_URL");
    if (serverUrl.isEmpty()) {
        serverUrl = "ws://localhost:1234"; // Значение по умолчанию
    }
    engine.rootContext()->setContextProperty("serverUrl", serverUrl);
    engine.rootContext()->setContextProperty("trackModel", &trackModel);

    //QObject::connect(client, &WebSocketClient::tracksUpdated, [&trackModel](const std::vector<Track>& tracks) {
    //    trackModel.setTracks(tracks);
    //    });
    QObject::connect(client, &WebSocketClient::tracksUpdated, &trackModel, &TrackModel::setTracks);


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

    return app.exec();
}
