#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTimer>
#include "chessboard.h"
#include "chessgrid.h"
#include "chesspiece.h"
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
    QTimer *timer = new QTimer();

signals:
    void gameStarted();
    void gameEnded();

public slots:
    void initGame();
    void endGame();
    void updateTimerText();

private slots:
    void on_actionStart_triggered();
    void on_actionSurrender_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout = new QVBoxLayout();
    int currTimer = 0;

};
#endif // MAINWINDOW_H
