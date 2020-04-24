
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

// See Stackoverflow Article: Writing BMP image in pure c/c++ without other libraries
const int bytesPerPixel = 3; /// red, green, blue
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;
void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int width, int paddingSize);
unsigned char* createBitmapInfoHeader(int height, int width);


void createTable() {
    QSqlQuery query("CREATE TABLE countymap (id INTEGER PRIMARY KEY, name TEXT, shape TEXT, loc TEXT)");
    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();
}

void insert() {
    QSqlQuery query;
    if(!query.exec("INSERT INTO countymap (id, name, shape, loc) VALUES(1, 'marion','50v100w75v150w125v100w75v50', '100x100');"))
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

QString queryMapLoc(int Id) {
    QString shape;
    QSqlQuery query;
    query.prepare("SELECT loc FROM countymap WHERE id = :id");
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

    int height = 200;
    int width = 200;
    int countyHeight = 0;
    int countyWidth = 0;
    string countyName;
    int population;
    double area, perimeter;
    unsigned char image[height][width][bytesPerPixel];
    char* imageFileName = "IowaCountyImage.bmp";

    cout << "Welcome to the VisMapDb Program" << endl;
    //cout << "Input the name of the county you want to work with." << endl;
    //cin >> countyName;
    //cout << "Input the population of the county." << endl;
    //cin >> population;
    cout << "Enter the length of the county." << endl;
    cin >> countyHeight;
    cout << "Enter the width of the county." << endl;
    cin >> countyWidth;

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

    createTable();
    insert();

    qDebug() << "County Shape: " << queryMapShape(1) << endl;
    QString shapeStr = queryMapShape(1);
    string str = shapeStr.toLocal8Bit().constData();
    int n = std::count(shapeStr.begin(), shapeStr.end(), 'w');
    cout << "# of ws: " << n << endl;
    replace(str.begin(), str.end(), 'w', ' ');

    string myarray[n + 1];
    string myarray2D[n + 1][3];
    stringstream ss1(str);
    string temp;
    int ii = 0;
    while (ss1 >> temp){
        cout << "ii is: " << ii << endl;
        cout << "temp is: " << temp << endl;
        myarray[ii].assign(temp);
        cout << "myarray[ii] = " << myarray[ii] << endl;
        replace(temp.begin(), temp.end(), 'v', ' ');
        stringstream ss2(temp);
        int jj = 0;
         while (ss2 >> temp){
             myarray2D[ii][jj].assign(temp);
             cout << "myarray[" << ii << "][" << jj << "] = " << myarray2D[ii][jj] << endl;
             jj++;
         }
        ii++;
    }

    qDebug() << "County Location: " << queryMapLoc(1) << endl;
    QString x1Loc = queryMapLoc(1);
    string strLoc = x1Loc.toLocal8Bit().constData();
    replace(strLoc.begin(), strLoc.end(), 'x', ' ');

    string myarrayLoc[2];
    stringstream ssLoc(strLoc);
    string tempLoc;
    int iiLoc = 0;
    while (ssLoc >> tempLoc){
        cout << "ii is: " << iiLoc << endl;
        cout << "tempLoc is: " << tempLoc << endl;
        myarrayLoc[iiLoc].assign(tempLoc);
        cout << "myarrayLoc[" << iiLoc << "] = " << myarrayLoc[iiLoc] << endl;
        iiLoc++;
    }

    int i, j;
    int scale = 5;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            image[i][j][2] = (unsigned char)((double)255); ///red
            image[i][j][1] = (unsigned char)((double)255); ///green
            image[i][j][0] = (unsigned char)(((double)255)); ///blue
        }
    }
    cout << endl << endl;
    int x1 = stoi(myarray2D[0][0]);
    int y1 = stoi(myarray2D[0][1]);
    int x2 = stoi(myarray2D[1][0]);
    int y2 = stoi(myarray2D[1][1]);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if ((j >= x1 && j <= x2) && i == ((((y2 - y1)/(x2 - x1)) * j) + y1 - ((y2 - y1)/(x2 - x1))*x1 )){
                image[i][j][2] = (unsigned char)((double)0); ///red
                image[i][j][1] = (unsigned char)((double)0); ///green
                image[i][j][0] = (unsigned char)(((double)0)); ///blue
            }
        }
    }

    x1 = stoi(myarray2D[1][0]);
    y1 = stoi(myarray2D[1][1]);
    x2 = stoi(myarray2D[2][0]);
    y2 = stoi(myarray2D[2][1]);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if ((j >= x1 && j <= x2) && i == ((((y2 - y1)/(x2 - x1)) * j) + y1 - ((y2 - y1)/(x2 - x1))*x1 )){
                image[i][j][2] = (unsigned char)((double)0); ///red
                image[i][j][1] = (unsigned char)((double)0); ///green
                image[i][j][0] = (unsigned char)(((double)0)); ///blue
            }
        }
    }

    x1 = stoi(myarray2D[0][0]);
    y1 = stoi(myarray2D[0][1]);
    x2 = stoi(myarray2D[3][0]);
    y2 = stoi(myarray2D[3][1]);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if ((j >= x1 && j <= x2) && i == ((((y2 - y1)/(x2 - x1)) * j) + y1 - ((y2 - y1)/(x2 - x1))*x1 )){
                image[i][j][2] = (unsigned char)((double)0); ///red
                image[i][j][1] = (unsigned char)((double)0); ///green
                image[i][j][0] = (unsigned char)(((double)0)); ///blue
            }
        }
    }

    x1 = stoi(myarray2D[3][0]);
    y1 = stoi(myarray2D[3][1]);
    x2 = stoi(myarray2D[2][0]);
    y2 = stoi(myarray2D[2][1]);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if ((j >= x1 && j <= x2) && i == ((((y2 - y1)/(x2 - x1)) * j) + y1 - ((y2 - y1)/(x2 - x1))*x1 )){
                image[i][j][2] = (unsigned char)((double)0); ///red
                image[i][j][1] = (unsigned char)((double)0); ///green
                image[i][j][0] = (unsigned char)(((double)0)); ///blue
            }
        }
    }

    generateBitmapImage((unsigned char *)image, height, width, imageFileName);

    return 0;
}



void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName){

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (width*bytesPerPixel) % 4) % 4;

    unsigned char* fileHeader = createBitmapFileHeader(height, width, paddingSize);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for(i=0; i<height; i++){
        fwrite(image+(i*width*bytesPerPixel), bytesPerPixel, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader(int height, int width, int paddingSize){
    int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel*width+paddingSize) * height;

    static unsigned char fileHeader[] = {
        0,0, /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize    );
    fileHeader[ 3] = (unsigned char)(fileSize>> 8);
    fileHeader[ 4] = (unsigned char)(fileSize>>16);
    fileHeader[ 5] = (unsigned char)(fileSize>>24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader(int height, int width){
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0, /// number of color planes
        0,0, /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(infoHeaderSize);
    infoHeader[ 4] = (unsigned char)(width    );
    infoHeader[ 5] = (unsigned char)(width>> 8);
    infoHeader[ 6] = (unsigned char)(width>>16);
    infoHeader[ 7] = (unsigned char)(width>>24);
    infoHeader[ 8] = (unsigned char)(height    );
    infoHeader[ 9] = (unsigned char)(height>> 8);
    infoHeader[10] = (unsigned char)(height>>16);
    infoHeader[11] = (unsigned char)(height>>24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel*8);

    return infoHeader;
}
