#ifndef CHECK_BOX_H

#define CHECK_BOX_H

#include "InputControl.h"
#include "ControlFactory.h"

class CheckBox : public InputControl
{
public:
	CheckBox(const String& text, bool isChecked = false);
	CheckBox(const String& text, const Point& pos, bool isChecked = false);

	void setPosition(const Point& pos);

	Vector<String> getParts() const override;
	String state() const override;
	void modifyState(String command = "") override;
	void modifyStateUserInput() override;
	String generateDescription() const override;

private:
	static const char* m_States[2];
	bool m_IsChecked;

	Size calculateSize() const;
};

class CheckBoxCreator : public ControlCreator
{
public:
	CheckBoxCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !CHECK_BOX_H