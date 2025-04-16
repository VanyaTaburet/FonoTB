#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <clocale> 
#include "SimpleWebSocketServer.h"

// Глобальный объект для файла логов
QFile logFile;

void customLogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток для записи в файл
    QTextStream out(&logFile);

    // Получаем текущую дату и время
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Определяем тип сообщения
    QString logType;
    switch (type) {
    case QtDebugMsg:
        logType = "DEBUG";
        break;
    case QtInfoMsg:
        logType = "INFO";
        break;
    case QtWarningMsg:
        logType = "WARNING";
        break;
    case QtCriticalMsg:
        logType = "CRITICAL";
        break;
    case QtFatalMsg:
        logType = "FATAL";
        break;
    }

    // Записываем сообщение в файл
    out << QString("[%1] [%2] %3 (%4:%5, %6)\n")
               .arg(timestamp, logType, msg, context.file ? context.file : "unknown_file",
                    QString::number(context.line), context.function ? context.function : "unknown_function");
    out.flush();

    // Также выводим сообщение в консоль
    fprintf(stderr, "%s\n", msg.toLocal8Bit().constData());

    // Если сообщение фатальное, завершаем приложение
    if (type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[])
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

    // Ваш основной код
    qDebug() << "This is a debug message";
    qWarning() << "This is a warning message";
    qCritical() << "This is a critical message";

    SimpleWebSocketServer server;
    server.startServer();


    return a.exec();
}