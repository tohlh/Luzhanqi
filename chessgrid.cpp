#include "chessgrid.h"
#include "ui_chessgrid.h"

/* Initailise the whole grid. Assign grid coordinates to all the grids and chesspieces, shuffle the chesspieces. */
ChessGrid::ChessGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessGrid)
{
    ui->setupUi(this);

    grids.append({ui->grid_01_1, ui->grid_01_2, ui->grid_01_3, ui->grid_01_4, ui->grid_01_5});
    grids.append({ui->grid_02_1, ui->grid_02_2, ui->grid_02_3, ui->grid_02_4, ui->grid_02_5});
    grids.append({ui->grid_03_1, ui->grid_03_2, ui->grid_03_3, ui->grid_03_4, ui->grid_03_5});
    grids.append({ui->grid_04_1, ui->grid_04_2, ui->grid_04_3, ui->grid_04_4, ui->grid_04_5});
    grids.append({ui->grid_05_1, ui->grid_05_2, ui->grid_05_3, ui->grid_05_4, ui->grid_05_5});
    grids.append({ui->grid_06_1, ui->grid_06_2, ui->grid_06_3, ui->grid_06_4, ui->grid_06_5});
    grids.append({ui->grid_07_1, ui->grid_07_2, ui->grid_07_3, ui->grid_07_4, ui->grid_07_5});
    grids.append({ui->grid_08_1, ui->grid_08_2, ui->grid_08_3, ui->grid_08_4, ui->grid_08_5});
    grids.append({ui->grid_09_1, ui->grid_09_2, ui->grid_09_3, ui->grid_09_4, ui->grid_09_5});
    grids.append({ui->grid_10_1, ui->grid_10_2, ui->grid_10_3, ui->grid_10_4, ui->grid_10_5});
    grids.append({ui->grid_11_1, ui->grid_11_2, ui->grid_11_3, ui->grid_11_4, ui->grid_11_5});
    grids.append({ui->grid_12_1, ui->grid_12_2, ui->grid_12_3, ui->grid_12_4, ui->grid_12_5});

    chesspieces = { ui->chess_01, ui->chess_02, ui->chess_03, ui->chess_04, ui->chess_05,
                    ui->chess_06, ui->chess_07, ui->chess_08, ui->chess_09, ui->chess_10,
                    ui->chess_11, ui->chess_12, ui->chess_13, ui->chess_14, ui->chess_15,
                    ui->chess_16, ui->chess_17, ui->chess_18, ui->chess_19, ui->chess_20,
                    ui->chess_21, ui->chess_22, ui->chess_23, ui->chess_24, ui->chess_25,
                    ui->chess_26, ui->chess_27, ui->chess_28, ui->chess_29, ui->chess_30,
                    ui->chess_31, ui->chess_32, ui->chess_33, ui->chess_34, ui->chess_35,
                    ui->chess_36, ui->chess_37, ui->chess_38, ui->chess_39, ui->chess_40,
                    ui->chess_41, ui->chess_42, ui->chess_43, ui->chess_44, ui->chess_45,
                    ui->chess_46, ui->chess_47, ui->chess_48, ui->chess_49, ui->chess_50 };

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

    for (int i = 0; i < grids.size(); i++) {
        for (int j = 0; j < grids[i].size(); j++) {
            grids[i][j]->setCoord(j + 1, i + 1);
        }
    }

    for (int i = 0; i < chesspieces.size(); i++) {
        int x = chesspieces[i]->getXCoord();
        int y = chesspieces[i]->getYCoord();
        setGridChess(x, y, chesspieces[i]);
        setGridOccupied(x, y, true);
    }

    if (network::server) {
        QObject::connect(network::server->command, SIGNAL(sendAction(int, int, int, int)), this, SLOT(appendAction(int, int, int, int)));
        shuffleChess();
        arrangeChess(chesspieces);
        network::server->sendChessSeq(chessSeq);
    }

    if (network::client) {
        QObject::connect(network::client->command, SIGNAL(sendAction(int, int, int, int)), this, SLOT(appendAction(int, int, int, int)));
        QObject::connect(network::client, SIGNAL(receivedSeq(QList <int>)), this, SLOT(receivedSeq(QList <int>)));
    }

    for (int i = 0; i < chesspieces.size(); i ++) {
        QObject::connect(chesspieces[i], SIGNAL(sendAction(int, int, int, int)), this, SLOT(appendAction(int, int, int, int)));
    }

    for (int i = 0; i < grids.size(); i++) {
        for (int j = 0; j < grids[i].size(); j++) {
            QObject::connect(grids[i][j], SIGNAL(sendAction(int, int, int, int)), this, SLOT(appendAction(int, int, int, int)));
        }
    }

    validate = new Validator(grids);
}

ChessGrid::~ChessGrid()
{
    delete ui;
}

