#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void userListUpdated(const QStringList &userList);  // Signal definition

private slots:
    void onConnectButtonClicked();
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void parseUserList(const QString &jsonMessage);

private:
    Ui::MainWindow *ui;
    QWebSocket *m_webSocket;
    QStringListModel *userModel;
};

#endif // MAINWINDOW_H
