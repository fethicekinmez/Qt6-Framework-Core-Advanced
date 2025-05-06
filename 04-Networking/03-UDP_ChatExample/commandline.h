#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>

class CommandLine : public QObject
{
    Q_OBJECT

    QTextStream cin;
public:
    explicit CommandLine(QObject *parent = nullptr, FILE *fileHandler = nullptr);

    [[noreturn]] void monitor(); //the function will never return

signals:
    void command(QString value);
};

#endif // COMMANDLINE_H
