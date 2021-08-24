#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGridLayout>
#include "chessgrid.h"
#include "chesspiece.h"
#include "global.h"

namespace Ui {
class Chessboard;
}

class Chessboard : public QWidget
{
    Q_OBJECT

public:
    explicit Chessboard(QWidget *parent = nullptr);
    ~Chessboard();
    void setNewChessboard();
    ChessGrid *chessgrid = nullptr;

private:
    Ui::Chessboard *ui;
    QGridLayout *layout = new QGridLayout();

};

#endif // CHESSBOARD_H
