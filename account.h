/*********************************************
*
* @file account.h
*
* @brief Account class and function declarations.
*
*********************************************/

#pragma once

#include "main.h"
#include "crypto.h"

#define MIN_PW_LENGTH 8

using namespace std;


//using namespace std;


/*********************************************
*
* @class Account
* 
* @brief Account class used to handle user account creation and access.
*
*********************************************/
class Account
{
protected:
	string title;
	string message;
	string userInputString;
	string userID;
	string stringHash;
	string usernameHash;
	string passwordHash;
	
	bool userExists;

public:
	Account(); //constructor
	~Account() {}; //destructor
	bool createAccount();
	string hashString(string);
	bool checkExistingUsers(string);
	string getUserID(string);
	string createHash(string);
	bool isUserValid(string, string);
	string authenticateUser();
}; //Account class declaration


/*********************************************
*
* @brief Account constructor.
*
* @param title: string, display for page title.
* @param message: string, messages to user.
* @param userInputString: string, holds the users input.
* @param userID: string, a hashed userID.
* @param stringHash: string, a hashed string.
* @param usernameHash: string, a hashed username.
* @param passwordHash: string, a hashed password.
* @param userExists: bool, a flag for checking if a user exists
*
*********************************************/
Account::Account()
{
	title = "";
	message = "";
	userInputString = "";
	userID = "";
	stringHash = "";
	usernameHash = "";
	passwordHash = "";
	userExists = false;
}//account constructor


/*********************************************
*
* @brief Function that handles user account creation.
* 
* @details Account creation requires the username to be unique and passwords to be at least 8 characters long
*
*********************************************/
bool Account::createAccount()
{
	string getUsernameMsg = "Enter a username: ";
	string getPasswordMsg = "Enter a password with at least 8 characters: ";
	bool pwFlag = false;
	bool success = false;
	title = "Create new user account";

	cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

	//flag to check if a specified user already exists
	userExists = true;

	//get desired username, repeat until a unique username is created
	while (userExists)
	{
		userInputString = "";

		//get username, check if it already exists
		cout << getUsernameMsg;
		cin >> userInputString;
		usernameHash = hashString(userInputString);
		userExists = checkExistingUsers(usernameHash);
	}//while

	//get password that meets the minimum length requirement, store un/pw hash in USER_LIST file
	while (!pwFlag)
	{
		userInputString = "";

		int pwLength = 0;
		cout << getPasswordMsg;
		cin >> userInputString;

		//check length reqs
		pwLength = userInputString.length();

		if (pwLength < MIN_PW_LENGTH)
		{
			message = "ERROR: Password does not meet requirements, must be at least 8 characters.";
			cout << message << endl;
			pwFlag = false;
		}
		else
		{
			//hash the password and store it with the correct username/ID in the file with list of all users
			fstream listOfUsers;
			fstream userFile;

			passwordHash = hashString(userInputString);
			userID = getUserID(usernameHash);

			listOfUsers.open(USER_LIST, ios::app);
			listOfUsers << usernameHash << "," << passwordHash << endl;
			listOfUsers.close();

			string filenameUser = (DATA_PATH)+(userID)+".dat";

			userFile.open(filenameUser, ios::out);

			if (userFile.is_open())
			{
				userFile << "Site,Username,Password" << endl;
				userFile.close();

				message = "Account has been created!";
				cout << message << endl;

				pwFlag = true;
				success = true;

				return success;

			}
			else
			{
				cout << "ERROR!! - Cannot create user file!" << endl;
				pwFlag = true;
				success = false;

				return success;

			}
		}
	}
}//createAccount function


/*********************************************
*
* @brief Intermediary function that handles sending a string to be hashed.
* 
* @param unhashedString: string, the string input that needs to be hashed.
* 
* @return hashedString: string, the value of unhashedString after hash applied.
*
*********************************************/
string Account::hashString(string unhashedString)
{
	string hashedString;

	hashedString = createHash(unhashedString);

	return hashedString;

}//hashString function


/*********************************************
*
* @brief Function that handles hashing. 
*
* @param unhashedString: string, the string input that needs to be hashed.
*
* @return hashedString: string, the value of unhashedString after hash applied.
*
*********************************************/
string Account::createHash(string unhashedString)
{
	string hash;
	Crypto* hasher = new Crypto();

	hash = hasher->generateHash(unhashedString);

	return hash;

}//createHash function


