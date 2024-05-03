/*********************************************
* 
* @file menu.h
* 
* @brief Menu class and function declarations.
* 
*********************************************/


#pragma once

#include "main.h"
#include "account.h"
#include "manager.h"

using namespace std;

/*********************************************
* 
* @class Menu
* 
* @brief: Menu class used to display options to users.
* 
*********************************************/
class Menu 
{
protected:
	Account account;
	string title;
	string userID;
	int input;
	bool flag;

public:
	Menu(); //constructor
	~Menu() {}; //destructor
	bool mainMenu();
	bool accountMenu(string);

}; //menu class


/*********************************************
* 
* @brief Menu constructor.
* 
* @param flag: bool, to be used in loops, default to false.
* @param input: integer, user's input/menu selection, default to 0.
* @param title: string, title of the current displayed menu, default to empty.
*
*********************************************/
Menu::Menu()
{
	flag = false;
	input = 0;
	title = "";
}//menu constructor


/*******************************************
*
* @brief Function that handles the main menu display upon initial run of program. 
* 
* @return flag: bool, true if program is running (options 1 or 2)
* @return flag: bool, false if program has been exited (options 3)
*
**************************************************/
bool Menu::mainMenu()
{
	title = "\t\t MAIN MENU";
	input = 0;
	flag = false;

	const string options[] = { "Log in", "Create Account", "Exit" };
	const int numOptions = (sizeof(options) / sizeof(options[0]));

	//create new account obj for user account manipulation
	Account* account = new Account();

	//print menu and get what user wants to do
	while (!flag) 
	{

		cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

		//print menu options
		for (int i = 0; i < numOptions; i++)
		{
			int optNum = i + 1;
			cout << optNum << ". " << options[i] << endl;
		}

		cout << "Pick an option from the menu: ";
		cin >> input;

		switch (input)
		{
		case 1: //login
			flag = true;
			return flag;
		case 2: //create account
			flag = account->createAccount(); //true if account creation successful, false if account creation failure
			return flag;
		case 3: //exit
			flag = false;
			return flag;
		default: //invalid option
			flag = false;
			cout << "\n\nInvalid option entered, try again." << endl << endl;
			break;
		}//switch
	}//while

} //startMenu function


/*******************************************
*
* @brief Function that handles the user account menu after successful login. 
*
* @param uid: string, a hashed userID.
* 
* @return flag: bool, indicates user login status, returns to main menu. 
*
**************************************************/
bool Menu::accountMenu(string uid)
{
	Manager accountManager = Manager();

	userID = uid;
	title = "Account Menu";
	input = 0;
	flag = false;
	const string options[] = { "View Passwords", "Add Password", "Log Out" };
	const int numOptions = (sizeof(options) / sizeof(options[0]));

	while (!flag)
	{
		//print menu options
		cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

		for (int i = 0; i < numOptions; i++)
		{
			int optNum = i + 1;
			cout << optNum << ". " << options[i] << endl;
		}

		//get menu choice
		cout << "Pick an option from the menu: ";
		cin >> input;

		//do choice
		switch (input)
		{
		case 1: //view pw
			flag = true;
			accountManager.viewPasswords(userID);
			return flag;
		case 2: //add pw
			flag = true;
			accountManager.addPassword(userID);
			return flag;
		case 3: //logout
			flag = false;
			return flag;
		default: //invalid option
			flag = false;
			cout << "\n\nInvalid menu option entered." << endl << endl;
			break;
		}//switch
	}
} //accountMenu function
