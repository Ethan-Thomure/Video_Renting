#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void wait()
{
	cout << endl << endl; 
	system("pause");// I decided to use systemPause because I think it looks nicer
	return;
}

void line(int howLong = 120, char what = '-')
{
	for(int i = 0; i < howLong; i++) {
		cout << what;
	}
	cout << endl;
	return;
}

// type for the movies
class MovieType {
	private:
		string name;
		double cost;
		string rating;
		int stack; //as in stack of movies
	public:
		friend class CustomerType;
		friend class StoreType;
		MovieType();
};

MovieType::MovieType() {
	stack = 0;
	return;
}

//Make a type for our customer
class CustomerType
{
	private:
		string first;
		string last;
		string password;
		int age;
		char gender;
		MovieType movie[10];
		int hmMoviesPossessed;
		int privelege;
		double debt;
	public:
		friend class StoreType;
		CustomerType();	
		void setPrivelege(int toWhat);		
};
	
//We can initialize the member attributes here
CustomerType::CustomerType()
{
	hmMoviesPossessed = 0;
	debt = 0;
	privelege = 0;
	return;
}

// function to change privelege of person
void CustomerType::setPrivelege(int toWhat = 1) {
	privelege = toWhat;
	return;
}
	
//Make a type for our store
class StoreType
{
	private:
		CustomerType customer[10];
		int hmCust;
		MovieType moviesInStock[10];
		int hmMoviesInStock; // how many movies we have
		
		int time;//TODO
		
	public:
		friend class CustomerType;
		StoreType();
		void addCust();
		void addEmployee();
		void removeCust();
		void addMovie();
		void removeMovie();
		void stockMovie();
		
		void rentMovie(int which);		
		void rentMovie();
		void returnMovie(int which);
		void returnMovie();
		void payOff(int which);
		void payOff();
		void buyCandy(int which);
		void buyCandy();
				
		void printCust(bool showMovies, int which, bool showBanner);
		void printAll(bool showMovies);
		void printCust(bool showMovies);
		void printAdult(bool showMovies);
		void printEmployees(bool showMovies);
		void printMovie();
		void menu(int whichCustomer);	
		void employeeEnterPassword();
		void custEnterPassword();
					
		void sortCust();
		void sortCustByAge();
		
		void saveCust();
		void loadCust();
		void saveMovie();
		void loadMovie();
};
	
//Again... initialize member attributes here
StoreType::StoreType()
{
	hmCust = 0;
	hmMoviesInStock = 0;
	return;
}
	
//Add a customer... all pretty obvious
void StoreType::addCust()
{
	cin.ignore(100, '\n');
	system("cls");
	
	cout << "Enter the customer's first name : ";
	getline(cin, customer[hmCust].first);
	cout << "and the last name : ";
	getline(cin, customer[hmCust].last);
	
	cout << "What password will they be using? ";
	cin >> customer[hmCust].password;
	
	cout << "and their age : ";
	cin >> customer[hmCust].age;
	while (customer[hmCust].age <= 12 || customer[hmCust].age >= 130) {
		cout << "Either they lied to you, or they shouldn't be allowed to purchase movies" << endl
		 	 << "Enter again: ";
		cin >> customer[hmCust].age;
	}
	
	cout << "and their gender (M or F) : ";
	cin >> customer[hmCust].gender;
	while (customer[hmCust].gender != 'M' && customer[hmCust].gender != 'F') { // sorry for not being politically correct...
		cout << "Just M or F, please: ";
		cin >> customer[hmCust].gender;
	}
	
	hmCust ++;
	return;
}

//Add an employee
void StoreType::addEmployee() {
	cin.ignore(100, '\n');
	system("cls");
	
	//first and last name
	cout << "Enter the employee's first name : ";
	getline(cin, customer[hmCust].first); // I will refer employees as customers because they can purchase movies too!
	cout << "and the last name : ";
	getline(cin, customer[hmCust].last);
	
	cout << "What password do they want to use? ";
	cin >> customer[hmCust].password;
	
	//age
	cout << "and their age : ";
	cin >> customer[hmCust].age;
	while (customer[hmCust].age <= 18 || customer[hmCust].age >= 130) {
		cout << "Either they lied to you, or they shouldn't be allowed to work here" << endl
		 	 << "Enter again: ";
		cin >> customer[hmCust].age;
	}
	
	//gender
	cout << "and their gender (M or F) : ";
	cin >> customer[hmCust].gender;
	while (customer[hmCust].gender != 'M' && customer[hmCust].gender != 'F') { // sorry for not being politically correct...
		cout << "Just M or F, please: ";
		cin >> customer[hmCust].gender;
	}
	
	//privelege
	int choice;
	cout << "Is this a(n)" << endl
		 << "1 - employee" << endl
		 << "2 - supervisor" << endl << endl << "Enter your choice: ";
	cin >> choice;
	while (choice != 1 && choice != 2) {
		cout << "Just 1 or 2: ";
		cin >> choice;
	}
	customer[hmCust].privelege = choice;
	
	hmCust ++;
	return;
}

