#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QDataStream>
#include "command.h"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    bool connectToServer();
    void sendData(QString data);
    void receiveSeq(QString data);
    Command* command;

signals:
    void receivedSeq(QList <int> seq);
    void startGame();

public slots:
    void receiveData();

private slots:
    void on_connectButton_clicked();
    void on_doneButton_clicked();

private:
    Ui::Client *ui;
    QString serverIP;
    quint16 serverPort;
    QTcpSocket *readWriteSocket;
    QString currentData;

};

#endif // CLIENT_H
