#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chessboardLayout->addWidget(chessboard);
    QObject::connect(this, SIGNAL(gameStarted()), this, SLOT(initGame()));
    QObject::connect(this, SIGNAL(gameStarted()), chessboard, SLOT(setNewChessboard()));
    QObject::connect(this, SIGNAL(gameEnded()), this, SLOT(endGame()));
    QObject::connect(this, SIGNAL(gameEnded()), chessboard, SLOT(setBlankChessboard()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Public slots
void MainWindow::initGame()
{
    ui->actionSurrender->setEnabled(true);
}

void MainWindow::endGame()
{
    EndDialog *dialog = new EndDialog();
    dialog->setWinColor("Blue");
    dialog->show();
    ui->actionSurrender->setEnabled(false);
}

// Private slots
void MainWindow::on_actionStart_triggered()
{
    emit gameStarted();
}

void MainWindow::on_actionSurrender_triggered()
{
    emit gameEnded();
}
