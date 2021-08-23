#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

bool Client::connectToServer()
{
    readWriteSocket = new QTcpSocket(this);
    readWriteSocket->connectToHost(serverIP, serverPort);
    return readWriteSocket->waitForConnected(5000);
}

void Client::on_connectButton_clicked()
{
    serverIP = ui->userInputIP->text();
    serverPort = ui->userInputPort->text().toInt();

    if (connectToServer()) {
        ui->notifcationLabel->setText("Connected to host!");
        QObject::connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
        ui->doneButton->setEnabled(true);
    } else {
        ui->notifcationLabel->setText("Unable to connect to host");
        ui->doneButton->setEnabled(false);
    }
}

void Client::receiveData()
{
    currentData = this->readWriteSocket->readAll();
    ui->notifcationLabel->setText(currentData);
}

void Client::sendData()
{
    readWriteSocket->write("HELLO GUYS");
}

void Client::on_doneButton_clicked()
{
    this->hide();
}
