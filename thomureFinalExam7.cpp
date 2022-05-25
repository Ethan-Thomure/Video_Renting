/* Stuff I added:
(I tried to organize stuff, but with time constraints, I had to choose between functionality and neatness)
	Easy stuff:
	---------------------
		-	Person names and movie names with spaces

		-	Stupid-proofing - make sure numbers within range and such...
							  gender has to match whatever options you deem appropriate...
							  age within reaonable range... possibly exclude under 12 or something)	  

		-	Different sort criteria - (I chose sortCustByAge)

		-	Auto-load on startup and save on exit, sort after adding

		-	Basic Money - like incorporating at rental time but not keeping track or paying down

		-	Rating - ask user for rating after the movie name and 
					 don't allow the rental if customer is too young

		-	Receipt - nicely formatted summary of the transaction

		-	Different "focus search" (print adults) - only one (Print Employees)

		-	Password protect - can have name and PW (You are Skyler Ross with password JohnWick, everyone else has "password" as password)

		-	Add ANY attribute to the customer - gotta modify functions appropiately	(chose Debt and Privelege and Password)

		-	Different menus for customer/employee or for DB maint vs. handling movies
	--------------------
	Less basic stuff:
	--------------------
		-	Return movies - individually
		
		-	Money - track balance for each customer and add function for them to pay it off 
			completely or in part
			
		-	Sell snacks and such - only if you've incorporated money and tie this to it
								   don't give me "would you like popcorn with that?... yes or no" (gave buy snacks as a separate option)

		-	Movie Database - allow customer/clerk to select from a list of movies 
			  	 instead of typing in names (but when returning stuff you would have to because im lazy)
			  	 
		-	Ratings with Restrictions - Add a rating for each movie to the database of movies
	-----------------------
	More involved stuff:
	--------------------------
		-	Create new employee with login (wouldnt have suggested it if I couldnt do it)
		
		-	Multiple employees - each with different sign-ins 
						     give them different priveleges would be worth a LOT... like only level
						     2 employees can add or remove customers (easy peasy)
						     
		-	Create a database of movies (of MovieType) - and use that to rent from... 
													especially good if you track number in stock and put them back when
													they are returned (Yep)
---------------------------------------------------------------------------------------									
Stuff I DIDNT do:

	Easier Stuff
	-	Bells and whistles - Wide open.. start with a function to print an awesome "banner"
Less basic                                                                 
	-	Rewards - Pretty similar to discounts... maybe free snack with rental of some number of movies		   			  	 
	-	Discounts - possibly based on number of movies being rented... 
			 third one's free, or half price
			 or maybe keep track of total movies rented and give a free one after so many			 			  	 
	-	Due date - not sure how to do this because I'm not testing it over a period of time
		   but if you can come up with something cool	(I could do this, it would involve using ctime
		   												 and it will take too much effort for a "less basic" point value)	
More involved
	-	Zach wants to be robbed... not sure how that would work but
		I don't want any references to any form of violence... Insults are fine (I dont want to be robbed)
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "thomureFinalExamClasses7.h"
using namespace std;

// have file with three customers at least, include the header file

int main()
{	
	StoreType store;
	int answer;
	string temp;
	bool quit = false;
	
	do{	
		store.loadCust();
		store.loadMovie();
		system("cls");
		cout << "Welcome to Ethan's Super Duper Mega Awesome Ultra Fun Magically Cool Video Renting Center" << endl;
		line();
		cout << endl << "Who are you?" << endl
			 << "1 - Customer" << endl
			 << "2 - Employee" << endl
			 << "0 - Quit"<< endl << endl << "Enter: ";
		cin >> answer;
		switch (answer) {
			case 1:
				store.custEnterPassword();
				break;
			case 2:
				store.employeeEnterPassword();
				break;
			case 0:
				quit = true;
				break;
			default:
				cout << "Sorry, but that is not an option...";
				wait();
				break;
		}
	} while (!quit);
		
	//End the program
	cout << endl << endl;
	system("pause");
	return 0;	
}
