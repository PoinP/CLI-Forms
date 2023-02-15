#ifndef TEXT_BOX_H

#define TEXT_BOX_H

#include "InputControl.h"
#include "OutputControl.h"
#include "ControlFactory.h"

class TextBox : public InputControl,
				public OutputControl
{
public:
	TextBox(const Size& size, const String& text = "");
	TextBox(const Size& size, const Point& pos, const String& text = "");

	Vector<String> getParts() const override;
	String state() const override;
	void modifyState(String command) override;
	void modifyStateUserInput() override;
	void modifyText(String text) override;
	String generateDescription() const override;

private:
	int calculateRows(const String& text) const;
	String cropTextToFit(const String& text) const;

	String getFirstWord(char*& cStr) const;

	String cropString(String& str, const int& num) const;
};

class TextBoxCreator : public ControlCreator
{
public:
	TextBoxCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !TEXT_BOX_H