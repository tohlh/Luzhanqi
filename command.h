#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QRegularExpression>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    void parse(QString cmd);

signals:
    void sendActionNetwork(int from, int id, int xCoord, int yCoord);
    void myTurn();
    void endGame(int winColor);
};

#endif // COMMAND_H
