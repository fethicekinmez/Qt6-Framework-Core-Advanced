#include <QCoreApplication>
#include <QFuture>
#include <QtConcurrent>
#include "commandline.h"
#include "chat.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommandLine commandLine(&a, stdin);
    // run the monitor() member function of the CommandLine class asynchronously (i.e., in a separate thread), and returns a QFuture<void> object to track its execution.
    QFuture<void> future = QtConcurrent::run(&CommandLine::monitor, &commandLine);

    Chat chat;
    QObject::connect(&commandLine, &CommandLine::command, &chat, &Chat::command, Qt::QueuedConnection);

    qInfo() << "Enter your name to begin";


    return a.exec();
}
