#include "MainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>

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
    // Основной виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
	
	this->resize(800,600);

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
    m_webSocket->open(QUrl("ws://192.168.31.94:1234"));
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
