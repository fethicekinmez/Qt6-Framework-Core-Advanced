#include <QCoreApplication>
#include <QDebug>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    //client.connectToHost("www.httpbin.org", 80); Not encrypted
    client.connectToHost("httpbin.org", 443); //SSL Encrypted

    return a.exec();
}
