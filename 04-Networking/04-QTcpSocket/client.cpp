#include "client.h"

Client::Client(QObject *parent) : QObject{parent}{

    connect(&socket,&QTcpSocket::connected,this,&Client::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Client::disconnected);

    connect(&socket,&QTcpSocket::stateChanged,this,&Client::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Client::readyRead);

    //in Qt 5, Socket Error connection
    //connect(&socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&Client::error); //Explain
    connect(&socket,&QTcpSocket::errorOccurred,this,&Client::error);
}

void Client::connectToHost(QString host, quint16 port){

    if(socket.isOpen()){
        disconnect();
    }

    qInfo() << "Connecting to server " << host << " on port " << port;
    socket.connectToHost(host, port);

}

void Client::disconnect(){

    socket.close();
    socket.waitForDisconnected();
}

void Client::connected(){

    qInfo() << "Connected!";
    qInfo() << "Sending...";

    socket.write("Hello\r\n");

}

void Client::disconnected(){

    qInfo() << "Disconnected";

}

void Client::error(QAbstractSocket::SocketError socketError){


    qInfo() << socketError << " : " << socket.errorString();

}

void Client::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State: " << metaEnum.valueToKey(socketState) << " -- " << socketState;
}

void Client::readyRead()
{
    qInfo() << "Data from: " << sender() << " bytes: " << socket.bytesAvailable();
    qInfo() << "Data: " << socket.readAll();

}
