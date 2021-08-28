#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    ui->setupUi(this);
}

EndDialog::~EndDialog()
{
    delete ui;
}

void EndDialog::setWinColor(QString color)
{
    QString text = QString("%1 wins!").arg(color);
    ui->winTeam->setText(text);
}

void EndDialog::noWinner()
{
    ui->winTeam->setText("Colors are not decided. No winner!");
}
