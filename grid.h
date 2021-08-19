#ifndef GRID_H
#define GRID_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class Grid : public QLabel
{
    Q_OBJECT
public:
    Grid(QWidget *parent = nullptr);

    void setCoord(int x, int y);
    int getXCoord();
    int getYCoord();

protected:
    void mousePressEvent(QMouseEvent* event);
    int xCoord, yCoord;
};

#endif // GRID_H
