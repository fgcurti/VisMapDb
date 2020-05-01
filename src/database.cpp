#include "database.h"

Database::Database()
{

}



void Database::createTable() {
    QSqlQuery query("CREATE TABLE countymap (id INTEGER PRIMARY KEY, name TEXT, shape TEXT, loc TEXT)");
    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();
}

void Database::insert() {
    QSqlQuery query;
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(0, 'marion','60v120w120v120w120v60w60v60', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(1, 'marion','50v100w75v150w125v100w75v50', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(2, 'warren','80v130w105v180w155v130w105v80', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(3, 'polk','80v130w110v180w155v150w125v50w105v60', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(4, 'madison','50v100w75v150w115v100w75v50', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(5, 'madison','90v70w100v80w110v70', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(6, 'madison','95v100w100v100w100v95w95v95', '100x100');"))
      qWarning() << "ERROR: " << query.lastError().text();
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
       QString name = query.value(0).toString();
       qDebug() << name;
    }
}
