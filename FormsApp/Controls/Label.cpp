#include "Label.h"

#include <stdexcept>

Label::Label(const String& text)
    : Control(Point{ 0, 0 }, text)
{
    setSize(calculateSize());
}

Label::Label(const String& text, const Point& pos)
    : Control(pos, text)
{
    setSize(calculateSize());
}

Vector<String> Label::getParts() const
{
    Vector<String> parts;
    parts.pushBack(getText());

    return parts;
}

void Label::modifyText(String text)
{
    setText(text);
    setSize(calculateSize());
}

String Label::generateDescription() const
{
    return "Label: " + getText();
}

void Label::setPosition(const Point& pos)
{
    Control::setPos(pos);
}

Size Label::calculateSize() const
{
    Size size;
    size.height = 1;
    size.width = getText().length();

    return size;
}

LabelCreator::LabelCreator()
    : ControlCreator("label")
{
}

Control* LabelCreator::createControl(std::istream& iStream) const
{
    String text;
    Point pos;

    getLine(iStream, text, ',');
    iStream >> pos;

    if (!iStream)
        throw std::invalid_argument("Label was corrupted!");

    return new Label(text, pos);
}

LabelCreator __;