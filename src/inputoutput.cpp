#include "inputoutput.h"
#include "database.h"
#include <QSqlQuery>
#include <QHash>
#include <QSqlDatabase>
#include <QVariant>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

InputOutput::InputOutput()
{

}

list<int> InputOutput::getMaps(){
    int keepGoing = 1;
    int countyId = 1;
    list<int> countyIdList;
    while(keepGoing > 0){
        cout << "Enter the ID of the county you want the map of." << endl;
        cin >> countyId;
        countyIdList.push_back(countyId);
        cout << "Do you want to quit adding counties. If so enter -1, otherwise enter 1." << endl;
        cin >> keepGoing;
    }

    return countyIdList;
}

list<int> InputOutput::getStats(){
    int keepGoing = 1;
    int countyId = 1;
    list<int> countyIdList;
    while(keepGoing > 0){
        cout << "Enter the ID of the county you want the stats of." << endl;
        cin >> countyId;
        countyIdList.push_back(countyId);
        cout << "Do you want to quit adding counties. If so enter -1, otherwise enter 1." << endl;
        cin >> keepGoing;
    }

    return countyIdList;
}


void InputOutput::writeInfo(){
    int keepGoing = 1;
    int countyId = 1;
    string cntyName;
    string cntyShape;
    string cntyLocation;
    string cntyPopulation;
    while(keepGoing > 0){
        cout << "Enter the ID of the county." << endl;
        cin >> countyId;
        cout << "Enter the Name of the county." << endl;
        cin >> cntyName;
        QString countyName = QString::fromStdString(cntyName);
        cout << "Enter the vertices of the county.  Use xxvyywxxvyywxxvyy format" << endl;
        cin >> cntyShape;
        QString countyShape = QString::fromStdString(cntyShape);
        cout << "Enter the location of the county. Two numbers separated by x" << endl;
        cin >> cntyLocation;
        QString countyLocation = QString::fromStdString(cntyLocation);
        cout << "Enter the population of the county." << endl;
        cin >> cntyPopulation;
        QString countyPopulation = QString::fromStdString(cntyPopulation);
        QSqlQuery query;
        query.prepare("INSERT INTO countymap (id, name, shape, loc) VALUES(:id, :name, :shape, :loc)");
        query.bindValue(":id", countyId);
        query.bindValue(":name", countyName);
        query.bindValue(":shape", countyShape);
        query.bindValue(":loc", countyLocation);
        query.exec();


        QSqlQuery queryPop;
        queryPop.prepare("INSERT INTO countystats (id, name, population) VALUES(:id, :name, :population)");
        queryPop.bindValue(":id", countyId);
        queryPop.bindValue(":name", countyName);
        queryPop.bindValue(":population", countyPopulation);
        queryPop.exec();

        cout << "Do you want to quit adding counties. If so enter -1, otherwise enter 1." << endl;
        cin >> keepGoing;
    }

}



