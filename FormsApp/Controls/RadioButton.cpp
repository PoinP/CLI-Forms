#include "RadioButton.h"

#include <stdexcept>

RadioButton::RadioButton(Vector<Option> options)
    : Control(Point{ 0, 0 }, String()), m_Options(options)
{
    setSize(calculateSize());
}

RadioButton::RadioButton(Vector<Option> options, const Point& pos)
    : Control(pos, String()), m_Options(options)
{
    setSize(calculateSize());
}

RadioButton::RadioButton(const Option* options, const int& optionsSize, const Point& pos)
    : Control(pos, String()), m_Options(Vector<Option>())
{
    for (int i = 0; i < optionsSize; i++)
    {
        m_Options.pushBack(options[i]);
    }

    setSize(calculateSize());
}

Vector<String> RadioButton::getParts() const
{
    Vector<String> parts;
    String option;

    for (int i = 0; i < m_Options.size(); i++)
    {
        if (m_Options[i].isChecked)
            option += "[X] ";
        else
            option += "[ ] ";

        option += m_Options[i].text;

        parts.pushBack(option);
        option.clear();
    }

    return parts;
}

String RadioButton::state() const
{
    for (int i = 0; i < m_Options.size(); i++)
    {
        if (m_Options[i].isChecked)
            return m_Options[i].text;
    }

    return "No option selected!";
}

void RadioButton::modifyState(String command)
{
    if (!doesOptionExist(command))
        throw std::invalid_argument("This option doesn't exist!");

    for (int i = 0; i < m_Options.size(); i++)
    {
        if (command == m_Options[i].text)
            m_Options[i].isChecked = true;
        else
            m_Options[i].isChecked = false;
    }
}

void RadioButton::modifyStateUserInput()
{
    String userInput;

    std::cout << "Please enter the option's name you want to select(case sensitive): ";
    getLine(std::cin, userInput);

    try
    {
        modifyState(userInput);
        std::cout << "Changed selection to " << userInput << "!" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

String RadioButton::generateDescription() const
{
    String options = "Radio: [ ";
    for (int i = 0; i < m_Options.size(); i++)
    {
        options += m_Options[i].text;

        if (i + 1 < m_Options.size())
            options += " | ";
    }

    options += " ]";

    return options;
}

Size RadioButton::calculateSize() const
{
    Size size;
    size.height = m_Options.size();
    size.width = getLongestOption() + 4;

    return size;
}

bool RadioButton::doesOptionExist(const String& option)
{
    for (int i = 0; i < m_Options.size(); i++)
    {
        if (m_Options[i].text == option)
            return true;
    }

    return false;
}

int RadioButton::getLongestOption() const
{
    int longest = 0;
    for (int i = 0; i < m_Options.size(); i++)
    {
        int optionLength = m_Options[i].text.length();
        if (longest < optionLength)
            longest = optionLength;
    }

    return longest;
}

RadioCreator::RadioCreator()
    : ControlCreator("radio")
{
}

Control* RadioCreator::createControl(std::istream& iStream) const
{
    Vector<Option> options;
    Point pos;

    char c;
    c = iStream.get();
    if (c == '{')
    {
        String text;
        bool checked = false;

        do
        {
            if (c == ']')
            {
                options.pushBack(Option{ text, checked });
                text.clear();
            }

            c = iStream.get();

            if (c == '[')
            {
                getLine(iStream, text, ',');
                iStream >> checked;

                c = iStream.get();
            }
        } while (c != '}');
    }

    iStream.get();
    
    iStream >> pos;

    if (!iStream)
        throw std::invalid_argument("Radio Button was corrupted!");

    return new RadioButton(options, pos);
}

RadioCreator __;