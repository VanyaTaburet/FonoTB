#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onTextMessageReceived(const QString &message);

private:
    QString getUserName();
    void updateUserList(const QStringList &users);
    
    // Добавляем метод для загрузки .env
    bool loadEnv(QString &ip, int &port);

    // Добавляем переменные для хранения IP и порта
    QString serverIp;
    int serverPort;

    QWebSocket *m_webSocket;
    QPushButton *connectButton;
    QScrollArea *userScrollArea;
    QWidget *userListWidget;
    QVBoxLayout *userListLayout;
};

#endif // MAINWINDOW_H
