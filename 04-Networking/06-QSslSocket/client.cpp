#include "client.h"

Client::Client(QObject *parent) : QObject{parent}{

    connect(&socket,&QTcpSocket::connected,this,&Client::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Client::disconnected);

    connect(&socket,&QTcpSocket::stateChanged,this,&Client::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Client::readyRead);

    //in Qt 5, Socket Error connection
    //connect(&socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&Client::error); //Explain
    connect(&socket,&QTcpSocket::errorOccurred,this,&Client::error);

    //SSL
    connect(&socket,&QSslSocket::encrypted,this,&Client::encrypted);
    connect(&socket,&QSslSocket::encryptedBytesWritten,this,&Client::encryptedBytesWritten);
    connect(&socket,&QSslSocket::modeChanged,this,&Client::modeChanged);
    connect(&socket,&QSslSocket::peerVerifyError,this,&Client::peerVerifyError);
    connect(&socket,&QSslSocket::preSharedKeyAuthenticationRequired,this,&Client::preSharedKeyAuthenticationRequired);
    connect(&socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),this,&Client::sslErrors);
}

void Client::connectToHost(QString host, quint16 port){

    if(socket.isOpen()){
        disconnect();
    }

    qInfo() << "Connecting to server " << host << " on port " << port;
    //socket.connectToHost(host, port);
    socket.ignoreSslErrors(); // NOT SECURE
    socket.setProtocol(QSsl::AnyProtocol);
    socket.connectToHostEncrypted(host, port);

}

void Client::disconnect(){

    socket.close();
    socket.waitForDisconnected();
}

void Client::connected(){
    qInfo() << "Connected!";

    QByteArray request;
    request.append("GET /get HTTP/1.1\r\n");
    request.append("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    request.append("Host: local\r\n");
    request.append("Connection: Close\r\n");
    request.append("\r\n");
    socket.write(request);

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

//SSL PART

void Client::encrypted(){
    qInfo() << "Encrypted!!";
}

void Client::encryptedBytesWritten(qint64 written){
    qInfo() << "Encrypted bytes written: " << written;
}

void Client::modeChanged(QSslSocket::SslMode mode){
    qInfo() << "SSL Mode: " << mode;
}

void Client::peerVerifyError(const QSslError &error){
    qInfo() << "peerVerifyError: " << error;
}

void Client::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator){
    qInfo() << "Preshared key required: " << authenticator;
}

void Client::sslErrors(const QList<QSslError> &errors){
    qInfo() << "SSL Errors";
    foreach (QSslError e, errors) {
        qInfo() << e ;
    }
}
