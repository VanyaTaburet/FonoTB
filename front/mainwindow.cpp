#include "mainwindow.h"
#include <QWebEngineView>
#include <QCoreApplication>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *view = new QWebEngineView(this);
    view->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/index.html"));
    setCentralWidget(view);

    setMinimumSize(640, 360);   // минимум 16:9
    setMaximumSize(1920, 1080); // максимум 16:9

    resize(1280, 720);  // начальный размер 16:9
}


