#include "invite.h"
#include<QSqlQuery>
invite::invite()
{
 cin=0; nom=""; prenom="" ; metier="";age=0;password=0;
}
invite::invite(int cin,QString nom,QString prenom,QString metier,int age,int password)
{this->cin=cin; this->nom=nom; this->prenom=prenom;this->metier=metier;this->age=age;this->password=password;}
int invite::getcin(){return cin;}
QString invite::getnom(){return nom;}
QString invite::getprenom(){return prenom;}
QString invite::getmetier(){return metier;}
int invite::getage(){return age;}
int invite::getpassword(){return password;}
void invite::setcin(int cin){this->cin=cin;}
void invite::setnom(QString nom){this->nom=nom;}
void invite::setprenom(QString prenom){this->prenom=prenom;}
void invite::setmetier(QString metier){this->metier=metier;}
void invite::setage(int age){this->age=age;}
void invite::setpassword(int password){this->password=password;}
bool invite::ajouter()
{

        QString cin_string= QString::number(cin);
         QString age_string= QString::number(age);
          QString password_string= QString::number(password);
        QSqlQuery query;
              query.prepare("INSERT INTO employer (CIN, NOM,PRENOM,METIER,AGE,PASSWORD) "
                            "VALUES (:cin, :nom, :prenom, :metier, :age, :password)");
              query.bindValue(":cin",cin_string);
              query.bindValue(":nom", nom);
              query.bindValue(":prenom", prenom);
               query.bindValue(":metier", metier);
               query.bindValue(":age",age_string);
               query.bindValue(":password",password_string);
              return query.exec();




        }
bool invite::supprimer(int cin)
{
    QSqlQuery query;
          query.prepare("delete from employer where cin=:cin");
          query.bindValue(0,cin);

          return query.exec();




}







QSqlQueryModel* invite::afficher()
{
        QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM employer ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("AGE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));






  return model;
}
QSqlQueryModel* invite::chercher_invite(QString rech){
    QString sQuery="SELECT cin,nom,prenom,metier, age, password FROM employer WHERE nom LIKE'%"+rech+"%' or prenom LIKE'%"+rech+"%'or metier LIKE'%"+rech+"%'or age LIKE'%"+rech+"%'or password LIKE'%"+rech+"%' ";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}

bool invite::modifier()
{
     QSqlQuery query;
     QString cin_string= QString::number(cin);
 QString age_string= QString::number(age);
 QString password_string= QString::number(password);
     query.prepare("UPDATE employer SET nom=:nom , prenom=:prenom , metier=:metier, age=:age, password=:password "
                   " where cin= :cin");
     query.bindValue(":cin",cin_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":metier",metier);
     query.bindValue(":age",age_string);
     query.bindValue(":password",password_string);


     return query.exec();

}

QSqlQueryModel * invite::afficher_tri()
{
    QSqlQuery query;
  QString squery="SELECT cin ,nom,prenom,metier,age from employer ORDER BY cin";
  QSqlQueryModel*model=new QSqlQueryModel();
  query.prepare(squery);
  query.exec();
  model->setQuery(query);
  return model;
}
int invite::calculer1(int choix,int choix2)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM employer WHERE age BETWEEN (:choix) AND (:choix2)");
          query.bindValue(":choix",choix);
          query.bindValue(":choix2",choix2);

          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total; }
