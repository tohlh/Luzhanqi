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
    winColor = color;
    ui->winTeam->setText(winColor + tr(" wins!"));
}
