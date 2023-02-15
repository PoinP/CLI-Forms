#ifndef PANEL_H

#define PANEL_H

#include "InputControl.h"
#include "OutputControl.h"
#include "ControlFactory.h"

class Panel : public InputControl,
			  public OutputControl
{
public:
	Panel(const String& text);
	Panel(const String& text, const Point& pos);

	void addControl(Control* control);

	Vector<String> getParts() const override;
	String generateDescription() const override;

	String state() const override;
	String allControls() const;
	void modifyState(String command) override;
	void modifyStateUserInput() override;
	void modifyText(String text) override;
private:
	Vector<Control*> m_Controls;

	Vector<String> splitCommand(const String& command) const;
	Control* findControl(const int& id);
	Size calculateSize() const;
};

class PanelCreator : public ControlCreator
{
public:
	PanelCreator();

	Control* createControl(std::istream& iStream) const override;
};

#endif // !PANEL_H