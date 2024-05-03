/********************************************
* 
* @file main.cpp
* 
* @brief CS 4930 (Spring 2024) Semester Project: Encrypted Password Manager.
* 
**************************************************/


#include "main.h"

using namespace std;



int main()
{
	bool programRunning = true; 

	//start program
	Menu menu = Menu();

	while (programRunning)
	{
		programRunning = menu.mainMenu();

		//user did not choose to exit on main menu
		if (programRunning)
		{
			//authenticate user login credentials
			Account userAccount = Account();
			string userID = "";
			bool userLoggedIn = false;
			userID = userAccount.authenticateUser();

			if (userID == "0")
			{
				userLoggedIn = false;
			}
			else
			{
				userLoggedIn = true;
			}
			
			//show account menu for authenticated user while they're logged in
			while (userLoggedIn)
			{
				userLoggedIn = menu.accountMenu(userID);
			}
		}
	}//while program running

	//Exit program
	cout << "\n\n======================================\n" << "\t Exiting Password Manager... " << "\n======================================\n\n" << endl;

	return 0;
}