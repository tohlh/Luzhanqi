#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
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
    ui->notificationLabel->setText("Client connected!");
    ui->doneButton->setEnabled(true);
    readWriteSocket = listenSocket->nextPendingConnection();
    QObject::connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void Server::receiveData()
{
    currentData = readWriteSocket->readAll();
}

void Server::sendData()
{
    readWriteSocket->write("HELLO FROM SERVER");
}

void Server::on_doneButton_clicked()
{
    this->hide();
}

