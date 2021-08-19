#include "chessgrid.h"
#include "ui_chessgrid.h"

/* Initailise the whole grid. Assign grid coordinates to all the grids and chesspieces, shuffle the chesspieces. */
ChessGrid::ChessGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessGrid)
{
    ui->setupUi(this);

    QList <Grid*> grids = { ui->grid_01_1, ui->grid_01_2, ui->grid_01_3, ui->grid_01_4, ui->grid_01_5,
                            ui->grid_02_1, ui->grid_02_2, ui->grid_02_3, ui->grid_02_4, ui->grid_02_5,
                            ui->grid_03_1, ui->grid_03_2, ui->grid_03_3, ui->grid_03_4, ui->grid_03_5,
                            ui->grid_04_1, ui->grid_04_2, ui->grid_04_3, ui->grid_04_4, ui->grid_04_5,
                            ui->grid_05_1, ui->grid_05_2, ui->grid_05_3, ui->grid_05_4, ui->grid_05_5,
                            ui->grid_06_1, ui->grid_06_2, ui->grid_06_3, ui->grid_06_4, ui->grid_06_5,
                            ui->grid_07_1, ui->grid_07_2, ui->grid_07_3, ui->grid_07_4, ui->grid_07_5,
                            ui->grid_08_1, ui->grid_08_2, ui->grid_08_3, ui->grid_08_4, ui->grid_08_5,
                            ui->grid_09_1, ui->grid_09_2, ui->grid_09_3, ui->grid_09_4, ui->grid_09_5,
                            ui->grid_10_1, ui->grid_10_2, ui->grid_10_3, ui->grid_10_4, ui->grid_10_5,
                            ui->grid_11_1, ui->grid_11_2, ui->grid_11_3, ui->grid_11_4, ui->grid_11_5,
                            ui->grid_12_1, ui->grid_12_2, ui->grid_12_3, ui->grid_12_4, ui->grid_12_5 };

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

    for (int i = 0; i < grids.size(); i++) {
        int x = (i % 5) + 1;
        int y = (i / 5) + 1;
        grids[i]->setCoord(x, y);
    }

    for (int i = 0; i < 10; i++) {
        int x = (i % 5) + 1;
        int y = (i / 5) + 1;
        chesspieces[i]->setCoord(x, y);
    }

    for (int i = 20; i < 25; i++) {
        int x = (i % 5) + 1;
        int y = 6;
        chesspieces[i]->setCoord(x, y);
    }

    for (int i = 25; i < 30; i++) {
        int x = (i % 5) + 1;
        int y = 7;
        chesspieces[i]->setCoord(x, y);
    }

    for (int i = 40; i < 50; i++) {
        int x = (i % 5) + 1;
        int y = (i / 5) + 3;
        chesspieces[i]->setCoord(x, y);
    }

    chesspieces[10]->setCoord(1, 3);
    chesspieces[11]->setCoord(3, 3);
    chesspieces[12]->setCoord(5, 3);
    chesspieces[13]->setCoord(1, 4);
    chesspieces[14]->setCoord(2, 4);
    chesspieces[15]->setCoord(4, 4);
    chesspieces[16]->setCoord(5, 4);
    chesspieces[17]->setCoord(1, 5);
    chesspieces[18]->setCoord(3, 5);
    chesspieces[19]->setCoord(5, 5);

    chesspieces[30]->setCoord(1, 8);
    chesspieces[31]->setCoord(3, 8);
    chesspieces[32]->setCoord(5, 8);
    chesspieces[33]->setCoord(1, 9);
    chesspieces[34]->setCoord(2, 9);
    chesspieces[35]->setCoord(4, 9);
    chesspieces[36]->setCoord(5, 9);
    chesspieces[37]->setCoord(1, 10);
    chesspieces[38]->setCoord(3, 10);
    chesspieces[39]->setCoord(5, 10);

    arrangeChess(chesspieces);
}

ChessGrid::~ChessGrid()
{
    delete ui;
}

void ChessGrid::arrangeChess(QList <ChessPiece*> chesspieces)
{
    QRandomGenerator rand(QDateTime::currentMSecsSinceEpoch() / 1000);
    QList <int> chessID;
    for (int i = 0; i < 50; i++) {
        chessID.append(i);
    }

    for (int i = 0; i < chesspieces.size(); i++) {
        int index = rand.generate() % chessID.size();
        int currChessID = chessID[index];
        int color = currChessID > 25 ? 0 : 1;
        chessPieceTypedef type = getChessTypeFromID(currChessID % 25);
        chesspieces[i]->setChess(color, type);
        chesspieces[i]->setID(i + 1);
        chessID.remove(index);
    }
}

/*
 * x, y, grid coordinate
 */
void ChessGrid::moveChess(ChessPiece* chess, int x, int y) {
    QList <int> xCoord = {8, 108, 208, 308, 408};
    QList <int> yCoord = {8, 60, 112, 164, 216, 268, 438, 490, 542, 594, 646, 698};
    chess->move(xCoord[x], yCoord[y]);
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
