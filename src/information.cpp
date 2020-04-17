#include "information.h"

Information::Information()
{
    width = 0;
    height = 0;
}

// Calculates Area of square shaped county
double Information::calcArea(double width, double height){
    return width * height;
}
// Calculates Perimeter of square shaped county
double Information::calcPerimeter(double width, double height){
    return 2 * width + 2 * height;
}
