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

void Chat::readyRead()
{
    while(socket.hasPendingDatagrams()){

        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "\tRead: " << datagram.data();
    }

}

void Chat::command(QString value){

    QString message;
    if(name.isEmpty()) {
        name = value;
        message = name + " joined the room!";
        send(message);
        return;
    }
    message = name + ": ";
    message.append(value);
    send(message);
}

void Chat::send(QString value){

    QByteArray data = value.toLatin1();
    QNetworkDatagram datagram(data, QHostAddress::Broadcast);
    qint64 bytesWritten = socket.writeDatagram(datagram.data(), datagram.data().size(), QHostAddress::LocalHost, port);

    if (bytesWritten == -1) {
        qDebug() << "Failed to send datagram:" << socket.errorString();
    } else {
        qInfo() << "\tSend: " << data;
    }

}

