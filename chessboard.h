#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGridLayout>
#include "chessgrid.h"
#include "chesspiece.h"

namespace Ui {
class Chessboard;
}

class Chessboard : public QWidget
{
    Q_OBJECT

public:
    explicit Chessboard(QWidget *parent = nullptr);
    ~Chessboard();
    ChessGrid *chessgrid;

public slots:
    void setBlankChessboard();
    void setNewChessboard();

private:
    Ui::Chessboard *ui;
    QGridLayout *layout = new QGridLayout();

};

#endif // CHESSBOARD_H
