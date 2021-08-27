#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpServer>
#include "command.h"

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    void initServer();
    void sendData(QString data);
    void sendChessSeq(QList<int> &seq);
    Command* command;

public slots:
    void acceptConnection();
    void receiveData();
    void disconnected();

signals:
    void theyReady();
    void enablePlay();
    void stopGame();

private slots:
    void on_doneButton_clicked();

private:
    Ui::Server *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
    QString currentData;
};

#endif // SERVER_H
