#include "Control.h"

#include <stdexcept>

Vector<int> Control::m_Ids;

Control::Control(const Point& pos, const String& text)
    : m_Id(generateId()), m_Text(text)
{
    setPos(pos);
}

int Control::getId() const
{
    return m_Id;
}

const Size& Control::getSize() const
{
    return m_Size;
}

const Point& Control::getPosition() const
{
    return m_Pos;
}

const String& Control::getText() const
{
    return m_Text;
}

void Control::setSize(const Size& size)
{
    if (!isPositive(size.height))
        throw std::invalid_argument("Height can not be negative!");
    
    if (!isPositive(size.width))
        throw std::invalid_argument("Width can not be negative!");

    m_Size = size;
}

void Control::setPos(const Point& pos)
{
    if (!isPositive(pos.x))
        throw std::invalid_argument("Coord X can not be negative!");

    if (!isPositive(pos.y))
        throw std::invalid_argument("Coord Y can not be negative!");

    m_Pos = pos;
}

void Control::setText(const String& text)
{
    m_Text = text;
}

int Control::generateId() const
{
    int potentialId = m_Ids.size();

    while (!isIdUnique(++potentialId));

    m_Ids.pushBack(potentialId);

    return potentialId;
}

bool Control::isIdUnique(const int& id) const
{
    for (int i = 0; i < m_Ids.size(); i++)
    {
        if (m_Ids[i] == id)
            return false;
    }

    return true;
}

bool Control::isPositive(const int& num) const
{
    return num >= 0;
}

std::istream& operator>> (std::istream& iStream, Size& size)
{
    int width, height;
    char c;

    iStream >> c >> width;
    iStream >> c >> height;
    iStream >> c;

    if (width < 0 || height < 0)
        throw std::invalid_argument("Error reading from file! Size can't have negative values!");

    size = Size{ (unsigned)width, (unsigned)height };

    return iStream;
}

std::istream& operator>> (std::istream& iStream, Point& point)
{
    char c;

    iStream >> c >> point.x;
    iStream >> c >> point.y;
    iStream >> c;

    return iStream;
}

std::ostream& operator<< (std::ostream& oStream, const Size& size)
{
    oStream << "[" << size.width << ", " << size.height << "]";

    return oStream;
}

std::ostream& operator<< (std::ostream& oStream, const Point& pos)
{
    oStream << "[" << pos.x << ", " << pos.y << "]";

    return oStream;
}