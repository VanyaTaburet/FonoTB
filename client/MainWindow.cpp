#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QWebSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_webSocket(new QWebSocket), userModel(new QStringListModel(this)) {
    ui->setupUi(this);

    // Logging
    qDebug() << "MainWindow: Constructor called.";

    // Create QQmlApplicationEngine instance
    QQmlApplicationEngine engine;

    // Expose the current instance of MainWindow to QML as webSocketClient
    engine.rootContext()->setContextProperty("webSocketClient", this);

    // Load the QML file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Connect WebSocket signals
    connect(m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::onTextMessageReceived);

    // Connect the button
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    qDebug() << "MainWindow: Connection established and button connected.";
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_webSocket;
    qDebug() << "MainWindow: Destructor called.";
}

void MainWindow::onConnectButtonClicked() {
    qDebug() << "MainWindow: 'Connect' button clicked.";
    // Open WebSocket connection
    m_webSocket->open(QUrl("ws://192.168.31.94:1234")); // WebSocket server address
}

void MainWindow::onConnected() {
    qDebug() << "MainWindow: WebSocket connected.";
    QString userName = "saveliy123"; // Example username
    m_webSocket->sendTextMessage("SET_NAME " + userName);
}

void MainWindow::onTextMessageReceived(const QString &message) {
    qDebug() << "MainWindow: Received message: " << message;

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj["type"].toString() == "user_list") {
            parseUserList(message);
        }
    }
}

void MainWindow::parseUserList(const QString &jsonMessage) {
    qDebug() << "MainWindow: Parsing user list.";

    QJsonDocument doc = QJsonDocument::fromJson(jsonMessage.toUtf8());
    QJsonObject obj = doc.object();
    
    if (obj.contains("users") && obj["users"].isArray()) {
        QJsonArray usersArray = obj["users"].toArray();
        QStringList userList;
        
        for (const QJsonValue &val : usersArray) {
            userList.append(val.toString());
        }
        
        // Update the model in QML via signal
        emit userListUpdated(userList);  // This will emit the signal
    }
}
