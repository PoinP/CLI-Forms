#ifndef LIST_BOX_H

#define LIST_BOX_H

#include "InputControl.h"
#include "ControlFactory.h"

class ListBox : public InputControl
{
public:
	ListBox(const Vector<String>& options, const int& selectedOption = 0);
	ListBox(const Vector<String>& options, const Point& pos, const int& selectedOption = 0);
	ListBox(const String* options, const int& optionsSize, const Point& pos, const int& selectedOption = 0);

	String state() const override;
	void modifyState(String command) override;
	void modifyStateUserInput() override;
	Vector<String> getParts() const override;
	String generateDescription() const override;

private:
	Vector<String> m_Options;
	int m_SelectedOption;

	Size calculateSize() const;
	String combineOptions() const;
	bool doesOptionExist(const String& option);
};

class ListBoxCreator : public ControlCreator
{
public:
	ListBoxCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !LIST_BOX_H