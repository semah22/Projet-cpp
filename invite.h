#ifndef INVITE_H
#define INVITE_H
#include <QString>
#include <QSqlQueryModel>

class invite
{
public:
    invite();
    invite(int,QString,QString,QString,int,int);
        int getcin();
        QString getnom();
        QString getprenom();
        QString getmetier();
        int getage();
        int getpassword();
        void setcin(int);
        void setnom(QString);
        void setprenom(QString);
        void setmetier(QString);
        void setage(int);
        void setpassword(int);


        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        QSqlQueryModel*chercher_invite(QString rech);
        bool modifier();
        QSqlQueryModel*afficher_tri();
        int calculer1(int choix,int choix2);
private:
    int cin,age,password;
    QString nom , prenom, metier;
};

#endif // INVITE_H