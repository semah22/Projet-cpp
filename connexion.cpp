#include "connexion.h"

//Test Connexion Git

Connexion::Connexion()
{

}

bool Connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("semmah");//inserer nom de l'utilisateur
db.setPassword("semah11");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
