#include "TCPWebsocketServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPWebsocketServer w;
    w.show();
    return a.exec();
}
