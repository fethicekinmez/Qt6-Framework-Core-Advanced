#include <QCoreApplication>
#include <QDebug>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToHost("www.google.com", 80);

    return a.exec();
}
