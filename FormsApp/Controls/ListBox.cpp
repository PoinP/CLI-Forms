#include "ListBox.h"

#include <stdexcept>

ListBox::ListBox(const Vector<String>& options, const int& selectedOption)
    : Control(Point{ 0,0 }, ""), m_Options(options), m_SelectedOption(selectedOption)
{
    if (selectedOption > m_Options.size())
        throw std::invalid_argument("Invalid selected option!");

    setText(combineOptions());
    setSize(calculateSize());
}

ListBox::ListBox(const Vector<String>& options, const Point& pos, const int& selectedOption)
    : Control(pos, ""), m_Options(options), m_SelectedOption(selectedOption)
{
    if (selectedOption > m_Options.size())
        throw std::invalid_argument("Invalid selected option!");

    setText(combineOptions());
    setSize(calculateSize());
}

ListBox::ListBox(const String* options, const int& optionsSize, const Point& pos, const int& selectedOption)
    : Control(pos, ""), m_SelectedOption(selectedOption)
{
    if (selectedOption > optionsSize)
        throw std::invalid_argument("Invalid selected option!");

    for (int i = 0; i < optionsSize; i++)
    {
        m_Options.pushBack(options[i]);
    }

    setText(combineOptions());
    setSize(calculateSize());
}

String ListBox::state() const
{
    if (m_Options.empty())
        return "";

    return m_Options[m_SelectedOption];
}

void ListBox::modifyState(String command)
{
    if (!doesOptionExist(command))
        throw std::invalid_argument("This option doesn't exist!");

    for (int i = 0; i < m_Options.size(); i++)
    {
        if (command == m_Options[i])
            m_SelectedOption = i;
    }

    setSize(calculateSize());
}

void ListBox::modifyStateUserInput()
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

Vector<String> ListBox::getParts() const
{
    Vector<String> options;

    if (m_Options.empty())
        options.pushBack("| |");
    else
        options.pushBack("|" + m_Options[m_SelectedOption] + "|");

    return options;
}

String ListBox::generateDescription() const
{
    String desc = "ListBox: ";

    for (int i = 0; i < m_Options.size(); i++)
    {
        desc += m_Options[i];

        if (i + 1 < m_Options.size())
            desc += " | ";
    }

    return desc;
}

Size ListBox::calculateSize() const
{
    Size size;
    size.height = 1;

    if (m_Options.empty())
        size.width = 3;
    else
        size.width = m_Options[m_SelectedOption].size() + 2;

    return size;
}

String ListBox::combineOptions() const
{
    String options;

    for (int i = 0; i < m_Options.size(); i++)
    {
        options += m_Options[i];
       
        if (i + 1 < m_Options.size())
            options += " ";
    }

    return options;
}

bool ListBox::doesOptionExist(const String& option)
{
    for (int i = 0; i < m_Options.size(); i++)
    {
        if (m_Options[i] == option)
            return true;
    }

    return false;
}


ListBoxCreator::ListBoxCreator()
    : ControlCreator("listbox")
{
}

Control* ListBoxCreator::createControl(std::istream& iStream) const
{
    // listbox,{text,text,text},1,pos

    Vector<String> options;
    int currentOption;
    Point pos;

    char c;
    c = iStream.get();
    if (c == '{')
    {
        String option;

        do
        {
            getLine(iStream, option, ',');

            if (option.back() == '}')
                option.back() = '\0';

            options.pushBack(option.c_str());
        } while (option.back() != '\0');

        iStream >> currentOption;
        iStream.get();
        iStream >> pos;
    }

    if (!iStream)
        throw std::invalid_argument("Listbox was corrupted!");

    return new ListBox(options, pos, currentOption);
}

ListBoxCreator __;