void ChessGrid::shuffleChess()
{
    QList <int> chessID;
    for (int i = 0; i < 50; i++) {
        chessID.append(i);
    }

    QRandomGenerator rand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i = 0; i < chesspieces.size(); i++) {
        int index = rand.generate() % chessID.size();
        int currChessID = chessID[index];
        chessSeq.append(currChessID);
        chessID.remove(index);
    }
}

void ChessGrid::arrangeChess(QList <ChessPiece*> chesspieces)
{
    for (int i = 0; i < chesspieces.size(); i++) {
        int currChessID = chessSeq[i];
        int color = currChessID > 25 ? 0 : 1;
        chessPieceTypedef type = getChessTypeFromID(currChessID % 25);
        chesspieces[i]->setChess(color, type);
        chesspieces[i]->setID(i + 1);
        if (color == 0) {
            blueChess.append(chesspieces[i]);
        } else if (color == 1) {
            redChess.append(chesspieces[i]);
        }
    }

    while (chesspieces.size()) {
        chesspieces.remove(0);
    }
}

void ChessGrid::receivedSeq(QList<int> seq)
{
    for (int i = 0; i < seq.size(); i++) {
        chessSeq.append(seq[i]);
    }
    arrangeChess(chesspieces);
}

void ChessGrid::appendAction(int type, int id, int xCoord, int yCoord) //type 0:mouse, 1:network
{
    actionStruct newAction;
    newAction.id = id;
    newAction.xCoord = xCoord;
    newAction.yCoord = yCoord;
    QString cmd = QString("!act %1 %2 %3").arg(id).arg(xCoord).arg(yCoord);

    if (type == 0 && player::isTurn) {
        bool pas = false; // whether to end the command
        if (currAction.id != -2) {
            if (newAction.id == currAction.id) { //deselect chess
                deselectChess(newAction.id);
                clearAction();
            } else if (newAction.id == -1) { //move chess
                bool condition = validate->checkMove(getChessByID(currAction.id), newAction.xCoord, newAction.yCoord);
                if (condition) {
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    deselectChess(currAction.id);
                    clearAction();
                    pas = true;
                    player::steps++;
                }
            } else if (newAction.id > 0) { //attack chess
                // 0 chess1 destroyed, 1 chess2 destroyed, -1 both destroyed, -2 invalid move
                int condition = validate->checkAttack(getChessByID(currAction.id), getChessByID(newAction.id));
                if (condition ==  0) {
                    removeChess(currAction.id);
                    deselectChess(currAction.id);
                    clearAction();
                    pas = true;
                    player::steps++;
                } else if (condition == 1) {
                    removeChess(newAction.id);
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    deselectChess(currAction.id);
                    clearAction();
                    pas = true;
                    player::steps++;
                } else if (condition == -1) {
                    removeChess(newAction.id);
                    removeChess(currAction.id);
                    clearAction();
                    pas = true;
                    player::steps++;
                }  else if (condition == 2) {
                    removeChess(newAction.id);
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    int winColor = getChessByID(currAction.id)->getChessColor();
                    commitCommand(cmd);
                    emit endGame(winColor);
                    return;
                }
            }
        } else {
            if (newAction.id > 0 && !getChessByID(newAction.id)->getChessFlipped()) {
                ChessPiece* toFlip = getChessByID(newAction.id);
                toFlip->flipChess();
                player::steps++;
                if (player::myColor == -1) {
                    if (player::myLastColor == -1 || player::myLastColor != toFlip->getChessColor()) {
                        player::myLastColor = toFlip->getChessColor();
                    } else if (player::myLastColor == toFlip->getChessColor()) {
                        player::myColor = toFlip->getChessColor();
                        player::theirColor = !toFlip->getChessColor();
                        emit colorDecided();
                    }
                }
                clearAction();
                pas = true;
            } else if (newAction.id > 0 && getChessByID(newAction.id)->getChessFlipped() && getChessByID(newAction.id)->getChessColor() == player::myColor) {
                selectChess(newAction.id, true);
                currAction = newAction;
            }
        }
        if (pas) {
            cmd += " !pas";
            passOver();
        }
        commitCommand(cmd);
        checkLose();
    } else if (type == 1) {
        if (currAction.id != -2) {
            if (newAction.id == currAction.id) { //deselect chess
                deselectChess(newAction.id);
                clearAction();
            } else if (newAction.id == -1) { //move chess
                bool condition = validate->checkMove(getChessByID(currAction.id), newAction.xCoord, newAction.yCoord);
                if (condition) {
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    deselectChess(currAction.id);
                    clearAction();
                    player::steps++;
                }
            } else if (newAction.id > 0) { //attack chess
                // 0 chess1 destroyed, 1 chess2 destroyed, -1 both destroyed, -2 invalid move
                int condition = validate->checkAttack(getChessByID(currAction.id), getChessByID(newAction.id));
                if (condition ==  0) {
                    removeChess(currAction.id);
                    deselectChess(currAction.id);
                    clearAction();
                    player::steps++;
                } else if (condition == 1) {
                    removeChess(newAction.id);
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    deselectChess(currAction.id);
                    clearAction();
                    player::steps++;
                } else if (condition == -1) {
                    removeChess(newAction.id);
                    removeChess(currAction.id);
                    clearAction();
                    player::steps++;
                } else if (condition == 2) {
                    removeChess(newAction.id);
                    moveChess(currAction.id, newAction.xCoord, newAction.yCoord);
                    int winColor = getChessByID(currAction.id)->getChessColor();
                    emit endGame(winColor);
                    return;
                }
            }
        } else {
            if (newAction.id > 0 && !getChessByID(newAction.id)->getChessFlipped()) {
                ChessPiece* toFlip = getChessByID(newAction.id);
                toFlip->flipChess();
                player::steps++;
                if (player::theirColor == -1) {
                    if (player::theirLastColor == -1 || player::theirLastColor != toFlip->getChessColor()) {
                        player::theirLastColor = toFlip->getChessColor();
                    } else if (player::theirLastColor == toFlip->getChessColor()) {
                        player::theirColor = toFlip->getChessColor();
                        player::myColor = !toFlip->getChessColor();
                        emit colorDecided();
                    }
                }
                clearAction();
            } else if (newAction.id > 0 && getChessByID(newAction.id)->getChessFlipped() && getChessByID(newAction.id)->getChessColor() == player::theirColor) {
                selectChess(newAction.id, false);
                currAction = newAction;
            }
        }
        checkLose();
    }
}

