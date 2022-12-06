#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"facture.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_tri_id_clicked();

    void on_tri_num_fact_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_QR_clicked();

    void on_add_pushButton_clicked();

    void on_remise_clicked();

private:
    Ui::MainWindow *ui;
     facture FACTT;
};
#endif // MAINWINDOW_H
