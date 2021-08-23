#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    void setColor(int c);
    void getColor();

signals:
    void endGame(int winner); //color

private:
    int color; //0 for blue, 1 for red
    int prevColor;
};

#endif // PLAYER_H
