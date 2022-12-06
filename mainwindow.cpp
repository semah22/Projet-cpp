#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "facture.h"
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QDirModel>
#include <QtPrintSupport/QPrintDialog>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>
#include <QUrl>
#include <iostream>
#include <QtCharts>
#include"QrCode.hpp"
#include<qsqlquery.h>
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_id_client->setValidator(new QIntValidator(0, 9999999, this));
    ui->tabView->setModel(FACTT.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{
    int id_client=ui->le_id_client->text().toInt();
    int num_tel =ui->le_num_tel->text().toInt();
    int num_fact =ui->le_num_fact ->text().toInt();
    QString date_fact =ui->le_date_fact->text();
    int montant_fact =ui->le_montant_fact->text().toInt();
    QString payer_par_cheques =ui->le_payer_par_cheques->text();
    QString payer_par_especes =ui->le_payer_par_especes->text();

    facture FACTT(id_client,num_tel,num_fact,date_fact,montant_fact,payer_par_cheques,payer_par_especes);
    bool test=FACTT.ajouter();

    if(test){

        ui->tabView->setModel(FACTT.afficher());
      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
    { QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pb_modifier_clicked()
{
    int id_client = ui->le_id_client->text().toInt();
        int num_tel= ui->le_num_tel->text().toInt();
         int num_fact= ui->le_num_fact->text().toInt();
         QString date_fact = ui->le_date_fact->text();
         int montant_fact= ui->le_montant_fact->text().toInt();
         QString payer_par_cheques = ui->le_payer_par_cheques->text();
         QString payer_par_especes = ui->le_payer_par_especes->text();

        facture FACTT(id_client,num_tel,num_fact,date_fact,montant_fact,payer_par_cheques,payer_par_especes);
        bool test=FACTT.modifier(id_client);
        if(test)
        {

            ui->tabView->setModel(FACTT.afficher());//refresh

                   QMessageBox::information(nullptr, QObject::tr("effectué"),
                        QObject::tr(" Modifié.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
                   ui->le_id_client->clear();
                   ui->le_num_tel->clear();
                   ui->le_num_fact->clear();
                   ui->le_date_fact->clear();
                   ui->le_payer_par_cheques->clear();
                    ui->le_payer_par_especes->clear();
       }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                        QObject::tr("non modifié !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->le_id_client->clear();
            ui->le_num_tel->clear();
            ui->le_num_fact->clear();
            ui->le_date_fact->clear();
            ui->le_montant_fact->clear();




        }
}

void MainWindow::on_pb_supprimer_clicked()
{
    int id =ui->num_s->text().toInt();
    bool test=FACTT.supprimer(id);
    if(test)
   {
        ui->tabView->setModel(FACTT.afficher());
      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("suppression effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
      QMessageBox::critical(nullptr, QObject::tr("not ok"),
      QObject::tr("suppression non effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_tri_id_clicked()
{
     ui->tabView->setModel(FACTT.triID());
}

void MainWindow::on_tri_num_fact_clicked()
{
     ui->tabView->setModel(FACTT.triNUM_FACT());
}

void MainWindow::on_pushButton_clicked()
{
    facture FACTT;
        ui->tabView->setModel(FACTT.recherche_facture(ui->le_recherche->text()));
}


void MainWindow::on_pushButton_5_clicked()
{
        //pdf : vous trouver le fichier dans le dossier build

            QString strStream;
                        QTextStream out(&strStream);
                        const int rowCount = ui->tabView->model()->rowCount();
                        const int columnCount =ui->tabView->model()->columnCount();


                        out <<  "<html>\n"
                                "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                <<  QString("<title>%1</title>\n").arg("voyageur")
                                <<  "</head>\n"
                                "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                    "<h1>Liste des voyageurs</h1>"

                                    "<table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                            out << "<thead><tr bgcolor=#f0f0f0>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tabView->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tabView->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";
                            // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->tabView->isColumnHidden(column)) {
                                           QString data = ui->tabView->model()->data(ui->tabView->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table>\n"
                                   "</body>\n"
                                   "</html>\n";



                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);


                //QTextDocument document;
                //document.setHtml(html);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("mypdffile1.pdf");
                document->print(&printer);


    }


void MainWindow::on_pushButton_6_clicked()
{

            facture fact;
            QBarSet *set0 = new QBarSet("statistique : courbe");

            *set0 << fact.statistiquespayer("payer_par_cheques")<<fact.statistiquespayer("payer_par_especes") ;


            QColor color(0x6568F3);
            set0->setColor(color);

            QBarSeries *series = new QBarSeries();
            series->append(set0);




            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setBackgroundVisible(false);

            QColor bgColor(0xF4DCD3);
                           chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                           chart->setBackgroundVisible(true);

            QStringList categories;
            categories << "payer_par_cheques"<<"payer_par_especes" ;
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);

            QChartView *chartView = new QChartView(chart);

            chartView->setMinimumWidth(500);
            chartView->setMinimumHeight(300);
            chartView->setParent(ui->stat_2);
            chart->legend()->setAlignment(Qt::AlignBottom);
            chartView->show();


    }


void MainWindow::on_QR_clicked()
{
    int tabev=ui->tabView->currentIndex().row();
        QVariant idd=ui->tabView->model()->data(ui->tabView->model()->index(tabev,0));
        QString id= idd.toString();
        QSqlQuery qry;
        qry.prepare("select * from evenements where id_ev=:id");
        qry.bindValue(":id",id);
        qry.exec();
        int id_client,num_tel,num_fact,montant_fact;
        QString date_fact,payer_par_cheques,payer_par_espece,ids;
        while(qry.next()){
            date_fact=qry.value(1).toString();
            payer_par_cheques=qry.value(2).toString();
            payer_par_espece=qry.value(3).toString();

        }
        ids=QString(id);
        ids="id_client: "+ids+" num_tel: "+num_tel+" num_fact: "+num_fact+" montant_fact: "+montant_fact+"date_fact : "+date_fact+ "payer_par_cheques : "+payer_par_cheques+"payer_par_espece : "+payer_par_espece;
        QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(200,200);
        ui->qrlabel->setPixmap(QPixmap::fromImage(im));
}



void MainWindow::on_remise_clicked()
{
    QSqlQuery q;
       int t=0;
       q.prepare("SELECT montant_fact FROM FACTURE WHERE MONTANT_FACT>=3000");
       q.exec();
       while(q.next())
       {
           t++;
       }
       if(t>0)
       {
               if (FACTT.remise())

               {

                   ui->tabView->setModel(FACTT.remise());
                   QMessageBox :: information (nullptr, QObject ::tr("OK"),
                                QObject ::tr(" besoin de remise\n"
                                             "click cancel to exit"),
                           QMessageBox:: Cancel);
               }
               else
               {
                   QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                        QObject::tr("erreur.\n"
                                                    "click cancel to exit."),QMessageBox::Cancel);
               }
       }
       else
       {
           QMessageBox::information(nullptr,QObject::tr("not ok"),
                                QObject::tr("Pas besoin d'un remise.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
       }



    }

