#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QNetworkDatagram>


class Worker : public QObject
{
    Q_OBJECT

    QUdpSocket socket;
    QTimer timer;
    quint64 port = 12345;  // Ports < 1024 are admin ports, special services HTTP, FTP, POP3, SMTP

public:
    explicit Worker(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void stop();
    void timeout();
    void readyRead();
    void broadcast();
};

#endif // WORKER_H
