#include "database.h"

Database::Database()
{

}



void Database::createTable() {
    QSqlQuery query("CREATE TABLE countymap (id INTEGER PRIMARY KEY, name TEXT, shape TEXT, loc TEXT)");
    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();
    QSqlQuery querystats("CREATE TABLE countystats (id INTEGER PRIMARY KEY, name TEXT, population NUMBER)");
    if(!querystats.isActive())
        qWarning() << "ERROR: " << querystats.lastError().text();
}

void Database::insert() {
    QSqlQuery query;
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(0, 'warren','365v219w365v275w408v275w424v273w424v219', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(1, 'madison','308v219w308v276w365v275w365v219', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(2, 'polk','365v275w365v292w362v292w362v337w421v337w421v292w424v292w424v273w408v275', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(3, 'dallas','308v275w308v292w303v292w303v337w362v337w362v292w365v292w365v275', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    //if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(4, 'story','377v337w377v397w436v397w436v337', '100x100');"))
    //  qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countystats (id, name, population) VALUES(0, 'warren', 51466);"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countystats (id, name, population) VALUES(1, 'madison', 16338);"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countystats (id, name, population) VALUES(2, 'polk', 490161);"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countystats (id, name, population) VALUES(3, 'dallas', 93453);"))
      qWarning() << "ERROR: " << query.lastError().text();
    //if(!query.exec("INSERT INTO countystats (id, name, population) VALUES(4, 'story', 97117);"))
    //  qWarning() << "ERROR: " << query.lastError().text();
}

void Database::querySingle(int Id) {
    QString name;
    QSqlQuery query;
    query.prepare("SELECT name FROM countymap WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    qDebug() << "Name: " << query.value(0).toString() << endl;
}

void Database::queryPopulation(int Id) {
    QString name;
    QString population;
    QSqlQuery query;
    query.prepare("SELECT name, population FROM countystats WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    qDebug() << "Name: " << query.value(0).toString()  << "Population: " << query.value(1).toString() << endl;
}

QString Database::queryMapShape(int Id) {
    QString shape;
    QSqlQuery query;
    query.prepare("SELECT shape FROM countymap WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    return query.value(0).toString();
}

QString Database::queryMapLoc(int Id) {
    QString shape;
    QSqlQuery query;
    query.prepare("SELECT loc FROM countymap WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    return query.value(0).toString();
}

void Database::queryMultiple() {
    QSqlQuery query("SELECT * FROM countymap");
    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
       qDebug() << id << "  \t" << name;
    }
}
