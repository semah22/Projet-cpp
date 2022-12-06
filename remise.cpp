#include "remise.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE
Remise::Remise::facture()
{
id=0;
ide=0;
taux=0;
type="vide";
}
Remise::Remise(int id,float taux , int ide , QString type)
{
  this->id=id;
  this->ide=ide;
  this->taux=taux;
  this->type=type;
}
int Remise::get_id(){return  id;}
int Remise::get_ide(){return ide;}
float Remise::get_taux(){return taux;}
QString Remise::get_type(){return type;}
bool Remise::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
QString taux_string;
taux_string.setNum(taux);
QString ide_string= QString::number(ide);
query.prepare("INSERT INTO Remise (id, taux, idEvent,type) VALUES (:id, :taux, :idEvent, :type)");
query.bindValue(":id", res);
query.bindValue(":taux", taux_string);
query.bindValue(":idEvent", ide_string);
query.bindValue(":type", type);
return    query.exec();

}


QSqlQueryModel * Remise::afficher(){
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from Remise");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Taux"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEvenement"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

bool Remise::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from Remise where id = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool Remise::modifier(){
    QSqlQuery query;
    QString res= QString::number(this->id);
    QString taux_string;
    taux_string.setNum(this->taux);
    QString ide_string= QString::number(this ->ide);
    query.prepare("UPDATE Remise SET  taux =:taux , idevent=:idEvent WHERE id = :id");
    query.bindValue(":id",res);
    query.bindValue(":taux",taux_string);
    query.bindValue(":idEvent",ide_string);
    return  query.exec();
}
