#include "chat.h"

Chat::Chat(QObject *parent) : QObject{parent}{

    if(!socket.bind(port, QUdpSocket::ShareAddress)){
        qDebug() << socket.errorString();
    }
    else{
        qInfo() << "Started UDP on " << socket.localAddress() << " : " << socket.localPort();
        QObject::connect(&socket, &QUdpSocket::readyRead, this, &Chat::readyRead);
    }

}

void Chat::command(QString value){

    QString message = name + ": ";
    if(name.isEmpty())
    {
        name = value;
        message = name + ": joined";
        send(message);
        return;
    }
    message.append(value);
    send(message);
}

void Chat::send(QString value)
{
    QByteArray data = value.toLatin1();

    qint64 bytesWritten = socket.writeDatagram(data.data(), data.size(), QHostAddress::LocalHost, port);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send datagram:" << socket.errorString();
    } else {
        qInfo() << "\tSend: " << data;
    }

}

void Chat::readyRead()
{
    while(socket.hasPendingDatagrams()){

        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "\tRead: " << datagram.data();
    }

}
