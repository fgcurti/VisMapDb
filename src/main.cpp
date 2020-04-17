#include "information.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;

void createTable() {
    QSqlQuery query("CREATE TABLE countymap (id INTEGER PRIMARY KEY, name TEXT, shape TEXT, loc TEXT)");
    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();
}

void insert() {
    QSqlQuery query;
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(1, 'marion','0v0w10v0w10v10w0v10', '50x50');"))
      qWarning() << "ERROR: " << query.lastError().text();
}

void querySingle(int Id) {
    QString name;
    QSqlQuery query;
    query.prepare("SELECT name FROM countymap WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    qDebug() << "Name: " << query.value(0).toString() << endl;
}

QString queryMapShape(int Id) {
    QString shape;
    QSqlQuery query;
    query.prepare("SELECT shape FROM countymap WHERE id = :id");
    query.bindValue(":id", Id);
    query.exec();
    query.next();
    return query.value(0).toString();
}

void queryMultiple() {
    QSqlQuery query("SELECT * FROM countymap");
    while (query.next()) {
       QString name = query.value(0).toString();
       qDebug() << name;
    }
}

int main() {
    Information info;
    cout << "The area is " << info.calcArea(2,2) << endl;
    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        cout << "ERROR" << endl;
        qWarning() << "ERROR: " << db.lastError();
    }

    createTable();
    insert();

    qDebug() << "County Shape: " << queryMapShape(1) << endl;
    // 0v0w10v0w10v10w0v10
    QString x1 = queryMapShape(1);
    string str = x1.toLocal8Bit().constData();
    int n = std::count(x1.begin(), x1.end(), 'w');
    cout << "# of ws: " << n << endl;
    replace(str.begin(), str.end(), 'w', ' ');

    string myarray[n];
    stringstream ss(str);
    string temp;
    int ii = 0;
    while (ss >> temp){
        cout << "ii is: " << ii << endl;
        cout << "temp is: " << temp << endl;
        myarray[ii].assign(temp);
        ii++;
    }
    return 0;
}
