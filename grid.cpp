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

void Grid::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

    } else {

    }
}
