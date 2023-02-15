#include "Utility.h"

String Utility::intToString(int num)
{
    String str;

    while (num != 0)
    {
        str.append((num % 10) + 48);
        num /= 10;
    }

    return str;
}

char* Utility::stringCopy(char* dest, const char* source)
{
    int i;
    for (i = 0; source[i] != '\0'; i++)
    {
        dest[i] = source[i];
    }

    dest[i] = source[i];

    return dest;
}

int Utility::stringToInt(const char* str)
{
    int num = 0;

    while (*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
            num = (num * 10) + (*str - '0');

        str++;
    }

    return num;
}

Point Utility::findMinPoint(Vector<Control*> controls)
{
    if (controls.empty())
        return Point{ 0, 0 };

    int minX = controls[0]->getPosition().x;
    int minY = controls[0]->getPosition().y;

    const Point* pos;

    for (int i = 1; i < controls.size(); i++)
    {
         pos = &controls[i]->getPosition();

        if (minX > pos->x)
            minX = pos->x;

        if (minY > pos->y)
            minY = pos->y;
    }

    return Point{ minX, minY };
}

Point Utility::findMaxPoint(Vector<Control*> controls)
{
    if (controls.empty())
        return Point{ 0, 0 };

    int maxX = controls[0]->getPosition().x + controls[0]->getSize().width;
    int maxY = controls[0]->getPosition().y + controls[0]->getSize().height;

    const Control* control;
    Point pos;

    for (int i = 1; i < controls.size(); i++)
    {
        control = controls[i];
        pos = control->getPosition();

        pos.x += control->getSize().width;
        pos.y += control->getSize().height;

        if (maxX < pos.x)
            maxX = pos.x;

        if (maxY < pos.y)
            maxY = pos.y;
    }

    return Point{ maxX, maxY };
}

Size Utility::calculateWindowsSize(Vector<Control*> controls)
{
    Point maxPoint = findMaxPoint(controls);

    Size size;
    size.width = maxPoint.x;
    size.height = maxPoint.y;

    return size;
}

bool Utility::isOverlapping(const Control* control, const Vector<Control*> controls)
{
    if (!control || controls.empty())
        return false;

    for (int i = 0; i < controls.size(); i++)
    {
        if (areOverlapping(controls[i], control))
            return true;
    }

    return false;
}

bool Utility::areOverlapping(const Control* c1, const Control* c2)
{
    Point c1Pos = c1->getPosition();
    Point c2Pos = c2->getPosition();

    Size c1Size = c1->getSize();
    Size c2Size = c2->getSize();

    Point c1Bot = { c1Pos.x + (int)c1Size.width - 1, c1Pos.y + (int)c1Size.height - 1 };
    Point c2Bot = { c2Pos.x + (int)c2Size.width - 1, c2Pos.y + (int)c2Size.height - 1 };

    // There most likely is a better way using a director vector but this is for homework, so it should do!

    if ((c2Pos.x >= c1Pos.x && c2Pos.x <= c1Bot.x &&
        c2Pos.y >= c1Pos.y && c2Pos.y <= c1Bot.y) ||
        (c2Bot.x >= c1Pos.x && c2Bot.x <= c1Bot.x &&
        c2Bot.y >= c1Pos.y && c2Bot.y <= c1Bot.y))
    {
        return true;
    }

    return false;
}

