#include "chessgrid.h"
#include "ui_chessgrid.h"

ChessGrid::ChessGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessGrid)
{
    ui->setupUi(this);
}

ChessGrid::~ChessGrid()
{
    delete ui;
}

void ChessGrid::arrangeChess()
{
    QRandomGenerator rand(QDateTime::currentMSecsSinceEpoch() / 1000);
    //ui->chess_03->setChess(0, junqi);
    //ui->chess_48->setChess(1, junqi);

    QList <ChessPiece*> chesspieces = { ui->chess_01, ui->chess_02, ui->chess_03, ui->chess_04, ui->chess_05,
                                        ui->chess_06, ui->chess_07, ui->chess_08, ui->chess_09, ui->chess_10,
                                        ui->chess_11, ui->chess_12, ui->chess_13, ui->chess_14, ui->chess_15,
                                        ui->chess_16, ui->chess_17, ui->chess_18, ui->chess_19, ui->chess_20,
                                        ui->chess_21, ui->chess_22, ui->chess_23, ui->chess_24, ui->chess_25,
                                        ui->chess_26, ui->chess_27, ui->chess_28, ui->chess_29, ui->chess_30,
                                        ui->chess_31, ui->chess_32, ui->chess_33, ui->chess_34, ui->chess_35,
                                        ui->chess_36, ui->chess_37, ui->chess_38, ui->chess_39, ui->chess_40,
                                        ui->chess_41, ui->chess_42, ui->chess_43, ui->chess_44, ui->chess_45,
                                        ui->chess_46, ui->chess_47, ui->chess_48, ui->chess_49, ui->chess_50 };

    QList <int> chessID;
    for (int i = 0; i < 50; i++) {
        chessID.append(i);
    }

    for (int i = 0; i < 50; i++) {
        int index = rand.generate() % chessID.size();
        int currChessID = chessID[index];
        int color = currChessID > 25 ? 0 : 1;
        chessPieceTypedef type = getChessTypeFromID(currChessID % 25);
        chesspieces[i]->setChess(color, type);
        chessID.remove(index);
    }
}

/*
 * 1 - 3 gongbing
 * 4 - 6 paizhang
 * 7 - 9 lianzhang
 * 10 - 12 dilei
 * 13 - 14 zhadan
 * 15 - 16 yingzhang
 * 17 - 18 tuanzhang
 * 19 - 20 lvzhang
 * 21 - 22 shizhang
 * 23 junzhang
 * 24 siling
 * 25 junqi
 *
 */

chessPieceTypedef ChessGrid::getChessTypeFromID(int ID) {
    switch(ID) {
        case 0:
        case 1:
        case 2:
        {
            return gongbing;
        }
        case 3:
        case 4:
        case 5:
        {
            return paizhang;
        }

        case 6:
        case 7:
        case 8:
        {
            return lianzhang;
        }
        case 9:
        case 10:
        case 11:
        {
            return dilei;
        }
        case 12:
        case 13:
        {
            return zhadan;
        }
        case 14:
        case 15:
        {
            return yingzhang;
        }
        case 16:
        case 17:
        {
            return tuanzhang;
        }
        case 18:
        case 19:
        {
            return lvzhang;
        }
        case 20:
        case 21:
        {
            return shizhang;
        }
        case 22:
        {
            return junzhang;
        }
        case 23:
        {
            return siling;
        }
        case 24:
        {
            return junqi;
        }
    }
}
