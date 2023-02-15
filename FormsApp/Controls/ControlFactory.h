#ifndef CONTROL_FACTORY_H

#define CONTROL_FACTORY_H

#include "Control.h"

class ControlCreator;

class ControlFactory
{
public:
	static ControlFactory& getInstance();

	void registerCreator(ControlCreator* creator);
	Control* createControl(std::istream& iStream) const;
private:
	Vector<ControlCreator*> m_Creators{};

	ControlCreator* findCreator(String type) const;

	ControlFactory() {};
	ControlFactory(const ControlFactory&) = delete;
	ControlFactory& operator=(const ControlFactory&) = delete;
};

class ControlCreator
{
public:
	ControlCreator(const String& type);

	String getType() const;
	virtual Control* createControl(std::istream& iStream) const = 0;

private:
	String m_Type;
};

#endif // !CONTROL_FACTORY_H