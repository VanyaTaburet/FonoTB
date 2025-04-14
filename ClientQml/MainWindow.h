#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "WebSocketClient.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(WebSocketClient* client, QWidget* parent = nullptr);
    ~MainWindow();

private:
    void loadEnv();
    void onConnectClicked();
    void onTextMessageReceived(const QString& message);
    QString getUserName();
    void updateUserList(const QStringList& users);

    WebSocketClient* m_webSocketClient;
    QPushButton* connectButton;
    QScrollArea* userScrollArea;
    QWidget* userListWidget;
    QVBoxLayout* userListLayout;
    QString serverIp;
    int serverPort;
};

#endif // MAINWINDOW_H

