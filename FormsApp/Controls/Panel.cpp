#include "Panel.h"
#include "../Utilities/Utility.h"

#include <stdexcept>

Panel::Panel(const String& text)
    : Control(Point{ 0, 0 }, text), m_Controls(Vector<Control*>())
{
    setSize(calculateSize());
}

Panel::Panel(const String& text, const Point& pos)
    : Control(pos, text), m_Controls(Vector<Control*>())
{
    setSize(calculateSize());
}

void Panel::addControl(Control* control)
{
    if (Utility::isOverlapping(control, m_Controls))
        throw std::invalid_argument("This control overlaps another one!");

    m_Controls.pushBack(control);
    setSize(calculateSize());
}

Vector<String> Panel::getParts() const
{
    Vector<String> parts;
    String line;

    Size wSize = calculateSize();

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
                        line += part;

                        w += size->width - 1;

                        if (part.length() < (int)size->width)
                        {
                            for (int i = 0; i < ((int)size->width - part.length()); i++)
                            {
                                line += " ";
                            }
                        }

                        printed = true;
                    }
                }
            }

            if (!printed)
                line += " ";
        }

        parts.pushBack(line);
        line.clear();
    }

    return parts;
}

String Panel::generateDescription() const
{
    return "Panel: " + getText() + " - <" + allControls() + ">";
}

String Panel::state() const
{
    String state;
    InputControl* control = nullptr;

    for (int i = 0; i < m_Controls.size(); i++)
    {
        control = dynamic_cast<InputControl*>(m_Controls[i]);

        if(control)
            state += Utility::intToString(control->getId()) + ". " + control->state() + " | ";
    }

    return state;
}

String Panel::allControls() const
{
    String allControls;

    for (int i = 0; i < m_Controls.size(); i++)
    {
        allControls += Utility::intToString(m_Controls[i]->getId()) + ". " + m_Controls[i]->generateDescription();

        if (i + 1 < m_Controls.size())
            allControls += " | ";
    }

    return allControls;
}

void Panel::modifyState(String command)
{
    String userInput;
    std::cout << "Please enter the ID of the control you want to modify: ";
    std::cin >> userInput;

    Control* foundControl = findControl(Utility::stringToInt(userInput.c_str()));

    if (!foundControl)
        throw std::invalid_argument("No such control exists!");

    InputControl* inputControl = dynamic_cast<InputControl*>(foundControl);

    if (!inputControl)
        throw std::invalid_argument("The selected control isn't an input one!");

    inputControl->modifyStateUserInput();
}

void Panel::modifyStateUserInput()
{
    for (int i = 0; i < m_Controls.size(); i++)
    {
        InputControl* inputControl = dynamic_cast<InputControl*>(m_Controls[i]);

        if (!inputControl)
            continue;

        std::cout << inputControl->generateDescription() << ": \n";
        inputControl->modifyStateUserInput();
    }
}

void Panel::modifyText(String text)
{
    setText(text);
}

Vector<String> Panel::splitCommand(const String& command) const
{
    String cmd;
    Vector<String> commands;
    const char* charCmd = command.c_str();

    while (*charCmd != '\0')
    {
        if (*charCmd == ' ' || *(charCmd + 1) == '\0')
        {
            commands.pushBack(cmd);
            cmd.clear();
            charCmd++;
            continue;
        }

        cmd.pushBack(*charCmd);
        charCmd++;
    }

    if (commands.size() < 2)
        throw std::invalid_argument("Inavlid command! Not enough arguments");

    return commands;
}

Control* Panel::findControl(const int& id)
{
    for (int i = 0; i < m_Controls.size(); i++)
    {
        if (m_Controls[i]->getId() == id)
            return m_Controls[i];
    }

    return nullptr;
}

Size Panel::calculateSize() const
{
    Size size = Utility::calculateWindowsSize(m_Controls);

    return size;
}

PanelCreator::PanelCreator()
    : ControlCreator("panel")
{
}

Control* PanelCreator::createControl(std::istream& iStream) const
{
    String name;
    Point pos;
    Vector<Control*> controls;
    Control* control;

    getLine(iStream, name, ',');
    iStream >> pos;
    iStream.get();

    char c;
    c = iStream.get();
    
    if (c == '{')
    {
        String text;

        do
        {
            if (c == ']')
            {
                controls.pushBack(control);
                text.clear();
            }

            c = iStream.get();

            if (c == '[')
            {
                control = ControlFactory::getInstance().createControl(iStream);
                c = iStream.get();
            }
        } while (c != '}');
    }

    iStream.ignore(1024, '\n');

    Panel* panel = new Panel(name, pos);

    for (int i = 0; i < controls.size(); i++)
    {
        panel->addControl(controls[i]);
    }

    if (!iStream)
        throw std::invalid_argument("Panel was corrupted!");

    return panel;
}

PanelCreator __;