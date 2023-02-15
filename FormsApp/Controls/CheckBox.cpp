#include "CheckBox.h"

#include <stdexcept>

const char* CheckBox::m_States[2] = { "Unchecked", "Checked" };

CheckBox::CheckBox(const String& text, bool isChecked)
	: Control(Point { 0, 0 }, text), m_IsChecked(isChecked)
{
	setSize(calculateSize());
}

CheckBox::CheckBox(const String& text, const Point& pos, bool isChecked)
	: Control(pos, text), m_IsChecked(isChecked)
{
	setSize(calculateSize());
}

void CheckBox::setPosition(const Point& pos)
{
	Control::setPos(pos);
}

Vector<String> CheckBox::getParts() const
{
	Vector<String> parts;
	String cb;

	if (m_IsChecked)
		cb += "[X] ";
	else
		cb += "[ ] ";

	cb += getText();
	parts.pushBack(cb);

	return parts;
}

String CheckBox::state() const
{
	return m_States[m_IsChecked];
}

void CheckBox::modifyState(String command)
{
	m_IsChecked = !(m_IsChecked);
}

void CheckBox::modifyStateUserInput()
{
	String userInput;

	std::cout << "Do you want to change the checkbox's state(y/n): ";
	std::cin >> userInput;

	if (userInput == 'n' || userInput == 'N' || userInput == "no")
		return;

	if (userInput == 'y' || userInput == 'Y' || userInput == "yes")
	{
		modifyState();
		return;
	}

	std::cout << "Invalid input!" << std::endl;
}

String CheckBox::generateDescription() const
{
	return "CheckBox: " + getText();
}

Size CheckBox::calculateSize() const
{
	Size size;
	size.height = 1;
	size.width = getText().length() + 4;

	return size;
}



CheckBoxCreator::CheckBoxCreator()
	: ControlCreator("checkbox")
{
}

Control* CheckBoxCreator::createControl(std::istream& iStream) const
{
	String text;
	Point pos;
	bool isChecked;

	getLine(iStream, text, ',');
	iStream >> pos;
	iStream.get();
	iStream >> isChecked;

	if (!iStream)
		throw std::invalid_argument("Checkbox was corrupted!");

	return new CheckBox(text, pos, isChecked);
}

CheckBoxCreator __;