void ChessGrid::commitCommand(QString cmd)
{
    if (network::server) {
        network::server->sendData(cmd);
    }

    if (network::client) {
        network::client->sendData(cmd);
    }
}

void ChessGrid::checkLose()
{
    bool blueLost = validate->checkLose(blueChess);
    bool redLost = validate->checkLose(redChess);

    if (blueLost) emit endGame(1);
    if (redLost) emit endGame(0);
}

void ChessGrid::passOver()
{
    emit theirTurn();
}

void ChessGrid::clearAction()
{
    currAction = {-2, -2, -2};
}

/*
 * x, y, grid coordinate
 * move chess with id to grid at (x, y)
 */
void ChessGrid::selectChess(int id, bool yourself)
{
    ChessPiece* toSelect = getChessByID(id);
    if (toSelect) {
        toSelect->selectChess(yourself);
    }
}

void ChessGrid::deselectChess(int id)
{
    ChessPiece* toDeselect = getChessByID(id);
    if (toDeselect) {
        toDeselect->deselectChess();
    }
}

void ChessGrid::moveChess(int id, int x, int y)
{
    ChessPiece* toMove = getChessByID(id);
    if (toMove) {
        setGridOccupied(toMove->getXCoord(), toMove->getYCoord(), false);
        setGridOccupied(x, y, true);
        clearGridChess(toMove->getXCoord(), toMove->getYCoord());
        setGridChess(x, y, toMove);
        toMove->move(xCoord[x], yCoord[y]);
        toMove->setCoord(x, y);
    }
}

void ChessGrid::removeChess(int id)
{
    ChessPiece* toRemove = nullptr;
    for (int i = 0; i < blueChess.size(); i++) {
        if (blueChess[i]->getID() == id) {
            toRemove = blueChess[i];
            blueChess.remove(i);
            break;
        }
    }
    for (int i = 0; i < redChess.size(); i++) {
        if (redChess[i]->getID() == id) {
            toRemove = redChess[i];
            redChess.remove(i);
            break;
        }
    }
    if (toRemove) {
        setGridOccupied(toRemove->getXCoord(), toRemove->getYCoord(), false);
        clearGridChess(toRemove->getXCoord(), toRemove->getYCoord());
        delete(toRemove);
    }
}

Grid* ChessGrid::getGrid(int x, int y)
{
    return grids[y - 1][x - 1];
}

void ChessGrid::setGridOccupied(int x, int y, bool a)
{
    grids[y - 1][x - 1]->setOccupied(a);
}

bool ChessGrid::isGridOccupied(int x, int y)
{
    return grids[y - 1][x - 1]->getOccupied();
}

void ChessGrid::setGridChess(int x, int y, ChessPiece* chess)
{
    grids[y - 1][x - 1]->setChess(chess);
}

ChessPiece* ChessGrid::getGridChess(int x, int y)
{
    return grids[y - 1][x - 1]->getChess();
}

ChessPiece* ChessGrid::getChessByID(int id)
{
    ChessPiece* ret = nullptr;
    for (int i = 0; i < blueChess.size(); i++) {
        if (blueChess[i]->getID() == id) {
            ret = blueChess[i];
            break;
        }
    }
    for (int i = 0; i < redChess.size(); i++) {
        if (redChess[i]->getID() == id) {
            ret = redChess[i];
            break;
        }
    }
    return ret;
}

void ChessGrid::clearGridChess(int x, int y)
{
    grids[y - 1][x - 1]->clearChess();
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
    return junqi;
}
