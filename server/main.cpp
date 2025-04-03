#include <QCoreApplication>
#include "SimpleWebSocketServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleWebSocketServer server;
    server.startServer();

    return a.exec();
}
