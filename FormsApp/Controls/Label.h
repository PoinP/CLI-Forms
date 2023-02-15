#ifndef LABEL_H

#define LABEL_H

#include "OutputControl.h"
#include "ControlFactory.h"

#include <iostream>

class Label : public OutputControl
{
public:
	Label(const String& text);
	Label(const String& text, const Point& pos);

	void setPosition(const Point& pos);

	Vector<String> getParts() const override;
	void modifyText(String text) override;
	String generateDescription() const override;

private:
	Size calculateSize() const;
};

class LabelCreator : public ControlCreator
{
public:
	LabelCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !LABEL_H