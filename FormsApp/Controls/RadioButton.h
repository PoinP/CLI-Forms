#ifndef RADIO_BUTTON_H

#define RADIO_BUTTON_H

#include "InputControl.h"
#include "ControlFactory.h"

struct Option
{
	String text;
	bool isChecked = false;
};

class RadioButton : public InputControl
{
public:
	RadioButton(Vector<Option> options);
	RadioButton(Vector<Option> options, const Point& pos);
	RadioButton(const Option* options, const int& optionsSize, const Point& pos);

	Vector<String> getParts() const override;
	String state() const override;
	void modifyState(String command) override;
	void modifyStateUserInput() override;
	String generateDescription() const override;

private:
	Vector<Option> m_Options;

	Size calculateSize() const;
	bool doesOptionExist(const String& option);
	int getLongestOption() const;
};

class RadioCreator : public ControlCreator
{
public:
	RadioCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !RADIO_BUTTON_H