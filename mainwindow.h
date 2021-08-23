#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTimer>
#include "chessboard.h"
#include "chessgrid.h"
#include "chesspiece.h"
#include "server.h"
#include "client.h"
#include "global.h"
#include "enddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Chessboard *chessboard = new Chessboard();

signals:
    void gameStarted();
    void gameEnded();


public slots:
    void enablePlay();
    void initGame();
    void endGame();
    void updateTimerText();
    void myTurn();
    void theirTurn();

private slots:
    void on_actionStart_triggered();
    void on_actionSurrender_triggered();
    void on_actionCreate_a_connection_triggered();
    void on_actionConnect_to_server_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout = new QVBoxLayout();


};
#endif // MAINWINDOW_H
