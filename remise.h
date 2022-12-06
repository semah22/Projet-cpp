#ifndef Remise_H
#define Remise_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPainter>
#include <QPaintEvent>
class Remise
{public:
    Remise();
    Remise(int, float , int , QString);
    float get_taux();
    int get_id();
    int get_ide();
    QString get_type();
    bool ajouter();
    bool verif(int);
    bool supprimer(int);

private:
    int id,ide;
    float taux;
    QString type ;
};

#endif // Remise_H

