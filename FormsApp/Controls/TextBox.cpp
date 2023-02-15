#include "TextBox.h"
#include "../Utilities/Utility.h"

#include <stdexcept>

TextBox::TextBox(const Size& size, const String& text)
    : Control(Point{ 0, 0 }, text)
{
    setSize(size);
}

TextBox::TextBox(const Size& size, const Point& pos, const String& text)
    : Control(pos, text)
{
    setSize(size);
}

Vector<String> TextBox::getParts() const
{
    String croppedText = cropTextToFit(getText());

    String line;
    Vector<String> parts;

    int strIndex = 0;
    int height = getSize().height;
    int width = getSize().width;

    bool wait;

    for (int i = 0; i < height; i++)
    {
        wait = false;

        line += "[";

        for (int j = 0; j < width - 2; j++)
        {
            if (croppedText[strIndex] == '\0')
                wait = true;

            if (croppedText[strIndex] == '\n')
            {
                strIndex++;
                wait = true;
            }

            if (!wait)
                line += croppedText[strIndex++];

            if (wait)
                line += " ";

            if (j + 1 == (width - 2) && croppedText[strIndex] == '\n')
            {
                strIndex++;
            }
        }

        line += "]";

        parts.pushBack(line);
        line.clear();
    }

    return parts;
}

String TextBox::state() const
{
    String text = cropTextToFit(getText());
    String formattedText;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ' && text[i - 1] == ' ')
            continue;

        if (text[i] == '\n' && text[i - 1] == ' ')
            continue;

        if (text[i] == '\n')
        {
            formattedText.pushBack(' ');
            continue;
        }

        formattedText.pushBack(text[i]);
    }

    return formattedText;
}

void TextBox::modifyState(String command)
{
    setText(command);
}

void TextBox::modifyStateUserInput()
{
    String userInput;

    std::cout << "What text do you want to put: ";
    getLine(std::cin, userInput);

    if (userInput.empty())
        return;

    modifyState(userInput);
}

void TextBox::modifyText(String text)
{
    setText(text);
}

String TextBox::generateDescription() const
{
    return "TextBox: " + getText();
}

int TextBox::calculateRows(const String& text) const
{
    int i = 0;
    int rows = 0;
    
    while (text[i] != '\0')
    {
        if (text[i++] == '\n')
            rows++;
    }

    return rows;
}

String TextBox::cropTextToFit(const String& text) const
{
    char* cStr = Utility::stringCopy(new char[text.length() + 1], text.c_str());
    char* cStrStart = cStr;

    const int maxWidth = getSize().width - 2;

    if (maxWidth <= 0)
    {
        return String();
    }

    int currRow = 1;
    int width = maxWidth;
    int height = getSize().height;

    String croppedText;
    String word;
    bool skip = false;;

    while (currRow <= height)
    {
        if (!skip)
            word = getFirstWord(cStr);
        else
            skip = false;

        if (word.length() + 1 < width)
        {
            croppedText += word + " ";
            width -= (word.length() + 1);
        }
        else if (word.length() == width)
        {
            croppedText += word + '\n';
            width -= word.length();
        }
        else
        {
            if (width == maxWidth)
            {
                if (word.length() == maxWidth)
                {
                    croppedText += word + '\n';
                    width -= word.length();
                }
                else if(word.length() > width)
                {
                    croppedText += cropString(word, width) + '\n';
                    width = 0;
                    skip = true;
                }
                else
                {
                    croppedText += word + " ";
                    width -= word.length();
                }
            }
            else
            {
                width = getSize().width - 2;
                currRow++;

                if (currRow <= height)
                {
                    croppedText += '\n' + word + " ";
                    width -= word.length() + 1;
                }
            }
        }

        if (width == 0)
        {
            width = getSize().width - 2;
            currRow++;
        }
    }

    cStr = cStrStart;
    delete[] cStr;

    return croppedText;
}

String TextBox::getFirstWord(char*& cStr) const
{
    int length = 0;
    String word = "";

    while (*cStr != ' ' && *cStr != '\0')
    {
        length++;
        word += *cStr;
        cStr++;
    }

    if (*cStr != '\0')
        cStr++;

    return word;
}

String TextBox::cropString(String& str, const int& num) const
{
    String firstHalf;
    String secondHalf;

    if (num < 0)
        throw std::invalid_argument("Num can not be lower than zero!");
    if (num == str.length())
        return str;
    if (num > str.length())
        throw std::out_of_range("Num must be lower than the string's length!");

    int i;
    for (i = 0; i < num; i++)
    {
        firstHalf.pushBack(str[i]);
    }

    for (; i < str.size(); i++)
    {
        secondHalf.pushBack(str[i]);
    }

    str = secondHalf;
    return firstHalf;
}



TextBoxCreator::TextBoxCreator()
    : ControlCreator("textbox")
{
}

Control* TextBoxCreator::createControl(std::istream& iStream) const
{
    String text;
    Size size;
    Point pos;

    getLine(iStream, text, ',');
    iStream >> size;
    iStream.get();
    iStream >> pos;

    if (!iStream)
        throw std::invalid_argument("Textbox was corrupted!");

    return new TextBox(size, pos, text);
}

TextBoxCreator __;
