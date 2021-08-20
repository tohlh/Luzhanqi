#ifndef GRID_H
#define GRID_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include "chesspiece.h"

class Grid : public QLabel
{
    Q_OBJECT
public:
    Grid(QWidget *parent = nullptr);

    void setCoord(int x, int y);
    int getXCoord();
    int getYCoord();
    void setOccupied(bool a);
    bool getOccupied();
    void setChess(ChessPiece* c);
    void clearChess();
    ChessPiece* getChess();

signals:
    void sendAction(int id, int xCoord, int yCoord);

protected:
    void mousePressEvent(QMouseEvent* event);
    int xCoord, yCoord;
    bool isOccupied;
    ChessPiece* currChess;
};

#endif // GRID_H
