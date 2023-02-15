#ifndef FORM_H

#define FORM_H

#include "Control.h"
#include "InputControl.h"
#include "OutputControl.h"

#include <fstream>

class Form
{
public:
	Form();
	Form(const String& name);
	Form(const String& name, const Vector<Control*>& controls);
	Form(const String& name, Control** controls, const int& controlsSize);
	~Form();

	Control* operator[](const int& id);
	const Control* operator[](const int& id) const;

	void printForm() const;
	void addControl(Control* control);

	void loadForm(std::istream& iStream);

	void printAllControls() const;
	void enterInputFormData();
	void printInputControlsInfo() const;
	void changeOuputControlText(const int& id, const String& text);

private:
	Form(const Form&) = delete;
	Form& operator=(const Form&) = delete;

private:
	String m_Name;
	Vector<Control*> m_Controls;

	Vector<InputControl*>* getInputControls() const;
};

#endif // !FORM_H