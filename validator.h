#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "chesspiece.h"
#include "grid.h"
#include "chessrules.h"

class Validator
{
public:
    Validator(QList < QList <Grid*> > &g);

    bool checkMove(ChessPiece* chess, int x, int y); //Check if the chess can go from its current pos to desired pos
    int checkAttack(ChessPiece* chess1, ChessPiece* chess2); // 0 chess1 destroyed, 1 chess2 destroyed, -1 both destroyed

private:
    QList < QList <Grid* > > grids;
};

#endif // VALIDATOR_H