//Remove a customer
void StoreType::removeCust()
{
	printCust(true);
	int which;
	cout << endl << "Which customer do you wish to remove : ";
	cin >> which;
	while (which < 0 || which > hmCust || customer[which].privelege != 0) {
		cout << "Invalid Customer, Try again: ";
		cin >> which;
	}
			
	//Start with that customer and 'overwrite' them with the next customer
	for ( int i = which; i < hmCust - 1; i ++ )
		customer[i] = customer[ i + 1 ];
	
	//And we've got one fewer customer now
	hmCust --;
	return;
}

void StoreType::addMovie() {
	printMovie();
	cin.ignore(100, '\n');
	
	cout << "Enter the Name of this new movie: ";
	getline(cin, moviesInStock[hmMoviesInStock].name);
	
	cout << "How much do you want it to cost? ";
	cin >> moviesInStock[hmMoviesInStock].cost;
	while(moviesInStock[hmMoviesInStock].cost < 0) {
		cout << "We don't pay the customers to use our services... try again: ";
		cin >> moviesInStock[hmMoviesInStock].cost;
	}
	
	cout << "What rating is the movie? ";
	cin >> moviesInStock[hmMoviesInStock].rating;
	while (moviesInStock[hmMoviesInStock].rating != "G" &&
		   moviesInStock[hmMoviesInStock].rating != "PG" &&
		   moviesInStock[hmMoviesInStock].rating != "R" &&
		   moviesInStock[hmMoviesInStock].rating != "MA") {
		
		cout << "That would be G, PG, R, or MA: ";
		cin >> moviesInStock[hmMoviesInStock].rating;
		}
	
	hmMoviesInStock++;
	return;
}

void StoreType::stockMovie() {
	printMovie();
	int which;
	int howMuch;
	
	cout << "Which movie to supply? (input the #) ";
	cin >> which;
	while(which < 0 || which > hmMoviesInStock) {
		cout << "Invalid Movie, try again";
		cin >> which;
	}
	
	cout << "How much movies do you want to add to it (or put in negative to rid of extra)? ";
	cin >> howMuch;
	
	moviesInStock[which].stack += howMuch;
	return;
}

void StoreType::removeMovie() {
	printMovie();
	int which;
	
	cout << "Enter the movie # that you want to remove: ";
	cin >> which;
	while(which < 0 || which > hmMoviesInStock) {
		cout << "Invalid movie, try again: ";
		cin >> which;
	}
	
	//remove it
	for ( int i = which; i < hmMoviesInStock - 1; i ++ )
		moviesInStock[i] = moviesInStock[ i + 1 ];
		
	hmMoviesInStock --;
	return;
}
// for when you only want to print 1 customer
void StoreType::printCust(bool showMovies, int which, bool showBanner) {
	if (showBanner) { // if this is the only customer being shown
		system("cls");
		cout << "#  First     Last      " << (showMovies ? "Age   Gen   Debt   Privelege   Movies " : "") << endl;
		line();
	}

	cout << setw(3) << left << which 
		 << setw(10) << customer[which].first << setw(10) << customer[which].last;
	if(showMovies) {
		cout << setw(6) << customer[which].age << setw(6) << customer[which].gender << fixed 
			 << setprecision(2) << setw(7) << customer[which].debt << setw(12) << customer[which].privelege;
		
		//And loop through their array of movies to print them out
		for( int j = 0; j < customer[which].hmMoviesPossessed ; j++ )
			cout << customer[which].movie[j].name << " ";
	}
	cout << endl;
	return;
}

void StoreType::printAll(bool showMovies) {
	system("cls");		
	cout << "Welcome to Ethan's Super Duper Mega Awesome Ultra Fun Magically Cool Video Renting Center" << endl;
	line();
	cout << "        List of everyone involved here" << endl;
	line();
	cout << "#  First     Last      " << (showMovies ? "Age   Gen   Debt   Privelege   Movies " : "") << endl;
	line();
	
	for(int i = 0; i < hmCust; i++) {
		printCust(showMovies, i, false);
	}
}

void StoreType::printCust(bool showMovies)
{
	//Standard banner
	system("cls");		
	cout << "Welcome to Ethan's Super Duper Mega Awesome Ultra Fun Magically Cool Video Renting Center" << endl;
	line();
	cout << "        Customer list" << endl;
	line();
	cout << "#  First     Last      " << (showMovies ? "Age   Gen   Debt   Privelege   Movies " : "") << endl;
	line();
	
	//Loop through the array of customers and print out their info
	for ( int i = 0; i < hmCust; i ++ )
	{
		// only print em out if they are customers
		if (customer[i].privelege == 0) {
			printCust(showMovies, i, false);
			cout << endl;
		}
	}
	return;
}
	
