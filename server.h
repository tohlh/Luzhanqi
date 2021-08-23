#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpServer>

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

public slots:
    void acceptConnection();
    void receiveData();
    void sendData();

private slots:
    void on_doneButton_clicked();

private:
    Ui::Server *ui;
    QTcpServer* listenSocket;
    QTcpSocket* readWriteSocket;
    QString currentData;
    QDataStream in;
};

#endif // SERVER_H
