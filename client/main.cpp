#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebSockets/QWebSocket>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Загружаем QML-файл
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));  // Убедись, что QML файл загружается правильно

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