//To just print the adults
void StoreType::printAdult(bool showMovies)
{
	//Standard banner
	system("cls");		
	cout << "Welcome   to   Video   Rama" << endl;
	line();
	cout << "        Customer list" << endl;
	line();
	cout << "#  First     Last      " << (showMovies ? "Age   Gen   Debt   Movies " : "") << endl;
	line();
	
	//Loop through the array of customers
	for ( int i = 0; i < hmCust; i ++ )
	{
		//But only print them out if they are adults
		if( customer[i].age >= 18 ) {
		printCust(showMovies, i, false);
			cout << endl;	
		}	
	}
	return;
}

void StoreType::printEmployees(bool showMovies) {
	//Standard banner
	system("cls");		
	cout << "Welcome to Ethan's Super Duper Mega Awesome Ultra Fun Magically Cool Video Renting Center" << endl;
	line();
	cout << "        Customer list" << endl;
	line();
	cout << "#  First     Last      " << (showMovies ? "Age   Gen   Debt   Privelege   Movies " : "") << endl;
	line();
	
	//Loop through the array of employees
	for ( int i = 0; i < hmCust; i ++ )
	{
		//But only print them out if they are employees
		if( customer[i].privelege > 0 ) {
			printCust(showMovies, i, false);
			cout << endl;	
		}		
	}
	return;
	
}

void StoreType::printMovie() {
	system("cls");		
	cout << "Welcome to Ethan's Super Duper Mega Awesome Ultra Fun Magically Cool Video Renting Center" << endl;
	line();
	cout << "        List of Movies" << endl;
	line();
	cout << "#  Rating   Cost     In Stock    Name" << endl;
	line();
	
	for(int i = 0; i < hmMoviesInStock; i++) {
		cout << left << setw(3) << i << setw(8) << moviesInStock[i].rating << "$" << setw(9) << setprecision(2) << fixed
			 << moviesInStock[i].cost << setw(12) << moviesInStock[i].stack << moviesInStock[i].name << endl;
	}
	cout << endl;
	line(120, '=');
	cout << endl << endl;
	return;
}

void StoreType::sortCust()
{
	CustomerType temp;
	
	//Loop through multiple times and sort by first name
	for ( int j = 0; j < hmCust - 1; j ++ )
	{
		//Loop through the array of customers
		for( int i = 0; i < hmCust - 1; i ++ )
		{
			//If we find a pair out of order
			if ( customer[i].first > customer[i + 1].first )
			{
				//Swap them... put them in the right order
				temp = customer[i];
				customer[i] = customer[i + 1];
				customer[i + 1] = temp;
			}
		}
	}
	
	//And do it again for last names
	for ( int j = 0; j < hmCust - 1; j ++ )
	{
		//Loop through the array of customers
		for( int i = 0; i < hmCust - 1; i ++ )
		{
			//If we find a pair out of order
			if ( customer[i].last > customer[i + 1].last )
			{
				//Swap them... put them in the right order
				temp = customer[i];
				customer[i] = customer[i + 1];
				customer[i + 1] = temp;
			}
		}
	}
	return;
}

void StoreType::sortCustByAge() {
	CustomerType temp;
	//Loop through multiple times and sort by first name
	for ( int j = 0; j < hmCust - 1; j ++ )
	{
		//Loop through the array of customers
		for( int i = 0; i < hmCust - 1; i ++ )
		{
			//If we find a pair out of order
			if ( customer[i].age > customer[i + 1].age )
			{
				//Swap them... put them in the right order
				temp = customer[i];
				customer[i] = customer[i + 1];
				customer[i + 1] = temp;
			}
		}
	}
	return;
}

//Save Customers to a file
void StoreType::saveCust()
{
	ofstream writeCust ( "thomureCustomers.dat", ios::out );
		if ( !writeCust ) {//if there was a problem creating the writefile object
			cerr << "File couldn't be opened.";
			exit(1);
		}
	
	//Save the number of customers/employees first, so when load the file, we know how many to expect
	writeCust << hmCust << " ";
	
	//Loop through the array of customers
	for( int i = 0; i < hmCust; i ++ ) {
	
	//convert " " into "_"
		for (int j = 0; j < customer[i].first.length(); j++) {
			if (customer[i].first[j] == ' ') customer[i].first[j] = '_';
		}
		for (int j = 0; j < customer[i].last.length(); j++) {
			if (customer[i].last[j] == ' ')	customer[i].last[j] = '_';
		}
		
		// going through customer movies and remove spaces
		for (int j = 0; j < customer[i].hmMoviesPossessed; j++) {
			string movieName = customer[i].movie[j].name;
			//going through the list of char in the movies
			for(int k = 0; k < movieName.length(); k++) {
				if (movieName[k] == ' ') movieName[k] = '_';
			}
			customer[i].movie[j].name = movieName;
		}
	
		//save their information
		writeCust << customer[i].first << " " << customer[i].last << " " << customer[i].age << " " 
		<< customer[i].gender << " " << customer[i].privelege << " " << customer[i].password << " " 
		<< customer[i].debt << " " << customer[i].hmMoviesPossessed << " ";
		
		//including their movies	 	  
		for ( int j = 0; j < customer[i].hmMoviesPossessed; j ++ ){
			writeCust << customer[i].movie[j].name << " " << customer[i].movie[j].cost << " " << customer[i].movie[j].rating << " ";
			customer[i].movie[j].stack = 1;
		}
		//convert "_" back into " " because program didnt close yet and people would see the "_"
		for (int j = 0; j < customer[i].first.length(); j++) {
			if (customer[i].first[j] == '_') customer[i].first[j] = ' ';
		}
		for (int j = 0; j < customer[i].last.length(); j++) {
			if (customer[i].last[j] == '_')	customer[i].last[j] = ' ';
		}
	}
	return;
}
	
