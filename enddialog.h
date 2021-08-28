#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class EndDialog;
}

class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(QWidget *parent = nullptr);
    ~EndDialog();
    void setWinColor(QString color);
    void noWinner();

private:
    Ui::EndDialog *ui;
    QString winColor;
};

#endif // ENDDIALOG_H
