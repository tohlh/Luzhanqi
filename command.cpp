#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

bool Command::parse(QString cmd)
{
    QString sign = cmd.mid(0, 4);
    QList <QString> list;

    qInfo() << cmd;

    if (sign == "!act") {
        list = cmd.split(QRegularExpression("\\s+"));
        if (list.size() < 5) return false;

        if (list.size() == 6 && list[5] == "!end") emit myTurn();
        emit sendActionNetwork(list[1].toInt(), list[2].toInt(), list[3].toInt(), list[4].toInt());
    }

    return true;
}