//Load Customers from the file
void StoreType::loadCust()
{
	ifstream readCust ( "thomureCustomers.dat", ios::in );
	
	if ( !readCust )
	{
		cerr << "File could not be opened";
		exit(1);
	}
	
	//Get the number of customers first
	readCust >> hmCust;

	//Use it to control our loop through the array
	for( int i = 0; i < hmCust; i ++ ) {
		
		//get each customer's information
		readCust >> customer[i].first >> customer[i].last >> customer[i].age >> customer[i].gender 
		  		 >> customer[i].privelege >> customer[i].password >> customer[i].debt >> customer[i].hmMoviesPossessed;
				 
		//including their movies
		string movieName;
		for( int j = 0; j < customer[i].hmMoviesPossessed; j ++ ) {
			readCust >> movieName >> customer[i].movie[j].cost >> customer[i].movie[j].rating;
			//going through the list of char in the movies to convert back to spaces
			for(int k = 0; k < movieName.length(); k++) {
					if (movieName[k] == '_') movieName[k] = ' ';
			}
			customer[i].movie[j].name = movieName;
		}
		//convert "_" into " "
		for (int j = 0; j < customer[i].first.length(); j++) {
			if (customer[i].first[j] == '_') customer[i].first[j] = ' ';
		}
		for (int j = 0; j < customer[i].last.length(); j++) {
			if (customer[i].last[j] == '_') customer[i].last[j] = ' ';
		}
	}
	return;
}

void StoreType::saveMovie() {
	ofstream writeMovie ("thomureMovies.dat", ios::out);
	if (!writeMovie) {
		cerr << "File Couldn't be opened";
		exit(1);
	}
	
	//save how many movies we have first
	writeMovie << hmMoviesInStock << " ";
	
	// going through  movies and removing spaces
	for (int j = 0; j < hmMoviesInStock; j++) {
		string movieName = moviesInStock[j].name; // so that way when we try to look at the name, it wont have "_"
			
		//going through the list of char in the movies to remove spaces
		for(int k = 0; k < movieName.length(); k++) {
			if (movieName[k] == ' ') movieName[k] = '_';
		}
		// might as well write it to the file while we are at it
		writeMovie << movieName << " " << moviesInStock[j].stack << " " << moviesInStock[j].rating
				   << " " << moviesInStock[j].cost << " ";
	}
	return;
}

void StoreType::loadMovie() {
	ifstream readMovie ("thomureMovies.dat", ios::in);
	if (!readMovie) {
		cerr << "File Couldn't be opened";
		exit(1);
	}
	
	//save how many movies we have first
	readMovie >> hmMoviesInStock;
	
	//loop through array of moviesInStock	
	for (int j = 0; j < hmMoviesInStock; j++) {
		readMovie >> moviesInStock[j].name >> moviesInStock[j].stack >> moviesInStock[j].rating
				  >> moviesInStock[j].cost;
				  		
		//going through the list of char in the movies to change back to " "
		for(int k = 0; k < moviesInStock[j].name.length(); k++) {
			if (moviesInStock[j].name[k] == '_') moviesInStock[j].name[k] = ' ';
		}

	}
	return;
}

