#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>

class Chat : public QObject
{
    Q_OBJECT

    QString name;
    QUdpSocket socket;
    quint64 port = 2020;

public:
    explicit Chat(QObject *parent = nullptr);

signals:

public slots:
    void command(QString value);
    void send(QString value);
    void readyRead();
};

#endif // CHAT_H
