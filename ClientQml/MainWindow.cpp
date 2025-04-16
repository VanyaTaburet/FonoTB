#include "MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(WebSocketClient* client, QWidget* parent)
    : QMainWindow(parent),
    m_webSocketClient(client),
    connectButton(new QPushButton("Connect")),
    userScrollArea(new QScrollArea),
    userListWidget(new QWidget),
    userListLayout(new QVBoxLayout),
    serverIp("127.0.0.1"),
    serverPort(12345)
{
    qDebug() << "MainWindow constructor called";
    loadEnv();
    qDebug() << "Initializing UI components";
    // Инициализация UI компонентов
    qDebug() << "UI components initialized";
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    qDebug() << "Signals and slots connected in MainWindow";
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor called";
}

void MainWindow::loadEnv() {
    QFile file(".env");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open .env file";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('=');
        if (parts.size() == 2) {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            if (key == "SERVER_IP") {
                serverIp = value;
            }
            else if (key == "SERVER_PORT") {
                serverPort = value.toInt();
            }
        }
    }

    if (serverIp.isEmpty()) {
        qDebug() << "SERVER_IP not found";
        serverIp = "127.0.0.1";
    }
    if (serverPort == 0) {
        qDebug() << "SERVER_PORT not found";
        serverPort = 1234;
    }

    qDebug() << "Loaded IP and port from .env file:" << serverIp << ":" << serverPort;
}

void MainWindow::onConnectClicked() {
    QString url = QString("ws://%1:%2").arg(serverIp).arg(serverPort);
    qDebug() << "Connecting to WebSocket server at" << url;
    m_webSocketClient->connectToServer(url);
}


void MainWindow::onTextMessageReceived(const QString& message) {
    // Логика обработки полученного текстового сообщения
}

QString MainWindow::getUserName() {
    // Логика получения имени пользователя
    return QString();
}

void MainWindow::updateUserList(const QStringList& users) {
    // Логика обновления списка пользователей
}

