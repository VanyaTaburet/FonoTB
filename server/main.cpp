#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <clocale>
#include <QSettings>
#include "SimpleWebSocketServer.h"
#include "SimpleHttpFileServer.h"

// Глобальный объект для файла логов
QFile logFile;

void customLogMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QTextStream out(&logFile);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString logType;
    switch (type) {
    case QtDebugMsg:    logType = "DEBUG"; break;
    case QtInfoMsg:     logType = "INFO"; break;
    case QtWarningMsg:  logType = "WARNING"; break;
    case QtCriticalMsg: logType = "CRITICAL"; break;
    case QtFatalMsg:    logType = "FATAL"; break;
    }
    out << QString("[%1] [%2] %3 (%4:%5, %6)\n")
        .arg(timestamp, logType, msg, context.file ? context.file : "unknown_file",
            QString::number(context.line), context.function ? context.function : "unknown_function");
    out.flush();
    fprintf(stderr, "%s\n", msg.toLocal8Bit().constData());
    if (type == QtFatalMsg)
        abort();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    QCoreApplication a(argc, argv);

    // Открываем файл для записи логов
    logFile.setFileName("application.log");
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qCritical() << "Unable to open log file for writing!";
        return -1;
    }

    // Устанавливаем пользовательский обработчик логов
    qInstallMessageHandler(customLogMessageHandler);

    qDebug() << "Application started";

    // Чтение .env для IP и портов
    QString ipAddress = "127.0.0.1";
    quint16 httpPort = 8080;

    QFile envFile(".env");
    if (envFile.exists()) {
        QSettings settings(".env", QSettings::IniFormat);
        settings.setIniCodec("UTF-8");
        ipAddress = settings.value("IP", ipAddress).toString();
        httpPort = settings.value("HOST_HTTP", httpPort).toUInt();
        qDebug() << "Loaded HTTP server config from .env: IP =" << ipAddress << ", PORT =" << httpPort;
    }
    else {
        qWarning() << "No .env file found. Using default HTTP server settings.";
    }

    // --- WebSocket сервер ---
    SimpleWebSocketServer server;
    server.startServer();

    // --- HTTP сервер для файлов ---
    SimpleHttpFileServer httpServer;
    if (!httpServer.listen(QHostAddress(ipAddress), httpPort)) {
        qCritical() << "Failed to start HTTP file server!";
    }
    else {
        qInfo() << "HTTP file server started at http://" << ipAddress << ":" << httpPort << "/";
    }

    return a.exec();
}