/*********************************************
*
* @brief Function that checks if a user already exists.
* 
* @detail Parse the USER_LIST file line by line.
*
* @param usernameHash: string, the hashed value of a given username input.
*
* @return userExists: bool, true if the username already exists in the USER_LIST file.
* @return userExists: bool, false if the username does not exist in the USER_LIST file.
*
*********************************************/
bool Account::checkExistingUsers(string usernameHash)
{
	bool userExists = false;

	string line; //store line input read in from file 
	string user; //store user input read in from lineData vector
	vector<string> userOutput;

	fstream userList;
	userList.open(USER_LIST, ios::in);



	if (userList.is_open())
	{
		//getline(istream& is, string &str, char delim)
		//is: input stream
		//str: stores the input read, output string
		//delim: cease reading more when it reaches this char

		//break each line in file apart until end
		while (getline(userList, line))
		{
			//parse each line for the user hash
			stringstream lineData(line);
			while (getline(lineData, user, ','))
			{
				userOutput.push_back(user);
			}
		}

		userList.close();

		//search the output vector for matching username hash
		for (const auto& i : userOutput)
		{
			if (usernameHash == i)
			{
				userExists = true;
				message = "ERROR: Username unavailable. Try again.";
				cout << message << endl << endl;

				return userExists;
			}
			else
			{
				userExists = false; //username is available

				return userExists;
			}
		}
	}
	else
	{
		userExists = false;

		return userExists;
	}

}//checkExistingUsers function
	

/*********************************************
*
* @brief Function that gets the user's ID based on their username hash.
*
* @param usernameHash: string, the user's hashed username.
*
* @return userID: string, the value of the specified user's ID.
*
*********************************************/
string Account::getUserID(string usernameHash)
{
	userID = createHash(usernameHash);

	return userID;

}//getUserID function


/*********************************************
*
* @brief Function that check if a user is valid or they have an account.
* 
* @detail Checks the USER_LIST file line by line for a matching username and password. 
*
* @param usernameHash: string, the hashed version of user's username.
* @param passwordHash: string, the hashed version of user's password.
*
* @return validUser: bool, true if the user has a valid account.
* @return validUser: bool, false if the user does not a valid account.
*
*********************************************/
bool Account::isUserValid(string usernameHash, string passwordHash)
{
	bool validUser = false;
	ifstream userList(USER_LIST);
	string userCreds = usernameHash + "," + passwordHash;
	string buffer = "";
	size_t found;

	//check if the user list file exists, if it doesn't then no users are registered
	if (!userList.is_open())
	{
		validUser = false;

		return validUser;
	}

	//check file line by line until end
	while (!userList.eof())
	{
		getline(userList, buffer);

		//search for the UN/PW
		found = buffer.find(userCreds);

		//user found
		if (found != string::npos)
		{
			validUser = true;
			return validUser;
		}
	}

}//isUserValid function


/*********************************************
*
* @brief Function that handles login authentication. 
*
* @detail User enters their UN/PW, then those are hashed to check if the user is valid. The userID is retrieved using the username hash.
*
* @return userID: string, the authenticated user's userID.
*
*********************************************/
string Account::authenticateUser()
{
	string getUsernameMsg = "Enter your username: ";
	string getPasswordMsg = "Enter your password: ";
	userInputString = "";
	usernameHash = "";
	passwordHash = "";
	userID = "";
	title = "Log in";
	bool validUser = false;

	
	cout << "\n\n======================================\n" << title << "\n======================================\n\n" << endl;

	//get hashed username
	cout << getUsernameMsg;
	cin >> userInputString;

	usernameHash = createHash(userInputString);

	//get hashed password
	userInputString = "";
	cout << getPasswordMsg;
	cin >> userInputString;

	passwordHash = createHash(userInputString);

	//get userID
	userID = getUserID(usernameHash);

	//check if user is valid
	validUser = isUserValid(usernameHash, passwordHash);

	//if user not valid (no account/wrong username or password)
	if (validUser == 0)
	{
		message = "ERROR!! - Invalid username or password.";
		userID = "0";

		cout << endl << endl << message << endl << endl;

		return userID;
	}

	//go back to main
	return userID;

}//authenticateUser function