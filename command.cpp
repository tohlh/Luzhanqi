#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

void Command::parse(QString cmd)
{
    QString sign = cmd.mid(0, 4);
    QList <QString> list;

    if (sign == "!act") {
        list = cmd.split(QRegularExpression("\\s+"));
        if (list.size() < 5) return;
        if (list.size() == 6 && list[5] == "!pas") {
            emit myTurn();
        }
        emit sendActionNetwork(list[1].toInt(), list[2].toInt(), list[3].toInt(), list[4].toInt());
    } else if (sign == "!end") {
        list = cmd.split(QRegularExpression("\\s+"));
        if (list.size() < 2) return;
        emit endGame(list[1].toInt());
    }
}
