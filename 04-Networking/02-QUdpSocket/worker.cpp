#include "worker.h"

Worker::Worker(QObject *parent) : QObject{parent}{

    QObject::connect(&timer, &QTimer::timeout, this, &Worker::timeout);
    QObject::connect(&socket, &QUdpSocket::readyRead, this, &Worker::readyRead);
    timer.setInterval(1000);
}

void Worker::start(){

    if(!socket.bind(QHostAddress::LocalHost, port, QAbstractSocket::ShareAddress)){
        qInfo() << socket.errorString();
        return;
    }

    qInfo() << "Started UDP on " << socket.localAddress() << " : " << socket.localPort();
    broadcast();
}

void Worker::broadcast(){

    qInfo() << "Broadcasting...";
    timer.start();
}

void Worker::stop(){

    timer.stop();
    socket.close();
    qInfo() << "Stopped";
}

void Worker::timeout(){

    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();
    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);

    qint64 bytesWritten = socket.writeDatagram(datagram.data(), datagram.data().size(), QHostAddress::LocalHost, port);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send datagram:" << socket.errorString();
    }
    else {
        qInfo() << "\tSend: " << data;
    }

}

void Worker::readyRead()
{
    while(socket.hasPendingDatagrams()){
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "\tRead: " << datagram.data() << " from " << datagram.senderAddress() << " : " << datagram.senderPort();
    }
}


