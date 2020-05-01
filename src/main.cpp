
#include "information.h"
#include "database.h"
#include "image.h"
#include <QDebug>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
//#include <image.h>


int main() {

    int height = 200;
    int width = 200;
    int countyHeight = 0;
    int countyWidth = 0;
    string countyName;
    int population, countyId;
    double area, perimeter;
    const int bytesPerPixel = 3; /// red, green, blue
    unsigned char image[height][width][bytesPerPixel];
    char* imageFileName = "IowaCountyImage.bmp";

    cout << "Welcome to the VisMapDb Program" << endl;
    //cout << "Input the name of the county you want to work with." << endl;
    //cin >> countyName;
    //cout << "Input the population of the county." << endl;
    //cin >> population;
    /*cout << "Enter the length of the county." << endl;
    cin >> countyHeight;
    cout << "Enter the width of the county." << endl;
    cin >> countyWidth;
    */
    cout << "Enter the ID of the county you want the map of." << endl;
    cin >> countyId;

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

    qDebug() << "County Shape: " << mydatabase.queryMapShape(countyId) << endl;
    QString shapeStr = mydatabase.queryMapShape(countyId);
    string str = shapeStr.toLocal8Bit().constData();
    int n = std::count(shapeStr.begin(), shapeStr.end(), 'w');
    replace(str.begin(), str.end(), 'w', ' ');

    string myarray[99];
    string myarray2D[99][2];
    stringstream ss1(str);
    string temp;
    int ii = 0;
    while (ss1 >> temp){
        myarray[ii].assign(temp);
        replace(temp.begin(), temp.end(), 'v', ' ');
        stringstream ss2(temp);
        int jj = 0;
         while (ss2 >> temp){
             myarray2D[ii][jj].assign(temp);
             jj++;
         }
        ii++;
    }
    Image myimage;
    myimage.saveImage(myarray2D, n);
    return 0;
}

