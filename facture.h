#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQueryModel>

class facture
{
public:
    facture();
    facture(int,int,int,QString,int,QString,QString);
    int getid_client();
    int getnum_tel();
    int getnum_fact();
    QString getdate_fact();
    int getmontant_fact();
    QString getpayer_par_cheques();
    QString getpayer_par_especes();

    void setid_client(int);
    void setnum_tel(int);
    void setnum_fact(int);
    void setdate_fact(QString);
    void setmontant_fact(int);
    void setpayer_par_cheques(QString);
    void setpayer_par_especes(QString);



    bool ajouter();
    bool supprimer(int id_client);
    QSqlQueryModel* afficher();
    bool modifier(int id_client);
    QSqlQueryModel* recherche_facture(QString search);
    QSqlQueryModel* triID();
    QSqlQueryModel* triNUM_FACT();
    int statistiquespayer(QString payer);
    QSqlQueryModel*remise();
private:
    int id_client,num_tel,num_fact,montant_fact;
    QString date_fact,payer_par_cheques,payer_par_especes ;
};
#endif // FACTURE_H
