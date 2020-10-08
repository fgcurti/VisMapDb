
#include "information.h"
#include "database.h"
#include "image.h"
#include "inputoutput.h"
#include <QDebug>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;



int main() {
    int countyHeight = 0;
    int countyWidth = 0;
    int keepRunning = 0;
    string countyName;
    double area, perimeter;

    cout << "Welcome to the VisMapDb Program" << endl;
    cout << "-------------------------------" << endl;

    Information info;
    try
    {
        area = info.calcArea(countyHeight,countyWidth);
        cout << "The area is " << area << endl;
    }
    catch(const char* err1)
    {
        cout << err1;
    }

    try
    {
        perimeter = info.calcPerimeter(countyHeight,countyWidth);
        cout << "The perimeter is " << perimeter << endl;
    }
    catch(const char* err2)
    {
        cout << err2;
    }

    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        cout << "ERROR" << endl;
        qWarning() << "ERROR: " << db.lastError();
    }
    Database mydatabase;
    mydatabase.createTable();
    mydatabase.insert();


    InputOutput io;
    list<int> tempList;
    while (keepRunning != -1){
        cout << "Here are your counties." << endl;
        cout << "Id \t Name" << endl;
        cout << "--------------------------" << endl;
        mydatabase.queryMultiple();
        cout << endl;
        cout << "What do you want to do:" << endl;
        cout << "1 : Generate a map" << endl;
        cout << "2 : get statistics" << endl;
        cout << "3 : Enter map shape features and statistics" << endl;
        cout << "-1: Quit" << endl;
        int numChoice = -1;
        cin >> numChoice;
        if (numChoice == -1){
            cout << "Thank you" << endl;
            keepRunning = numChoice;
        }
        else if (numChoice == 1){
            tempList = io.getMaps();
            list<list<list<int> > > county_list;
            list<list<int> > single_list;
            list<int> point_list;

            for (auto it = tempList.begin(); it != tempList.end(); ++it) {
                QString shapeStr = mydatabase.queryMapShape(*it);
                string str = shapeStr.toLocal8Bit().constData();
                replace(str.begin(), str.end(), 'w', ' ');
                stringstream ss1(str);
                string temp;
                int tempint;
                int ii = 0;
                while (ss1 >> temp){
                    replace(temp.begin(), temp.end(), 'v', ' ');
                    stringstream ss2(temp);
                    int jj = 0;
                     while (ss2 >> tempint){
                         point_list.push_back(tempint);
                         jj++;
                     }
                     single_list.push_back(point_list);
                     point_list.erase(point_list.begin(), point_list.end());
                    ii++;
                }
                county_list.push_back(single_list);
                single_list.erase(single_list.begin(), single_list.end());
            }
                Image myimage;
                myimage.saveImage(county_list);
        }
        else if (numChoice == 2){
            tempList = io.getStats();
            for (auto it = tempList.begin(); it != tempList.end(); ++it) {
                mydatabase.queryPopulation(*it);
            }
        }
        else{
            io.writeInfo();
        }
    }
        return 0;
}
