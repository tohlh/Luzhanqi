#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chessboardLayout->addWidget(chessboard);
    QObject::connect(this, SIGNAL(gameStarted()), this, SLOT(initGame()));
    QObject::connect(this, SIGNAL(gameEnded()), this, SLOT(endGame()));
    QObject::connect(timer::timer, SIGNAL(timeout()), this, SLOT(updateTimerText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Public slots
void MainWindow::initGame()
{
    ui->actionSurrender->setEnabled(true);
    timer::timer->start(1000);
    chessboard->setNewChessboard();
}

void MainWindow::endGame()
{
    EndDialog *dialog = new EndDialog();
    dialog->setWinColor("Blue");
    dialog->show();
    ui->actionSurrender->setEnabled(false);
    chessboard->setBlankChessboard();

    timer::currTimer = 0;
    timer::timer->stop();
    ui->timer->display(0);
}

void MainWindow::updateTimerText()
{
    if (timer::currTimer < 20) {
        timer::currTimer++;
    } else {
        // todo: others turn
        timer::currTimer = 0;
    }
    ui->timer->display(timer::currTimer);
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

void MainWindow::on_actionCreate_a_connection_triggered()
{
    if (network::client) {
        network::client->close();
        delete network::client;
    }

    if (!network::server) {
        network::server = new Server();
        network::server->initServer();
    }
    network::server->show();
}

void MainWindow::on_actionConnect_to_server_triggered()
{
    if (network::server) {
        network::server->close();
        delete network::server;
    }

    if (!network::client) {
        network::client = new Client();
    }
    network::client->show();
}

