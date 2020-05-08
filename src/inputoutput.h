#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

//#include <iostream>
//#include <iterator>
//#include <list>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "database.h"

using namespace std;

class InputOutput
{
public:
    InputOutput();
    list<int> getMaps();
    list<int> getStats();
    void writeInfo();
};

#endif // INPUTOUTPUT_H
