#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>   // Добавляем заголовок для кнопки
#include <QTextBrowser>  // Добавляем заголовок для текстового поля

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onTextMessageReceived(const QString &message);
    void updateUserList(const QStringList &users);

private:
    QWebSocket *m_webSocket;
    QVBoxLayout *userListLayout;
    QWidget *userListWidget;
    QScrollArea *userScrollArea;
    QPushButton *connectButton;  // Объявляем кнопку

    QString getUserName();
};

#endif // MAINWINDOW_H
