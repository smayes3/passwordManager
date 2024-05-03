/*********************************************
*
* @file manager.h
*
* @brief manager class and function declarations.
*
*********************************************/


#pragma once

#include "main.h"

using namespace std;



class Manager
{
protected:
	string title;
	string userID;
	string userInputString;
	bool flag;

public:
	Manager(); //constructor
	~Manager() {}; //destructor
	string getInput();
	void viewPasswords(string);
	void addPassword(string);
};


/*********************************************
*
* @brief manager constructor.
*
* @param title: string, display for page title.
* @param userID: string, a hashed userID.
*
*********************************************/
Manager::Manager()
{
	title = "";
	userID = "";
} //constructor


/*********************************************
*
* @brief Function that handles getting user input
*
* @return input: string, the user input.
*
*********************************************/
string Manager::getInput()
{
	string input = "";
	
	cin >> input;

	return input;

} //getInput function


/*********************************************
*
* @brief Function that handles adding account information to the password manager.
* 
* @detail Gets the site name, username, and password, then stores it into the user's file (<userID>.dat).
*
* @param uid: string, a hashed userID.
*
*********************************************/
void Manager::addPassword(string uid)
{
	userID = uid;
	string sitename;
	string username;
	string password;
	fstream userFile;
	string filePath = DATA_PATH + userID + ".dat";
	title = "Add Account Information";

	cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

	//append account info to specified user's file
	userFile.open(filePath, ios::app);


	if (userFile.fail())
	{
		cout << "ERROR!! - Cannot open user's manager file. " << endl;
	}
	else
	{

		cout << "Enter site name: ";
		sitename = getInput();
		cout << endl;

		cout << "Enter username: ";
		username = getInput();
		cout << endl;

		cout << "Enter password: ";
		password = getInput();
		cout << endl;

		userFile << sitename << "," << username << "," << password << endl;

		cout << endl << endl;
		cout << "Account information added!" << endl << endl;

		userFile.close();
	}
	return;

} //addPassword function


/*********************************************
*
* @brief Function that handles viewing account information stored in the password manager.
* 
* @detail Prints each line of the user's manager file (<userID>.dat) that contains all account information.
* 
* @param uid: string, a hashed userID.
*
*********************************************/
void Manager::viewPasswords(string uid)
{
	userID = uid;
	string line = "";
	ifstream userFile;
	string filePath = DATA_PATH + userID + ".dat";

	title = "Account Information";

	cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

	//open specified user's file of passwords
	userFile.open(filePath);

	if (userFile.fail())
	{
		cout << "ERROR!! - Cannot open file for userID: " << userID << endl;
	}
	else
	{

		//print out each line of the file
		getline(userFile, line, '\n');

		while (userFile)
		{
			cout << line << endl;

			getline(userFile, line, '\n');
		}

		userFile.close();
	
	}

	return;

} //viewPasswords function
















