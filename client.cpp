#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    command = new Command();
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
    QByteArray block = readWriteSocket->readAll();
    QDataStream ds(&block, QIODevice::ReadOnly);
    ds >> currentData;

    qInfo() << currentData;

    if (currentData.mid(0, 4) != "!sta") {
        command->parse(currentData);
    } else {
        receiveSeq(currentData);
    }
}

void Client::receiveSeq(QString data)
{
    QList <QString> rawSeq = data.split(QRegularExpression("\\s+"));
    QList <int> seq;

    for (int i = 1; i < rawSeq.size(); i++) seq.append(rawSeq[i].toInt());

    emit startGame();
    emit receivedSeq(seq);
}

void Client::sendData(QString data)
{
    QByteArray block;
    QDataStream ds(&block, QIODevice::WriteOnly);
    ds << data;
    readWriteSocket->write(block);
}

void Client::on_doneButton_clicked()
{
    this->hide();
}
