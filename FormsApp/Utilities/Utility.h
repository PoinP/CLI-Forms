#ifndef UTILITY_H

#define UTILITY_H

#include "../Controls/Control.h"
#include "String.h"
#include "Vector.h"

namespace Utility
{
    String intToString(int num);
    char* stringCopy(char* dest, const char* source);
    int stringToInt(const char* str);

    Point findMinPoint(Vector<Control*> controls);
    Point findMaxPoint(Vector<Control*> controls);
    Size calculateWindowsSize(Vector<Control*> controls);

    bool isOverlapping(const Control* control, const Vector<Control*> controls);
    bool areOverlapping(const Control* c1, const Control* c2);
}

#endif // !UTILITY_H