#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    command = new Command();
    listenSocket =  new QTcpServer(this);
    QObject::connect(listenSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

Server::~Server()
{
    delete ui;
}

void Server::initServer()
{
    if (!listenSocket->listen()) {
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    ui->IP->setText(tr("%1:%2").arg(ipAddress).arg(listenSocket->serverPort()));
}

void Server::acceptConnection()
{
    emit enablePlay();
    ui->notificationLabel->setText("Client connected!");
    ui->doneButton->setEnabled(true);
    readWriteSocket = listenSocket->nextPendingConnection();
    QObject::connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    QObject::connect(readWriteSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Server::receiveData()
{
    QByteArray block = readWriteSocket->readAll();
    QDataStream ds(&block, QIODevice::ReadOnly);
    ds >> currentData;
    command->parse(currentData);
}

void Server::disconnected()
{
    ui->notificationLabel->setText("The client has disconnected!");
    this->show();
    emit stopGame();
}

void Server::sendData(QString data)
{
    QByteArray block;
    QDataStream ds(&block, QIODevice::WriteOnly);
    ds << data;
    readWriteSocket->write(block);
}

void Server::sendChessSeq(QList<int> &seq)
{
    QString cmd = "!sta ";

    for (int i = 0; i < seq.size(); i++) {
        cmd += QString("%1").arg(seq[i]);
        cmd += " ";
    }

    sendData(cmd);
}

void Server::on_doneButton_clicked()
{
    this->hide();
}