//renting movie for when the purchacer is known
void StoreType::rentMovie(int which) {
	
	int moviePurchasedCount = 0; // how many movies in one bill
	int initialMoviesCount = customer[which].hmMoviesPossessed;
	//Allow them to enter movies until they are done
	do{
		double tempMoney;
		string tempRating;
		int whichMovie;
		
		printMovie();
		cout << endl << "Enter movie number (-1 to stop) : ";
		cin >> whichMovie;
		
		
		// putting this here, because -1 is not a movie
		if (whichMovie == -1) {
			break;
		}
		
		// checking if we have it
		if (whichMovie < -1 || whichMovie > hmMoviesInStock || moviesInStock[whichMovie].stack < 1) {
			cout << "WE DONT HAVE THAT!...";
			wait();
			continue;
		}
		
		// checking if person is old enough
		if ((customer[which].age < 18 && moviesInStock[whichMovie].rating == "R") || 
			(customer[which].age < 21 && moviesInStock[whichMovie].rating == "MA")) {
			cout << "Not Age appropriate..." << endl;
			wait();
			continue; // go back to ask for a different movie, or quit
		}	
			
		//copying the movie from the store into the customer's possession
		customer[which].movie[customer[which].hmMoviesPossessed].name = moviesInStock[whichMovie].name;
		customer[which].movie[customer[which].hmMoviesPossessed].rating = moviesInStock[whichMovie].rating;
		customer[which].movie[customer[which].hmMoviesPossessed].cost = moviesInStock[whichMovie].cost;
		customer[which].movie[customer[which].hmMoviesPossessed].stack = 1;
		
		//And now they have one more movie and we have one less of that movie
		customer[which].hmMoviesPossessed ++;
		moviesInStock[whichMovie].stack --;
		moviePurchasedCount ++;
			
	}while (true);

	system("cls");
	line(120, '=');
	cout << "Reciept for " << customer[which].first << " " << customer[which].last << endl;
	line(120, '_');
	cout << setw(80) << "Movie Name:" << "Price:" << endl;
	line();
	double subtotal = 0;
	for(int i = initialMoviesCount; i < initialMoviesCount + moviePurchasedCount; i++) {
		cout << left << setw(80) << customer[which].movie[i].name << "$" << fixed << setprecision(2) 
			 << customer[which].movie[i].cost << endl << endl;

		subtotal += customer[which].movie[i].cost;
	}
	cout << endl << endl;
	line(120, '=');
	cout << left << setw(80) << fixed << setprecision(2) << "Subtotal: " << "$" << subtotal << endl;
	cout << left << setw(80) << "Tax: " << fixed << setprecision(2) << subtotal * .07 << endl;
	cout << left << setw(80) << fixed << setprecision(2) << "Total: " << "$" << subtotal * (1 + .07);
	wait();
	
	customer[which].debt += subtotal * (1 + .07);
	return;
}

void StoreType::rentMovie() {
	//Find out which customer will be renting
	int which;
//	string temp;//to delete remaining stuff in input stream
	printCust(true);
	cout << endl << "Which customer is renting? : ";
	cin >> which;
	while (which > hmCust - 1 || which < 0 || customer[which].privelege != 0) {
		cout << endl << "That is not a valid customer, please try again: ";
		cin >> which;
	}
	rentMovie(which);
	return;
}
	
//returning movie for when returner is known
void StoreType::returnMovie(int which) {
	string answer;
	cin.ignore(100, '\n');
	do {
		system("cls");
		printCust(true, which, true);
		
		cout << endl << "Which movie is being returned (stop to stop)? ";
		getline(cin, answer);
		
		if (answer == "stop") break;
		
		//looking through movies
		for(int i = 0; i < customer[which].hmMoviesPossessed; i++) {
			
			//if movie found
			if (answer == customer[which].movie[i].name) {
				
				//search through store's movies
				for (int j = 0; j < hmMoviesInStock; j++) {
					
					// and give it back					
					if (answer == moviesInStock[j].name) {
						moviesInStock[j].stack ++;
						break; // because the movies don't stack for the customer but do for the store
					}
				}
				// get rid of it even if the store doesn't have it anymore
				for ( int j = i; j < customer[which].hmMoviesPossessed - 1; j ++ )
					customer[which].movie[j] = customer[which].movie[ j + 1 ];
				// by forgetting the last one
				customer[which].hmMoviesPossessed--;
				break;
			}
		}
	} while(true);
	return;
}

void StoreType::returnMovie() {
	//Find out which customer is returning
	int which;
	printAll(true);
	cout << endl << endl << "Who is returning? : ";
	cin >> which;
	while(which > hmCust || which < 0) {
		cout << "Invalid, try again";
		cin >> which;
	}
	
	returnMovie(which);
	return;
}

void StoreType::payOff(int which) {
	double amount;
	printCust(true, which, true);
	cout << endl << "How much money is being paid off? ";
	cin >> amount;
	while(amount < 0) {
		cout << "I am not paying you! Enter again: ";
		cin >> amount;
	}
	if(amount > customer[which].debt) {
		cout << endl << "The change is " << amount - customer[which].debt << endl;
		wait();
		amount = customer[which].debt;
	}
	customer[which].debt -= amount;
	return;
}

void StoreType::payOff() {
	int which;
	printAll(true);
	cout << endl << endl << "Who is Paying? : ";
	cin >> which;
	while(which > hmCust || which < 0) {
		cout << "Invalid, try again";
		cin >> which;
	}
	
	payOff(which);
	return;
}

