#ifndef DIALOG_H
#define DIALOG_H
#include "employer.h"
#include <QDialog>
#include "ui_dialog.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_recherche_clicked();

    void on_pb_update_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::Dialog *ui;
    employer I;

};

#endif // DIALOG_H
