#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGridLayout>
#include "chessboard.h"
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

signals:
    void gameStarted();
    void gameEnded();

public slots:
    void initGame();
    void endGame();

private slots:
    void on_actionStart_triggered();
    void on_actionSurrender_triggered();

private:
    Ui::MainWindow *ui;
    QGridLayout *layout = new QGridLayout();
    Chessboard *chessboard = new Chessboard();
};
#endif // MAINWINDOW_H