// function only for buyCandy
double storeDict(int option) {
	switch(option) {
		case 1:
		case 2:	
			return 1.00;
			break;
		case 3:
			return 2.00;
			break;
		case 4:
			return 12.99;
			break;
		case 5:
			return 6.00;
			break;
		default:
			return 0.00;
			break;		
	}
}

void StoreType::buyCandy(int which) {
	int choice;
	int totalItems = 0;	
	int cart[15]; // to keep track of bought items
	
	do {
		system("cls");
		cout << "What would " << customer[which].first << " like to buy?" << endl;
		line();
		cout << "items in cart: ";
		for (int i = 0; i < totalItems; i++) {
			cout << cart[i] << " ";
		}
		cout << endl;
		line();
		cout << setprecision(2) << fixed << endl << endl << "1 - Candy "<< storeDict(1) << endl
			 << "2 - Small Soda " << storeDict(2) << endl
			 << "3 - Medium Soda " << storeDict(3) << endl
			 << "4 - Super Duper Mega Awesome Ultra Fun Magically Cool Sized Soda " << storeDict(4) << endl
			 << "5 - Popcorn Large " << storeDict(5) << endl
			 << "0 - Finish order" << endl << endl << "Enter choice: ";
		cin >> choice;
		while (choice < 0 || choice > 5) {
			cout << "INVALID OPTION, try again: ";
			cin >> choice;
		}
		cart[totalItems] = choice;
		totalItems++;
	} while (choice != 0);

	system("cls");
	line(120, '=');
	cout << "Reciept for " << customer[which].first << " " << customer[which].last << endl;
	line(120, '_');
	cout << setw(80) << "Snack Number:" << "Price:" << endl;
	line();
	
	totalItems--; // taking out "Finish Order" of the cart
	double subtotal = 0;
	for(int i = 0; i < totalItems; i++) {
		cout << left << setw(80) << cart[i] << "$" << fixed << setprecision(2) 
			 << storeDict(cart[i]) << endl << endl;
		subtotal += storeDict(cart[i]);
	}
	cout << endl << endl;
	line(120, '=');
	cout << left << setw(80) << fixed << setprecision(2) << "Subtotal: " << "$" << subtotal << endl;
	cout << left << setw(80) << "Tax: " << fixed << setprecision(2) << subtotal * .07 << endl;
	cout << left << setw(80) << fixed << setprecision(2) << "Total: " << "$" << subtotal * (1 + .07);
	wait();
	customer[which].debt += subtotal * (1 + .07);
	return;
}

void StoreType::buyCandy() {
	int which;
	printCust(true);
	cout << "Who is buying snacks? ";
	cin >> which;
	while (which < 0 || customer[which].privelege != 0) {
		cout << "INVALID CUSTOMER, try again: ";
		cin >> which;
	}
	buyCandy(which);
	return;
}

// function to check if password is correct and runs menu if it did
void StoreType::employeeEnterPassword() {
	int answer;
	string attempt;
	
	printEmployees(false);
	cout << endl << endl << "Which Employee # are you (or enter -1 to go back): ";
	cin >> answer;
	
	if (answer == -1) return; // quit
	while (customer[answer].privelege < 1 || answer > hmCust)  {// if it isn't an employee
		cout << "Not a valid employee, try again: ";
		cin >> answer;
	}
	
	system("cls");
	cout << "Enter Password: ";
	cin >> attempt;
	while (attempt != customer[answer].password) {
		cout << "INCORRECT, TRY AGAIN: ";
		cin >> attempt;
	}
	menu(answer);
	return;
}

// function to check if password is correct for a customer and runs menu if it did
void StoreType::custEnterPassword() {
	int answer;
	string attempt;
	
	printCust(false);
	cout << endl << endl << "Which Customer # are you (or enter -1 to go back): ";
	cin >> answer;
	
	if (answer == -1) return; // quit
	while (customer[answer].privelege != 0 || answer > hmCust)  {// if it isn't a customer
		cout << "Not a valid customer, try again: ";
		cin >> answer;
	}
	
	system("cls");
	cout << "Enter Password: ";
	cin >> attempt;
	while (attempt != customer[answer].password) {
		cout << "INCORRECT, TRY AGAIN: ";
		cin >> attempt;
	}
	menu(answer); // runs menu for the customer
	return;
}

