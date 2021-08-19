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
