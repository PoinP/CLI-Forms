#ifndef CONTROL_H

#define CONTROL_H

#include <iostream>
#include <fstream>

#include "../Utilities/String.h"
#include "../Utilities/Vector.h"

struct Point
{
	int x;
	int y;
};

struct Size
{
	unsigned width;
	unsigned height;
};

class Control
{
public:
	Control(const Point& pos, const String& text);
	virtual ~Control() = default;

	int getId() const;
	const Size& getSize() const;
	const Point& getPosition() const;
	const String& getText() const;

	virtual Vector<String> getParts() const = 0;
	virtual String generateDescription() const = 0;

protected:
	void setSize(const Size& size);
	void setPos(const Point& pos);
	void setText(const String& text);

	int generateId() const;

private:
	static Vector<int> m_Ids;

	int m_Id;
	Size m_Size;
	Point m_Pos;
	String m_Text;

	bool isIdUnique(const int& id) const;
	bool isPositive(const int& num) const;
};

std::istream& operator>> (std::istream& iStream, Size& size);
std::istream& operator>> (std::istream& iStream, Point& point);
std::ostream& operator<< (std::ostream& oStream, const Size& size);
std::ostream& operator<< (std::ostream& oStream, const Point& pos);

#endif // !CONTROL_H