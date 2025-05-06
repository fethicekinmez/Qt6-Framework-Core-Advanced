#include <QCoreApplication>

#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QHostAddress> addressList = QNetworkInterface::allAddresses();

    for(int i=0; i<addressList.count(); i++){

        QHostAddress address = addressList.at(i);
        qInfo() << address.toString();

        qInfo() << "\t LoopBack: " << address.isLoopback(); // loopback address, meaning traffic sent to this IP stays on your own machine
        qInfo() << "\t Mulitcast: " << address.isMulticast(); // It's a way to send data to multiple recipients at once

        switch(address.protocol()){
        case QAbstractSocket::UnknownNetworkLayerProtocol:
            qInfo() << "\t Protocol: Unknown";
            break;
        case QAbstractSocket::AnyIPProtocol:
            qInfo() << "\t Protocol: Any";
            break;
        case QAbstractSocket::IPv6Protocol:
            qInfo() << "\t Protocol: IPv6";
            break;
        case QAbstractSocket::IPv4Protocol:
            qInfo() << "\t Protocol: IPv4";
            break;

        }

    }

    return a.exec();
}
