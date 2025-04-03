#include "MainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <QRegularExpression>

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_webSocket(new QWebSocket)
{
    // Загружаем IP и порт из .env
    if (!loadEnv(serverIp, serverPort)) {
        qDebug() << "Error: Failed to load .env file!";
        return;
    }

    qDebug() << "Loaded from .env: IP =" << serverIp << ", Port =" << serverPort;

    // Основной виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    this->resize(800, 600);

    // Главный layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Кнопка "Подключиться"
    connectButton = new QPushButton("Connect", this);
    mainLayout->addWidget(connectButton);
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);

    // ScrollArea для списка пользователей
    userScrollArea = new QScrollArea(this);
    userScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(userScrollArea);

    // Виджет-контейнер для списка пользователей
    userListWidget = new QWidget();
    userListLayout = new QVBoxLayout(userListWidget);
    userListWidget->setLayout(userListLayout);
    userScrollArea->setWidget(userListWidget);

    // Подключаем WebSocket
    connect(m_webSocket, &QWebSocket::connected, this, [this]() {
        QString userName = getUserName();
        QString setNameMessage = QString("SET_NAME %1").arg(userName);
        m_webSocket->sendTextMessage(setNameMessage);
    });

    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::onTextMessageReceived);
}

MainWindow::~MainWindow()
{
    delete m_webSocket;
}

void MainWindow::onConnectClicked()
{
    QString url = QString("ws://%1:%2").arg(serverIp).arg(serverPort);
    qDebug() << "Connecting to" << url;
    m_webSocket->open(QUrl(url));
}

void MainWindow::onTextMessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON: " << message;
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if (jsonObj.contains("type") && jsonObj["type"].toString() == "user_list") {
        QJsonArray usersArray = jsonObj["users"].toArray();
        QStringList users;
        for (const auto &user : usersArray) {
            users.append(user.toString());
        }
        updateUserList(users);
    }
}

QString MainWindow::getUserName()
{
#ifdef _WIN32
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(username, &username_len);
    return QString(username);
#else
    struct passwd *pw = getpwuid(getuid());
    return pw ? QString(pw->pw_name) : "UnknownUser";
#endif
}

void MainWindow::updateUserList(const QStringList &users)
{
    // Удаляем старые виджеты
    QLayoutItem *child;
    while ((child = userListLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Добавляем новых пользователей
    for (const QString &user : users) {
        QTextBrowser *userField = new QTextBrowser();
        userField->setText(user);
        userField->setFixedHeight(30);
        userListLayout->addWidget(userField);
    }
}

bool MainWindow::loadEnv(QString &ip, int &port) {
    QFile file(".env");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open .env file!";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        
        // Парсим строку "IP=192.168.3.8"
        QRegularExpression ipRegex(R"(IP\s*=\s*\"?([\d\.]+)\"?)");
        QRegularExpressionMatch ipMatch = ipRegex.match(line);
        if (ipMatch.hasMatch()) {
            ip = ipMatch.captured(1);
        }

        // Парсим строку "PORT=5678"
        QRegularExpression portRegex(R"(PORT\s*=\s*\"?(\d+)\"?)");
        QRegularExpressionMatch portMatch = portRegex.match(line);
        if (portMatch.hasMatch()) {
            port = portMatch.captured(1).toInt();  // Преобразуем строку в число
        }
    }

    file.close();

    // Проверяем, загрузились ли значения
    if (ip.isEmpty() || port <= 0) {
        qDebug() << "Error: Invalid IP or Port from .env";
        return false;
    }

    qDebug() << "Loaded from .env: IP =" << ip << ", Port =" << port;
    return true;
}