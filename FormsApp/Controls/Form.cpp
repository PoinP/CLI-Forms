#include "Form.h"
#include "../Utilities/Utility.h"
#include "ControlFactory.h"

#include <stdexcept>

Form::Form()
{}

Form::Form(const String& name)
	: m_Name(name), m_Controls(Vector<Control*>())
{
}

Form::Form(const String& name, const Vector<Control*>& controls)
	: m_Name(name), m_Controls(controls)
{
}

Form::Form(const String& name, Control** controls, const int& controlsSize)
	: m_Name(name), m_Controls(Vector<Control*>())
{
	for (int i = 0; i < controlsSize; i++)
	{
		m_Controls.pushBack(controls[i]);
	}
}

Form::~Form()
{
	for (int i = 0; i < m_Controls.size(); i++)
	{
		delete m_Controls[i];
	}
}

Control* Form::operator[](const int& id)
{
	for (int i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i]->getId() == id)
			return m_Controls[i];
	}

	return nullptr;
}

const Control* Form::operator[](const int& id) const
{
	for (int i = 0; i < m_Controls.size(); i++)
	{
		if (m_Controls[i]->getId() == id)
			return m_Controls[i];
	}

	return nullptr;
}

void Form::printForm() const
{
	Size wSize = Utility::calculateWindowsSize(m_Controls);
	bool printed = false;

	const Size* size;
	const Point* pos;

	for (unsigned h = 0; h < wSize.height; h++)
	{
		for (unsigned w = 0; w < wSize.width; w++)
		{
			printed = false;
			for (int i = 0; i < m_Controls.size(); i++)
			{
				size = &m_Controls[i]->getSize();
				pos = &m_Controls[i]->getPosition();

				if (pos->y <= (int)h && (pos->y + (int)size->height - 1) >= (int)h)
				{
					if (pos->x == w)
					{
						int index = size->height - (pos->y + size->height) + h;
						String part = m_Controls[i]->getParts()[index];

						std::cout << part;

						w += size->width - 1;

						if (part.length() < (int)size->width)
						{
							for (int i = 0; i < ((int)size->width - part.length()); i++)
							{
								std::cout << " ";
							}
						}

						printed = true;
					}
				}
			}

			if (!printed)
				std::cout << " ";
		}
		std::cout << "\n";
	}
}

void Form::addControl(Control* control)
{
	if (Utility::isOverlapping(control, m_Controls))
		throw std::invalid_argument("Error adding control! This control is overlapping with another control!");

	m_Controls.pushBack(control);
}

// It intentionally doesn't check if a form is already loaded.
// This is so that you can load a couple of forms as long as they don't overlap
void Form::loadForm(std::istream& iStream)
{
	while (iStream && iStream.peek() != -1 && iStream.peek() != '~')
	{
		if (iStream.peek() == '\n')
		{
			iStream.get();
			continue;
		}

		Control* control = ControlFactory::getInstance().createControl(iStream);

		if (!control)
			throw std::invalid_argument("This control doesn't exist!");

		addControl(control);
	}
}

void Form::printAllControls() const
{
	for (int i = 0; i < m_Controls.size(); i++)
	{
		std::cout << m_Controls[i]->getId() << ". " << m_Controls[i]->generateDescription() << std::endl;
	}
}

void Form::enterInputFormData()
{
	Vector<InputControl*>* inputControls = getInputControls();

	for (int i = 0; i < inputControls->size(); i++)
	{
		std::cout << "Please enter details for control: " << "[" << (*inputControls)[i]->generateDescription() << "]\n";
		(*inputControls)[i]->modifyStateUserInput();
	}

	delete inputControls;
}

void Form::printInputControlsInfo() const
{
	Vector<InputControl*>* inputControls = getInputControls();

	for (int i = 0; i < inputControls->size(); i++)
	{
		std::cout << "[" << (*inputControls)[i]->getId() << ". " << (*inputControls)[i]->generateDescription() << "]" 
			<< " - State: " << (*inputControls)[i]->state() << "\n";
	}

	delete inputControls;
}

void Form::changeOuputControlText(const int& id, const String& text)
{
	Control* control = (*this)[id];

	if (!control)
		throw std::invalid_argument("This control doesn't exist!");

	OutputControl* outControl = dynamic_cast<OutputControl*>(control);

	if (!outControl)
		throw std::invalid_argument("The selected control is not an output control!");

	outControl->modifyText(text);
}

Vector<InputControl*>* Form::getInputControls() const
{
	Vector<InputControl*>* inputControls = new Vector<InputControl*>();
	InputControl* temp;

	for (int i = 0; i < m_Controls.size(); i++)
	{
		temp = dynamic_cast<InputControl*>(m_Controls[i]);

		if (temp)
			inputControls->pushBack(temp);
	}

	return inputControls->empty() ? nullptr : inputControls;
}
