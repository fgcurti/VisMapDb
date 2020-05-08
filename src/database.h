#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database
{
public:
    Database();
    void createTable();

    void insert();
    void querySingle(int Id);
    void queryPopulation(int Id);
    QString queryMapShape(int Id);

    QString queryMapLoc(int Id);
    void queryMultiple();
};

#endif // DATABASE_H
