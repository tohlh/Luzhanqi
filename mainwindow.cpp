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

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Public slots
void MainWindow::initGame()
{
    ui->actionSurrender->setEnabled(true);
    timer->start(1000);
}

void MainWindow::endGame()
{
    EndDialog *dialog = new EndDialog();
    dialog->setWinColor("Blue");
    dialog->show();
    ui->actionSurrender->setEnabled(false);

    currTimer = 0;
    timer->stop();
    ui->timer->display(0);
}

void MainWindow::updateTimerText()
{
    if (currTimer < 20) {
        currTimer++;
    } else {
        // todo: others turn
        currTimer = 0;
    }
    ui->timer->display(currTimer);
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
