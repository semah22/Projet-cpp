#include "facture.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>

facture::facture()
{
    id_client=0;
    num_tel =0;
    num_fact =0;
    date_fact="";
    montant_fact=0;
    payer_par_cheques="";
    payer_par_especes="";

}
facture::facture(int id_client,int num_tel,int num_fact,QString date_fact,int montant_fact,QString payer_par_cheques,QString payer_par_especes)
{
this->id_client=id_client;
this->num_tel=num_tel;
this->num_fact=num_fact;
this->date_fact=date_fact;
this->montant_fact=montant_fact;
this->payer_par_cheques=payer_par_cheques;
this->payer_par_especes=payer_par_especes;

}
int facture::getid_client(){return id_client;}
int facture::getnum_tel(){return num_tel;}
int facture::getnum_fact(){return num_fact;}
QString facture::getdate_fact(){return date_fact;}
int facture::getmontant_fact(){return montant_fact;}
QString facture::getpayer_par_cheques(){return payer_par_cheques;}
QString facture::getpayer_par_especes(){return payer_par_especes;}

void facture::setid_client(int id_client){this->id_client=id_client;}
void facture::setnum_tel(int num_tel){this->num_tel=num_tel;}
void facture::setnum_fact(int num_fact){this->num_fact=num_fact;}
void facture::setdate_fact(QString date_fact){this->date_fact=date_fact;}
void facture::setmontant_fact(int montant_fact){this->montant_fact=montant_fact;}
void facture::setpayer_par_cheques(QString payer_par_cheques){this->payer_par_cheques=payer_par_cheques;}
void facture::setpayer_par_especes(QString payer_par_especes){this->payer_par_especes=payer_par_especes;}


bool facture::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id_client);
    QString num_tel_string= QString::number(num_tel);
    QString num_fact_string= QString::number(num_fact);
    QString montant_fact_string= QString::number(montant_fact);
         query.prepare("INSERT INTO Facture (id_client, num_tel , num_fact , date_fact ,montant_fact,payer_par_cheques,payer_par_especes ) "
                       "VALUES (:id_client, :num_tel, :num_fact, :date_fact, :montant_fact , :payer_par_cheques , :payer_par_especes)");
         query.bindValue(":id_client", id_string);
         query.bindValue(":num_tel", num_tel_string);
         query.bindValue(":num_fact", num_fact_string);
         query.bindValue(":date_fact", date_fact);
         query.bindValue(":montant_fact", montant_fact_string);
         query.bindValue(":payer_par_cheques", payer_par_cheques);
         query.bindValue(":payer_par_especes", payer_par_especes);

         return query.exec();


}

bool facture::supprimer(int id_client)
{
    QSqlQuery query;
    QString res=QString::number(id_client);
    query.prepare("Delete from facture where ID_client= :id_client");
    query.bindValue(":id_client",res);
    return query.exec();
}
QSqlQueryModel* facture::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT * FROM facture");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client "));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("num_tel "));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_fact "));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_fact "));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant_fact  "));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("payer_par_cheques "));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("payer_par_especes "));

return model;

}
bool facture::modifier(int id_client)
{
    QSqlQuery query;

       QString res= QString::number(id_client);
       query.prepare("UPDATE Facture SET id_client =:id_client ,num_tel =:num_tel ,num_fact =:num_fact  ,date_fact =:date_fact,montant_fact  =:montant_fact, payer_par_cheques =:payer_par_cheques, payer_par_especes=:payer_par_especes   WHERE id_client=:id_client");
       query.bindValue(":id_client", id_client);
       query.bindValue(":num_tel", num_tel);
       query.bindValue(":num_fact", num_fact);
       query.bindValue(":date_fact", date_fact);
       query.bindValue(":montant_fact", montant_fact);
       query.bindValue(":payer_par_cheques", payer_par_cheques);
       query.bindValue(":payer_par_especes", payer_par_especes);

          return    query.exec();
}
QSqlQueryModel * facture::recherche_facture(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from Facture where id_client like '%"+search+"%' or num_tel like '%"+search+"%' or num_fact like '%"+search+"%' or date_fact like '%"+search+"%' or montant_fact like '%"+search+"%' ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}
QSqlQueryModel * facture::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Facture ORDER BY id_client");
    return model;

}
QSqlQueryModel * facture::triNUM_FACT()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Facture ORDER BY nom");
    return model;

}
int facture::statistiquespayer(QString payer)
{
    QSqlQuery query;
    query.prepare("select count(*) from FACTURE where payer_par_cheques=:payer_par_cheques ");
    query.bindValue(":payer_par_cheques",payer);
    query.exec();
    query.next();
    return query.value(0).toInt();
}

QSqlQueryModel*  facture::remise()
{

    QSqlQueryModel *model=new QSqlQueryModel();
             model->setQuery("SELECT id_client,num_tel,num_fact,date_fact,0.8*montant_fact  FROM FACTURE WHERE (MONTANT_FACT>=3000) ");
             model->setHeaderData(4,Qt::Horizontal,QObject::tr("apres remise"));






   return model;

   }





