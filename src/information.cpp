#include "information.h"

Information::Information()
{
    width = 0;
    height = 0;
}

// Calculates Area of square shaped county
double Information::calcArea(double height, double width){
    if (width < 0 || height < 0)
    {
        throw "Error: Length or height is negative.\n";
    }
    else
        return height * width;
}// Calculates Area of square shaped county
double Information::calcArea(){
    if (width < 0 || height < 0)
    {
        throw "Error: Length or height is negative.\n";
    }
    else
        return height * width;
}
// Calculates Perimeter of square shaped county
double Information::calcPerimeter(double height, double width){
    if (width < 0 || height < 0)
    {
        throw "Error: Length or height is negative.\n";
    }
    else
        return 2 * height + 2 * width;
}