// Displays menu based on the privelege person has
void StoreType::menu (int whichCustomer) {
	int choice;
	
	loadCust();
	// using if because switch within switch would be confusing
	if (customer[whichCustomer].privelege == 3) { //if person is an administrator
		do {
		int temp;
		
		system("cls"); // choose login: Customer (level 0), Employee (level 1), Administrator(pre made account for Skyler Ross, user: SkylerRoss Password: LovesJohnWick) (level 2)
			
		line();
		cout << "        Administrative Options" << endl;
		line();
		cout << "1 - Profile" << endl
			 << "2 - Add a customer and Sort by Last Name" << endl
			 << "3 - Remove and a customer and Sort by Last Name" << endl
			 << "4 - Add employee and sort by last name" << endl
			 << "5 - Promote/Demote/Hire employee" << endl
			 << "6 - Add a movie" << endl
			 << "7 - Remove a movie" << endl
			 << "8 - Stock a movie" << endl
			 << "9 - Print the customers" << endl
			 << "10 - Print adults" << endl	
			 << "11 - Print the Employees" << endl
			 << "12 - Print the Movies" << endl
			 << "13 - Rent movies" << endl
			 << "14 - Buy Some Snacks for a Customer" << endl
			 << "15 - Return movies" << endl	
			 << "16 - Have a person pay off" << endl	 			 		 
			 << "17 - Save the customers/Employees/movies" << endl
			 << "18 - Sort the customers by age and Save customers" << endl
			 << "19 - Logout without Saving" << endl
			 << "20 - Set your debt to zero... because it's your store" << endl
			 << "21 - Rent a movie for yourself" << endl
			 << "22 - Buy some snacks for yourself" << endl
			 << "0 - Save cusotmers and movies and Logout" << endl << endl << "Enter your choice : "; // change to save and exit
		cin >> choice;
		
		//Since we named our functions well, none of this needs commenting
		switch ( choice )
		{
			case 1:
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 2:
				addCust();
				sortCust();
				printCust(true);
				wait();
				break;
			case 3:
				removeCust();
				sortCust();
				printCust(true);
				wait();
				break;
			case 4:
				addEmployee();
				sortCust();
				printEmployees(true);
				wait();
				break;	
			case 5:
				int newPrivelege;
				
				printAll(true);
				cout << endl << "Who are you going to change priveleges to? ";
				cin >> temp;
				while(temp > hmCust || temp < 0) {
					cout << "Invalid Person, try again: ";
					cin >> temp;
				}
				
				system("cls");
				printCust(true, temp, true);
				cout << "What will you set this person to:" << endl
					 << "0 - Customer, If you wanted to fire someone, set them to this first" << endl
					 << "1 - Employee" << endl
					 << "2 - Supervisor" << endl
					 << "3 - Administrator, Use this option with caution!" << endl << endl << "Enter your choice: ";
				cin >> newPrivelege;
				while (newPrivelege < 0 || newPrivelege > 3) {
					cout << "INVALID OPTION, TRY AGAIN: ";
					cin >> newPrivelege;
				}
				customer[temp].setPrivelege(newPrivelege);
				printAll(true);
				wait();
				break;
			case 6:
				addMovie();
				printMovie();
				wait();
				break;
			case 7:
				removeMovie();
				printMovie();
				wait();
				break;
			case 8:
				stockMovie();
				printMovie();
				wait();
				break;
			case 9:
				printCust(true);
				wait();
				break;
			case 10:
				printAdult(true);
				wait();
				break;	
			case 11:
				printEmployees(true);
				wait();
				break;	
			case 12:
				printMovie();
				wait();
				break;
			case 13:
				rentMovie();
				printCust(true);
				wait();
				break;
			case 14:
				buyCandy();
				printCust(true);
				wait();
				break;
			case 15:
				returnMovie();
				printCust(true);
				wait();
				break;	
			case 16:
				payOff();
				printCust(true);
				wait();
				break;
			case 17:
				saveCust();
				saveMovie();
				printCust(true);
				wait();
				break;
			case 18:
				sortCustByAge();
				saveCust();
				printCust(true);
				wait();
				break;
			case 19:
				return;
//				break;
			case 20:
				customer[whichCustomer].debt = 0;
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 21:
				rentMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 22:
				buyCandy(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 0:
				saveCust();
				saveMovie();
				break;
			default:
				cout << "Sorry but that's not an option";
				wait();
				break;
			}	
		}while(choice);
	} else if(customer[whichCustomer].privelege == 2) { // if person is a supervisor
		do {
		system("cls");
			
		line();
		cout << "        Supervisor Options" << endl;
		line();
		cout << "1 - Profile" << endl
			 << "2 - Add a customer and Sort by Last Name" << endl
			 << "3 - Remove and a customer and Sort by Last Name" << endl
			 << "4 - Stock Movies" << endl
			 << "5 - Print the customers" << endl
			 << "6 - Print adults" << endl
			 << "7 - Print Movies" << endl
			 << "8 - Rent movies" << endl
			 << "9 - Rent movies for yourself" << endl
			 << "10 - Buy Snacks" << endl
			 << "11 - Buy Snacks for yourself" << endl
			 << "12 - Return movies" << endl
			 << "13 - Return your movies" << endl
			 << "14 - Have a person pay up" << endl
			 << "15 - Pay your bill" << endl
			 << "16 - Save the customers and movies" << endl
			 << "17 - Sort the customers by age and Save" << endl
			 << "18 - Logout without Saving" << endl
			 << "0 - Save and Logout" << endl << endl << "Enter your choice : "; // change to save and exit
		cin >> choice;
		
		//Since we named our functions well, none of this needs commenting
		switch ( choice )
		{
			case 1:
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 2:
				addCust();
				sortCust();
				printCust(true);
				wait();
				break;
			case 3:
				printCust(true);
				removeCust();
				sortCust();
				printCust(true);
				wait();
				break;
			case 4:
				stockMovie();
				printMovie();
				wait();
				break;
			case 5:
				printCust(true);
				wait();
				break;
			case 6:
				printAdult(true);
				wait();
				break;
			case 7:
				printMovie();
				wait();
				break;
			case 8:
				rentMovie();
				printCust(true);
				wait();
				break;	
			case 9:
				rentMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 10:
				buyCandy();
				printCust(true);
				wait();
				break;
			case 11:
				buyCandy(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 12:
				returnMovie();
				printCust(true);
				wait();
				break;	
			case 13:
				returnMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 14:
				payOff();
				printCust(true);
				wait();
				break;
			case 15:
				payOff(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 16:
				saveCust();
				saveMovie();
				printCust(true);
				wait();
				break;
			case 17:
				sortCustByAge();
				saveCust();
				printCust(true);
				wait();
				break;
			case 18:
				return;
//				break;
			case 0:
				saveCust();
				saveMovie();
				break;
			default:
				cout << "Sorry but that's not an option";
				wait();
				break;
			}	
		}while(choice);
	} else if (customer[whichCustomer].privelege == 1) { // if customer is acually an employee
		do {
		system("cls");
			
		line();
		cout << "        Employee Options" << endl;
		line();
		cout << "1 - Profile" << endl
			 << "2 - Print the customers" << endl
			 << "3 - Print adults" << endl	
			 << "4 - Print Movies" << endl
			 << "5 - Rent movies for a customer" << endl
			 << "6 - Rent movies for yourself" << endl
			 << "7 - Buy Candy" << endl
			 << "8 - Buy Candy for yourself" << endl
			 << "9 - Have a person pay" << endl
			 << "10 - pay your bills" << endl
			 << "11 - Return movies" << endl
			 << "12 - return your movies" << endl
			 << "13 - Save the customers and Movies" << endl
			 << "14 - Sort the customers by age and Save" << endl
			 << "15 - Logout without Saving" << endl
			 << "0 - Save and Logout" << endl << endl << "Enter your choice : "; // change to save and exit
		cin >> choice;
		
		//Since we named our functions well, none of this needs commenting
		switch ( choice )
		{
			case 1:
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 2:
				printCust(true);
				wait();
				break;
			case 3:
				printAdult(true);
				wait();
				break;							
			case 4:
				printMovie();
				wait();
				break;
			case 5:
				rentMovie();
				printCust(true);
				wait();
				break;
			case 6:
				rentMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 7:
				buyCandy();
				printCust(true);
				wait();
				break;
			case 8:
				buyCandy(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 9:
				payOff();
				printCust(true);
				wait();
				break;
			case 10:
				payOff(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 11:
				returnMovie();
				printCust(true);
				wait();
				break;	
			case 12:
				returnMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 13:
				saveCust();
				saveMovie();
				printCust(true);
				wait();	
				break;
			case 14:
				sortCustByAge();
				saveCust();
				printCust(true);
				wait();
			case 15:
				return;
//				break;
			case 0:
				saveCust();
				saveMovie();
				break;
			default:
				cout << "Sorry but that's not an option";
				wait();
				break;
			}	
		}while(choice);
	} else if (customer[whichCustomer].privelege == 0) {
		do {
		system("cls");
			
		line();
		cout << "        Customer Options" << endl;
		line();
		cout << "1 - Profile" << endl
			 << "2 - Print Movies" << endl
			 << "3 - Rent movies" << endl		
			 << "4 - Buy snacks"	<< endl
			 << "5 - Pay debt" << endl
			 << "6 - Return movies" << endl		 
			 << "7 - Save" << endl
			 << "8 - Logout without Saving" << endl
			 << "0 - Save and Logout" << endl << endl << "Enter your choice : "; // change to save and exit
		cin >> choice;
		
		//Since we named our functions well, none of this needs commenting
		switch ( choice )
		{
			case 1:
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 2:
				printMovie();
				wait();
				break;
			case 3:
				rentMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 4:
				buyCandy(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 5:
				payOff(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;
			case 6:
				returnMovie(whichCustomer);
				printCust(true, whichCustomer, true);
				wait();
				break;				
			case 7:
				saveCust();
				saveMovie();
				wait();
				break;
			case 8:
				return;
//				break;
			case 0:
				saveCust();
				saveMovie();
				break;
			default:
				cout << "Sorry but that's not an option";
				wait();
				break;
			}	
		}while(choice);
	}
	
	return;
}
