#include "client.h"

Client::Client(QObject *parent) : QObject{parent}{

    connect(&socket,&QTcpSocket::connected,this,&Client::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Client::disconnected);

    connect(&socket,&QTcpSocket::stateChanged,this,&Client::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Client::readyRead);

    //in Qt 5, Socket Error connection
    //connect(&socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&Client::error); //Explain
    connect(&socket,&QTcpSocket::errorOccurred,this,&Client::error);

    //Proxy
    QNetworkProxy proxy(QNetworkProxy::HttpProxy, "102.220.13.208", 8080); // https://free-proxy-list.net
    // Set authenication
    //proxy.setUser();
    //proxy.setPassword();
    socket.setProxy(proxy);
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

    /*
    QByteArray request = "Hello\r\n";
    qInfo() << "Sending... " << request ;
    socket.write(request);
    */
    QByteArray data;
    data.append("GET /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");
    socket.write(data);

    socket.waitForBytesWritten();
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
