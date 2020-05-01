#ifndef INFORMATION_H
#define INFORMATION_H


class Information
{
private:
    double width;
    double height;
public:
    Information();
    double calcArea(double width, double height);
    double calcPerimeter(double width, double height);
    unsigned char* createBitmapFileHeader(int height, int width, int paddingSize);
};

#endif // INFORMATION_H
