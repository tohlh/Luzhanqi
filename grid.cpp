#include "grid.h"

Grid::Grid(QWidget *parent) : QLabel(parent)
{

}

void Grid::setCoord(int x, int y)
{
    xCoord = x;
    yCoord = y;
}

int Grid::getXCoord()
{
    return xCoord;
}

int Grid::getYCoord()
{
    return yCoord;
}

void Grid::setOccupied(bool a)
{
    isOccupied = a;
}

bool Grid::getOccupied()
{
    return isOccupied;
}

void Grid::setChess(ChessPiece* c)
{
    currChess = c;
}

ChessPiece* Grid::getChess()
{
    return currChess;
}

void Grid::clearChess()
{
    currChess = nullptr;
}

void Grid::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit sendAction(0, -1, xCoord, yCoord);
    } else {
        Grid::mousePressEvent(event);
    }
}
