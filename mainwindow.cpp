#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employer.h"
#include <QMessageBox>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QUrl>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString cin,password;
          cin =ui->lineEdit_CINLOG->text();
          password=ui->lineEdit->text();

          employer I;
          QSqlQuery qry,query;

      if(qry.exec("select CIN,PASSWORD from INVITER where CIN='"+cin +"' and PASSWORD='"+password+"'"))
      {
              int count=0;
      while(qry.next())
      {
            count++;



       if(count==1)
       {
           query.prepare("INSERT INTO INVITER(CIN,PASSWORD) "
                                  "VALUES (:CIN,  :PW)");

                    query.bindValue(":CIN",qry.value(0).toString());

                    query.bindValue(":PW",qry.value(2).toString());

                    query.exec();



            this->hide();
              ui->lineEdit_CINLOG->clear();
              ui->lineEdit->clear();

              Dialog dialog;
                          dialog.setModal(true);
                          dialog.exec();








              }
      }

              if(count<1)
              {


              }
}}
