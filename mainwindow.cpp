#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chessboardLayout->addWidget(chessboard);
    QObject::connect(this, SIGNAL(gameStarted()), this, SLOT(initGame()));
    QObject::connect(this, SIGNAL(gameEnded(int)), this, SLOT(endGame(int)));
    QObject::connect(timer::timer, SIGNAL(timeout()), this, SLOT(updateTimerText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Public slots
void MainWindow::enablePlay() {
    ui->actionStart->setEnabled(true);
}

void MainWindow::initGame()
{
    ui->actionStart->setEnabled(false);
    chessboard->setNewChessboard();

    if (network::server) {
        myTurn();
        QObject::connect(network::server->command, SIGNAL(myTurn()), this, SLOT(myTurn()));
        QObject::connect(network::server->command, SIGNAL(endGame(int)), this, SLOT(endGame(int)));
    }

    if (network::client) {
        theirTurn();
        QObject::connect(network::client->command, SIGNAL(myTurn()), this, SLOT(myTurn()));
        QObject::connect(network::client->command, SIGNAL(endGame(int)), this, SLOT(endGame(int)));
    }

    QObject::connect(chessboard->chessgrid, SIGNAL(theirTurn()), this, SLOT(theirTurn()));
    QObject::connect(this->chessboard->chessgrid, SIGNAL(colorDecided()), this, SLOT(colorDecided()));
    QObject::connect(chessboard->chessgrid, SIGNAL(endGame(int)), this, SLOT(endGame(int)));
}

void MainWindow::endGame(int winColor)
{
    if (dialog == nullptr) {
        dialog = new EndDialog();
    }
    if (winColor == 0) {
        dialog->setWinColor("Blue");
    } else if (winColor == 1) {
        dialog->setWinColor("Red");
    }
    dialog->show();

    ui->colorLabel->setText("");
    ui->turnLabel->setText("");
    ui->actionSurrender->setEnabled(false);

    if (network::server) {
        ui->actionStart->setEnabled(true);
    }

    timer::currTimer = 20;
    timer::timer->stop();
    ui->timer->display(0);
}

void MainWindow::updateTimerText()
{
    if (timer::currTimer > 0) {
        timer::currTimer--;
    } else {
        timer::overTimeCnt++;
        if (timer::overTimeCnt > 2) {
            QString cmd = QString("!end %1").arg(player::theirColor);
            if (network::server) {
                network::server->sendData(cmd);
            }
            if (network::client) {
                network::client->sendData(cmd);
            }
            endGame(player::theirColor);
        }

        theirTurn();
        if (network::server) {
            network::server->sendData("!act -2 -2 -2 -2 !pas");
        }
        if (network::client) {
            network::client->sendData("!act -2 -2 -2 -2 !pas");
        }
    }
    ui->timer->display(timer::currTimer);
}

void MainWindow::colorDecided()
{
    if (player::myColor == 0) {
        ui->colorLabel->setText("Your color is blue");
    } else if (player::myColor == 1) {
        ui->colorLabel->setText("Your color is red");
    }
}

void MainWindow::myTurn()
{
    player::isTurn = true;
    ui->turnLabel->setText("Your turn");
    timer::timer->start(1000);
    if (player::steps >= 19) {
        ui->actionSurrender->setEnabled(true);
    }
}

void MainWindow::theirTurn()
{
    player::isTurn = false;
    ui->turnLabel->setText("Opponent's turn");
    timer::timer->stop();
    timer::currTimer = 20;
    ui->timer->display(timer::currTimer);
    if (player::steps >= 20) {
        ui->actionSurrender->setEnabled(true);
    }
}

// Private slots
void MainWindow::on_actionStart_triggered()
{
    emit gameStarted();
}

void MainWindow::on_actionSurrender_triggered()
{
    emit gameEnded(player::theirColor);
    QString cmd = QString("!end %1").arg(player::theirColor);
    if (network::server) {
        network::server->sendData(cmd);
    }
    if (network::client) {
        network::client->sendData(cmd);
    }
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
        QObject::connect(network::server, SIGNAL(enablePlay()), this, SLOT(enablePlay()));
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
        QObject::connect(network::client, SIGNAL(startGame()), this, SLOT(initGame()));
    }
    network::client->show();
}

