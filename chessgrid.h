#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include "chesspiece.h"

namespace Ui {
class ChessGrid;
}

class ChessGrid : public QWidget
{
    Q_OBJECT

public:
    explicit ChessGrid(QWidget *parent = nullptr);
    ~ChessGrid();

    void arrangeChess();

private:
    Ui::ChessGrid *ui;
};

#endif // CHESSGRID_H
