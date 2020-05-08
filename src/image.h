#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;



const int fileHeaderSize = 14;
const int infoHeaderSize = 40;


const int bytesPerPixel = 3; /// red, green, blue

class Image
{
public:
    Image();
    // See Stackoverflow Article: Writing BMP image in pure c/c++ without other libraries
    //void saveImage(string (&myarray2D)[99][2], int n);
    void saveImage(list<list<list<int> > > county_list);
    void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName);
    unsigned char* createBitmapInfoHeader(int height, int width);
    unsigned char* createBitmapFileHeader(int height, int width, int paddingSize);
    unsigned char* LoadBitmapFile(char *filename, char *bitmapInfoHeader);
};

#endif // IMAGE_H
