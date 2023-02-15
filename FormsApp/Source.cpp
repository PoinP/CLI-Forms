#include <iostream>
#include <fstream>

#include "Controls/Form.h"

void loadFromFile(Form& form, const char* filePath);
void loadFromConsole(Form& form);
void printMenu();
void getControlDescMenu(Form& form);
void changeOutupControlMenu(Form& form);
void enterDetailsInputControl(Form& form);

int main()
{
	Form myForm("Homework 2");

	try
	{
		// Sample data for input from console is in the funtion definition
		// loadFromConsole(myForm);


		// loadFromFile(myForm, "Forms\\Default.txt");  // You can also try this one :)
		loadFromFile(myForm, "Forms\\Homework.txt");
	}
	catch (const std::exception& ex)
	{
		std::cout << "There was an error loading the from: '" << ex.what() << "' Please fix the format and then try to load the from again!" << std::endl;
		return -1;
	}

	std::cout << "--------------------------------------\n";
	myForm.printForm();
	std::cout << "--------------------------------------\n";

	int userInput;

	do
	{
		std::cout << "\n\n";
		printMenu();

		std::cin >> userInput;
		std::cout << '\n';

		if (!std::cin)
		{
			userInput = -1;
			std::cin.clear();
			std::cin.ignore(1024, '\n');
		}

		try
		{
			switch (userInput)
			{
			case 1:
				myForm.printAllControls();
				break;
			case 2:
				myForm.printInputControlsInfo();
				break;
			case 3:
				getControlDescMenu(myForm);
				break;
			case 4:
				std::cin.get();
				myForm.enterInputFormData();
				break;
			case 5:
				std::cin.get();
				// A user shouldn't be able to change an output control's data!
				// It is allowed here only for the sake of showing that a function exists
				// that allows changing an output control's text
				changeOutupControlMenu(myForm);
				break;
			case 6:
				enterDetailsInputControl(myForm);
				break;
			case 7:
				myForm.printForm();
				break;
			case 9:
				break;
			default:
				std::cout << "Unknown command! Please try again!" << std::endl;
				break;
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << " Please try again!" << std::endl;
		}
	} while (userInput != 9);

	std::cout << "Goodbye!" << std::endl;
}

void loadFromFile(Form& form, const char* filePath)
{
	std::ifstream iStream(filePath);

	if (!iStream)
	{
		std::cout << "Invalid input file!" << std::endl;
		return;
	}

	form.loadForm(iStream);

	iStream.close();
}

void loadFromConsole(Form& form)
{
	// -------------Sample Data-------------
	// label,Input,(0,0) 
	// textbox,Test,(10,1),(8,0) 
	// radio,{[Yes,0],[No,1],[Maybe,0]},(0,1)

	std::cout << "Please enter the controls one line at a time! Enter '~' to stop entering controls!\n"
		<< "If you enter a loop you can try using ',' and then '~' to stop entering!" << std::endl;
	form.loadForm(std::cin);
}

void printMenu()
{
	std::cout << "What would you like to do?\n"
		<< "1. Print all controls\n"
		<< "2. Print all input controls\n"
		<< "3. Get description of certain control\n"
		<< "4. Enter input info for all input controls\n"
		<< "5. Change the text of an output control\n"
		<< "6. Input a ceratin control\n"
		<< "7. Print form\n"
		<< "9. Exit" << std::endl;
}

void enterDetailsInputControl(Form& form)
{
	int id;

	std::cout << "Please enter a control's ID: ";
	std::cin >> id;

	if (!std::cin)
		throw std::invalid_argument("Input error!");

	std::cin.ignore(1024, '\n');

	if (!form[id])
		throw std::invalid_argument("This control doesn't exist or it's part of a panel!");

	InputControl* control = dynamic_cast<InputControl*>(form[id]);

	if (!control)
		throw std::invalid_argument("Selected control isn't an input control!");

	control->modifyStateUserInput();
}

void changeOutupControlMenu(Form& form)
{
	int id;
	String text;

	std::cout << "Please enter a control's ID: ";
	std::cin >> id;

	if (!std::cin)
		throw std::invalid_argument("Input error!");

	std::cin.ignore(1024, '\n');

	std::cout << "Please enter the text: ";
	getLine(std::cin, text);

	try
	{
		form.changeOuputControlText(id, text);
		std::cout << "Changed a control's text to " << text << "!" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

void getControlDescMenu(Form& form)
{
	int id;

	std::cout << "Please enter a control's ID: ";
	std::cin >> id;

	if (!std::cin)
		throw std::invalid_argument("Input error!");

	std::cin.ignore(1024, '\n');

	// We use the operator[] for indexing here
	if (!form[id])
		throw std::invalid_argument("This control doesn't exist or it's part of a panel!");

	std::cout << form[id]->generateDescription() << std::endl;
}