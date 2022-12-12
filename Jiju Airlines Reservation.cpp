// 	Jiju Airlines Reservation v.1.1.0

#include <iostream> 	//library of standard input/output streams
#include <iomanip> 		//library containing functions manipluting outputs such as setw and setprecision
#include <cctype> 		//Library that declares a set of functions to classify and transform characters such as isalpha isspace
#include <ctime> 		//Library that contain functions to get and use date and time information based from the local system
#include <windows.h> 	//Library that contains declarations for all of the functions in the Windows API SetConsoleCursorPosition, SetConsoleCursor, gotoxy, GetAsyncKeyState
#include <string>		//Library that allows us to use and manipulate string data types

#pragma warning(disable: 4996)      //To disable IDE specific errors (Visual Studio, VS Code)
#pragma comment(lib, "User32.lib")  //To link Windows 32-bit library for windows.h 

using namespace std;

void gotoxy(int x, int y) //function to set cursor position to an exact coordinates based on the x and y axis of console/terminal
{
	COORD coord;
	coord.X = x;
	coord.Y = y;	//setting both x and y coordinate of cursor
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set the cursor on the coordinates
}

void Color(int color) //function to change color of text and backround
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ShowConsoleCursor(bool showCursor) //function to enable or disable cursor visibility
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo); //get current status of cursor
	cursorInfo.bVisible = showCursor; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool runAgain = false; //Used in the function below

void arrow_keys() { //Function to use arrow keys as input in yes or no inputs
	string logo = "\t\t\t\t\t  \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\t\t\t\t\t  \xba       \xdf\xdf\xdb \xdf\xdb\xdb\xdf  \xdf\xdf\xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba         \xdb  \xde\xdd     \xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba      \xdf\xdc\xdc\xdf \xdc\xdb\xdb\xdc \xdf\xdc\xdc\xdf \xdf\xdc\xdc\xdf      \xba\n \t\t\t\t\t  \xba A    I    R    L    I    N   E\xba\n\t\t\t\t\t  \xba     R E S E R V A T I O N S   \xba\n\t\t\t\t\t  \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc";
	bool running = true;
	char yn = ' ';
	gotoxy(50, 14);
	gotoxy(1, 14);
	ShowConsoleCursor(false); //make cursor invisible
	cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << "\x10YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl;
	yn = 'Y';
	gotoxy(54, 14);
	while (running) { //run a loop with a bool as a condition

		if (GetAsyncKeyState(VK_RIGHT)) { //detect if left arrow key is pressed
			ShowConsoleCursor(false); //make cursor invisible
			gotoxy(1, 14);
			cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES"; Color(241); cout << "      \x10NO" << "                     " << char(186) << endl; //moves arrow and highltght NO
			yn = 'N';
			gotoxy(63, 14);
            continue;
		}
		if (GetAsyncKeyState(VK_LEFT)) { //detect if right arrow key is pressed
			ShowConsoleCursor(false); //make cursor invisible
			gotoxy(1, 14);
			cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << "\x10YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl; //moves arrow and highltght YES
			yn = 'Y';
			gotoxy(54, 14);
            continue;
		}
		if (GetAsyncKeyState(VK_RETURN)) { //detect if enter key is pressed
			switch (yn) { //switch case of decision of user
			case 'y': case 'Y':
				system("cls");
				running = false; //sets bool value to false to stop loop
				gotoxy(1, 1);
				runAgain = true; //This is for last page of system
				break;
			case 'n': case 'N': // ends program if NO is the choice
				system("cls");
				cout << logo;
				cout << "\n\n\n\t\t\t\t\t      Thank You! And Goodbye!";
				Sleep(5000); //5 Second delay before program exits out
				exit(0);
				break;
			}
		}
	}
}

bool onlyAlpha(string name) { //function to check a string if it contains characters other than alphanumerics
	for (int z = 0; z < name.size(); z++) {
		if (!isalpha(name[z])) { 	//checks if a character of the string is not an alphanumeric
			if (isspace(name[z])) {		//if it's a space continue
				continue;
			}
			else					//else it contains invalid characters
				return false;
		}

	}
	return true;
}

bool inputValidation_passed(string input)  //function to validate whether string input contains unwanted characters
{
	bool valid_pass = true;
	if ((input[0] == '0' && isdigit(input[1]))) // Input can't start from 0
		valid_pass = false;
	else
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (isspace(input[i]) || !(isdigit(input[i])) || input[i] == '.') 
			// Checks and validates the input if it contains spaces, have alphabets, or contains '.'
				valid_pass = false;
		}
	}
	return valid_pass;
}

void dayPrompt() 	//function to print prompt if the day input is invalid
{
	gotoxy(1, 19);
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Invalid Day: "; Color(241); cout << setw(40) << char(186) << endl;
	gotoxy(58, 19);
}

void monthPrompt()	//function to print prompt if the month input is invalid
{
	gotoxy(1, 17);
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Invalid Month: "; Color(241); cout << setw(40) << char(186) << endl;
	gotoxy(58, 17);
}

void yearPrompt()	//function to print prompt if the year input is invalid
{
	gotoxy(1, 15);
	cout << "\t\t      " << char(186); Color(241); cout << setw(35) << "Invalid Year: "; Color(241); cout << setw(40) << char(186) << endl;
	gotoxy(58, 15);
}

void schedPrompt() //function to print prompt if the month input is invalid
{
	gotoxy(1, 41);
	cout << "\t\t\t\t      " << char(186); Color(240); cout << " INVALID Schedule, Please Re-Input:     "; Color(241); cout << char(186) << endl;
	gotoxy(75, 41);
}

void passengerPrompt() //function to print prompt if the passenger number input is invalid
{
	gotoxy(1, 11);
	cout << "\t\t\t " << char(186); Color(241); cout << setw(35) << "                           Please Retry"; Color(241); cout << setw(28) << char(186) << endl;
	gotoxy(1, 12);
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	gotoxy(1, 13);
	cout << "\t\t\t " << char(186); Color(240); cout << " And Enter an Approriate Number of Passenger Reservation (1-8):   "; Color(241); cout << char(186) << endl;
	gotoxy(90, 13);
}

//Input date layout
void screenDateInput()
{
	cout << "\t\t      " << char(204);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Year: "; Color(241); cout << setw(40) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Month: "; Color(241); cout << setw(40) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Day: "; Color(241); cout << setw(40) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(200);      for (int i = 0; i < 74; i++) { cout << char(205); }      cout << char(188) << endl;
}

// Loading Screen Layout
void loading() {
	ShowConsoleCursor(false);
	cout << "\n\n\n\n\n\t\t\t\t\t\xfe JIJU Airlines Reservations is Loading \xfe\n\n";
	char a = 177, b = 219;
	cout << "\t\t\t\t\t\t";
	for (int i = 0; i <= 22; i++)
		cout << a;
	cout << "\r";
	cout << "\t\t\t\t\t\t";
	for (int i = 0; i <= 22; i++)
	{
		cout << b;
		for (int j = 0; j <= 3e7; j++);
	}
	ShowConsoleCursor(true);
}

// Function to pause system momentarily 
void any_keypress() {
	Color(241);
	ShowConsoleCursor(false);
	cout << char(201);      for (int i = 0; i < 66; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186); Color(240); cout << "                     Press Any Key to Proceed  "; Color(241); cout << setw(20) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(200);      for (int i = 0; i < 66; i++) { cout << char(205); }      cout << char(188) << endl;
	system("pause>nul");
	system("cls");
}

struct fee //Structure for fee related variables
{
	double baggage[10], grossAmnt, final, vat, perPassenger[10];
	int payment;
}fee;
double ticketPrice;

void feeCalculation(int index) //Function to calculate fee per passenger
{
	fee.perPassenger[index] = fee.baggage[index] + ticketPrice;
}

//Main Function Of The Program
int main() {
    
	string schedTime, numPassngers_input, dateInput, destination, ageInput, baggageInput, payInput, logo = "\t\t\t\t\t  \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\t\t\t\t\t  \xba       \xdf\xdf\xdb \xdf\xdb\xdb\xdf  \xdf\xdf\xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba         \xdb  \xde\xdd     \xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba      \xdf\xdc\xdc\xdf \xdc\xdb\xdb\xdc \xdf\xdc\xdc\xdf \xdf\xdc\xdc\xdf      \xba\n \t\t\t\t\t  \xba A    I    R    L    I    N   E\xba\n\t\t\t\t\t  \xba     R E S E R V A T I O N S   \xba\n\t\t\t\t\t  \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc";

	struct date		//Structure for seperate date inputs
	{
		int year, rtYear, month, rtMonth, day, rtDay, hour, rtHour;
	}date;

	struct receipt	//Structure for each string to display in the receipt
	{
		string flightType, rtFlightType, destination, rtDestination, time, rtTime;
		int space;
	}receipt;

	struct passnger	//Sturcture of data for passenger details
	{
		int count, index = 0, age[10], baggage[10];
	}passenger;

	struct name		//structure containing the passengers name information
	{
		string surname[10], firstname[10], middle[10];
	}name;

	int flightType;
	char yn = 'x';
	bool running = true, passedValid = true;

	time_t timeNow = time(0); 				//Using ctime library, get current time from local system
	tm* localTime = localtime(&timeNow);

	// Input: Welcome Screen [Y/N]
	system("cls");
	system("color f1"); //Set the main color of text and backround of program to Light White Backround and Light Blue Texts
	cout << logo;
	cout << "\n\n\n\t\t\t\t" << char(201);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                     WELCOME                       "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "  WOULD YOU LIKE TO MAKE AN AIRLINE RESERVATION?   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES       NO                     "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(200);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(188) << endl;

	// Process: Reservation for L/R and Return Input
	arrow_keys();

	// Output: Loading Screen
	cout << logo;
	//do loading before program starts
	loading();
	system("cls");

	cout << logo;
	cout << "\n\n\t\t\t ";
	any_keypress();
	ShowConsoleCursor(true); //make cursor visible

	// Input: Type of Reservation [One-Way or Round-Trip]
	cout << logo;
	cout << "\n\n\n\n\t\t\t  " << char(201);  for (int i = 0; i < 63; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t\t  " << char(186) << "                                                               " << char(186) << endl;
	cout << "\t\t\t  " << char(186); Color(240); cout << "     WHAT TYPE OF RESERVATION WOULD YOU LIKE TO MAKE(1-2):     "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t  " << char(186) << "                                                               " << char(186) << endl;
	cout << "\t\t\t  " << char(204);  for (int i = 0; i < 31; i++) { cout << char(205); }  cout << char(203);  for (int i = 0; i < 31; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t\t  " << char(186) << "\t\t\t          " << char(186) << "\t\t\t          " << char(186) << endl;
	cout << "\t\t\t  " << char(186); Color(240); cout << "          (1) One-Way          "; Color(241); cout << char(186); Color(240); cout << "         (2)Round Trip         "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t  " << char(186) << "\t\t\t          " << char(186) << "\t\t\t          " << char(186) << endl;
	cout << "\t\t\t  " << char(200);  for (int i = 0; i < 31; i++) { cout << char(205); }  cout << char(202);  for (int i = 0; i < 31; i++) { cout << char(205); }  cout << char(188) << endl;
	gotoxy(1, 12);
	cout << "\t\t\t  " << char(186); Color(240); cout << "     WHAT TYPE OF RESERVATION WOULD YOU LIKE TO MAKE(1-2):     "; Color(241); cout << char(186) << endl;
	gotoxy(86, 12);
	cin >> flightType;

	// Process: Type of Reservation [Input Validation]
	while ((flightType != 2 && flightType != 1) || cin.fail()) 
	{ //Check input if it's other than 1 or 2
		gotoxy(1, 12);
		cout << "\t\t\t  " << char(186); Color(240); cout << "   INVALID INPUT, PLEASE RE-ENTER TYPE OF RESERVATION (1-2):   "; Color(241); cout << char(186) << endl;
		gotoxy(87, 12);
		flightType = 0;
		cin >> flightType;
	}

	if (flightType == 1) { //Set string of type of reservation to indicate in the reciept later on
		receipt.flightType = "One-Way";
	}
	else {
		receipt.flightType = "Round Trip";
	}

	system("cls");

	// Input: Destination Selection
	cout << logo;
	//Ask the user where will be the desired location of their booked flight, then prints all of available trip destinations
	cout << "\n\n\n\n\t\t\t\t      " << char(201);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t\t\t      " << char(186) << "            \xfe DESTINATIONS \xfe            " << char(186) << endl;
	cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 DOMESTIC FLIGHTS \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (A) \xb3 Batanes              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (B) \xb3 Bacolod              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (C) \xb3 Palawan              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (D) \xb3 Davao                "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "      Please Refer from the Above       "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << " And Enter Desired Destination(A - D):  "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(200);      for (int i = 0; i < 40; i++) { cout << char(205); }      cout << char(188) << endl;
	gotoxy(77, 23);
    cin.clear(); //Clear and ignore last input to not interfere next input of user
	cin.ignore(INT_MAX, '\n'); 
	getline(cin, destination); 	//Input of user, used getline because of string properties

	// Process: Destination Selection [Input Validation]
	while ((destination[0] > 'd' || destination[0] < 'a') && (destination[0] > 'D' || destination[0] < 'A') || (destination.length() != 1)) { //input validation if it only contains the letters A-D or it exceeds one character
		destination = ""; 	//Reset last input of user
		gotoxy(1, 23);
		cout << "\t\t\t\t      " << char(186); Color(240); cout << " INVALID Destination, Please Re-Input:  "; Color(241); cout << char(186) << endl;
		gotoxy(77, 23);
		getline(cin, destination);
	}

	// Process: Destination Selection [Ticket Pricing]
	switch (destination[0]) { 	//switch case to determine the price depending on destination picked by the user
	case 'a': case 'A':
		receipt.destination = "Batanes"; 	//receipt.destination is a string to refer to later for the receipt
		ticketPrice = 8650;					//sets the ticket price for the calculations
		break;
	case 'b': case 'B':
		receipt.destination = "Bacolod";
		ticketPrice = 4150;
		break;
	case 'c': case 'C':
		receipt.destination = "Palawan";
		ticketPrice = 3075;
		break;
	case 'd': case 'D':
		receipt.destination = "Davao";
		ticketPrice = 5452;
		break;
	}

	if (flightType == 2) //If two-way was picked by user, double the ticket price
		ticketPrice *= 2;

	system("cls");
	cout << logo;
	//Output: prints out and input of schedule of flight
	cout << "\n\n\n\t\t      " << char(201);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << "       When would you like your reservation flight to be scheduled?       "; Color(241); cout << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << "             Kindly indicate the Date of the Year, Month, Day.            "; Color(241); cout << char(186) << endl;
	screenDateInput();
	gotoxy(58, 15);
	getline(cin >> ws, dateInput); //input of year of schedule

	do	//loop to validate input
	{
		if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
		{
			yearPrompt(); //prompt user that input is not valid
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.year = stoi(dateInput); //Convert string input to int data type
		// Check whether value is not the expected year
		if ((date.year < (1900 + localTime -> tm_year) || date.year > (1901 + localTime->tm_year)))
		{
			yearPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
		}
		else
		{
			passedValid = true;
			break;
		}

	} while (!passedValid);

	gotoxy(44, 15);
	cout << "        Year: ";
	gotoxy(58, 17);
	dateInput.clear();
	getline(cin >> ws, dateInput); //Input of month of date schedule

	do	//loop to validate input
	{
		passedValid = true;
		if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
		{
			monthPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.month = stoi(dateInput); //Convert string input to int
		//Checks if the selected year is current year, then limits minimum month to current month
		if (date.year == localTime->tm_year + 1900 && (date.month < localTime->tm_mon + 1 || date.month > 12)) 
		{
			monthPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}
		//If not same year, then input can be between 1-12
		if (date.month < 1 || date.month > 12)
		{
			monthPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}
	} while (!passedValid);

	gotoxy(43, 17);
	cout << "        Month: ";
	gotoxy(58, 19);
	dateInput.clear();
	getline(cin >> ws, dateInput); //input of day of date schedule

	do //Loop to validate input
	{
		passedValid = true;
		if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
		{
			dayPrompt();
			dateInput = "";
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.day = stoi(dateInput); //Convert string input to int data type

		if (date.month == (localTime->tm_mon + 1) && date.year == (localTime->tm_year + 1900))
		{ //gets the value of month and year and whether it has the same date as today
			if (date.day < (localTime->tm_mday))
			{  //Selected day con't be any previous day
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
				continue;
			}

		}

		//Check first what month is the date, to indicate what is max day
		if(date.month == 1 || date.month == 3 || date.month == 5 || date.month == 8 || date.month == 10 || date.month == 12) //jan, mar, may, july, aug, oct, dec
		{
			if (date.day > 31) {	//day did not correspond to the max day of the month
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
			}
		}
		else if (date.month == 2) //feb
		{
			if (date.day > 28) {	//day did not correspond to the max day of the month
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
			}
		}
		else    //april, june, sept, nov
		{
			if (date.day > 30) {	//day did not correspond to the max day of the month
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
			}
		}
	} while (!passedValid);

	system("cls");
	cout << logo;
	//Output: prints all of available trip time destinations
	cout << "\n\n\n\n\t\t\t\t      " << char(201);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t\t\t      " << char(186) << "            \xfe ONWARD FLIGHT \xfe           " << char(186) << endl;
	cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 FLIGHT SCHEDULES \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (A) \xb3 12:00am              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (B) \xb3 2:00am               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (C) \xb3 4:00am               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (D) \xb3 6:00am               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (E) \xb3 8:00am               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (F) \xb3 10:00am              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (G) \xb3 12:00pm              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (H) \xb3 2:00pm               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (I) \xb3 4:00pm               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (J) \xb3 6:00pm               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (K) \xb3 8:00pm               "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (L) \xb3 10:00pm              "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "      Please Refer from the Above       "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(186); Color(240); cout << "    And Enter Desired Time (A - L):     "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t      " << char(200);      for (int i = 0; i < 40; i++) { cout << char(205); }      cout << char(188) << endl;
	gotoxy(75, 41);
	getline(cin >> ws, schedTime); //Input of departure time schedule

	do {
		passedValid = true; //Reset indicator if it passed validation

		while ((schedTime[0] > 'l' || schedTime[0] < 'a') && (schedTime[0] > 'L' || schedTime[0] < 'A') || (schedTime.length() != 1)) 
		{ //input validation if it only contains the letters A-L or it exceeds one character
			schedTime.clear();
			schedPrompt();
			getline(cin, schedTime);
			passedValid = false;
			continue;
		}

		switch (schedTime[0]) { //switch case to determine time
		case 'a': case 'A':
			receipt.time = "12:00am"; //Set string to display in receipt
			date.hour = 0; // 12am is 0 in 24 hr format
			break;

		case 'b': case 'B':
			receipt.time = "2:00am"; //Set string to display in receipt
			date.hour = 2; // 2am is 2 in 24 hr format
			break;

		case 'c': case 'C':
			receipt.time = "4:00am"; //Set string to display in receipt
			date.hour = 4; // 4am is 4 in 24 hr format
			break;

		case 'd': case 'D':
			receipt.time = "6:00am"; //Set string to display in receipt
			date.hour = 6; // 6am is 6 in 24 hr format
			break;

		case 'e': case 'E':
			receipt.time = "8:00am"; //Set string to display in receipt
			date.hour = 8; // 8am is 8 in 24 hr format
			break;

		case 'f': case 'F':
			receipt.time = "10:00am"; //Set string to display in receipt
			date.hour = 10; // 10am is 10 in 24 hr format
			break;

		case 'g': case 'G':
			receipt.time = "12:00pm"; //Set string to display in receipt
			date.hour = 12; // 12pm is 12 in 12 hr format
			break;

		case 'h': case 'H':
			receipt.time = "2:00pm"; //Set string to display in receipt 
			date.hour = 14; // 2pm is 14 in 24 hr format
			break;

		case 'i': case 'I':
			receipt.time = "4:00pm"; //Set string to display in receipt
			date.hour = 16; // 4pm is 16 in 24 hr format
			break;

		case 'j': case 'J':
			receipt.time = "6:00pm"; //Set string to display in receipt
			date.hour = 18; // 6pm is 18 in 24 hr format
			break;

		case 'k': case 'K':
			receipt.time = "8:00pm"; //Set string to display in receipt
			date.hour = 20; // 8pm is 20 in 24 hr format
			break;

		case 'l': case 'L':
			receipt.time = "10:00pm"; //Set string to display in receipt 
			date.hour = 22; // 10pm is 22 in 24 hr format
			break;
		}
        
		if (date.year == localTime->tm_year + 1900 && date.month == localTime->tm_mon + 1 && date.day == localTime->tm_mday && date.hour <= (localTime->tm_hour + 1))
		{
			passedValid = false;
			schedTime.clear();
			schedPrompt();
			getline(cin, schedTime);
		}
	} while (!passedValid);


	//Output: If selected type is two-way, ask the user when is their return date
	if (flightType == 2)
	{
		system("cls");
		cout << logo;
		//Output: input of schedule of return flight
		cout << "\n\n\n\t\t      " << char(201);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "         When would you like your Return flight to be scheduled?          "; Color(241); cout << char(186) << endl;
		cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "             Kindly indicate the Date of the Year, Month, Day.            "; Color(241); cout << char(186) << endl;
		screenDateInput();
		gotoxy(58, 15);
		getline(cin >> ws, dateInput); //Input of year of schedule

		do	//loop to validate input
		{
			passedValid = true;
			if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
			{
				yearPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}

			date.rtYear = stoi(dateInput);
			// check if input is less than or above the expected input
			if ((date.rtYear < date.year || date.rtYear > date.year + 1))
			{
				yearPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}
		} while (!passedValid);

		gotoxy(44, 15);
		cout << "        Year: ";
		gotoxy(58, 17);
		dateInput.clear();
		getline(cin >> ws, dateInput); //input of month of date schedule

		do	//loop to validate input
		{
			passedValid = true;
			if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
			{
				monthPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}

			date.rtMonth = stoi(dateInput);

			if (date.rtYear == localTime->tm_year + 1900 && (date.rtMonth < date.month || date.rtMonth > 12)) 
			{//check if the selected departure Year is current Year, and set the minimum return month to the selected departure month
				monthPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}

			if (date.rtMonth < 1 || date.rtMonth > 12) //If selected year is not current, then set input range to 1-12 
			{
				monthPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}
		} while (!passedValid);

		gotoxy(43, 17);
		cout << "        Month: ";
		gotoxy(58, 19);
		dateInput.clear();
		getline(cin >> ws, dateInput); //input of day of date schedule

		do
		{
			passedValid = true;
			if (!(inputValidation_passed(dateInput))) //Input validation of function that checks if input have unwanted characters
			{
				dayPrompt();
				dateInput = "";
				getline(cin >> ws, dateInput);
				passedValid = false;
				continue;
			}

			date.rtDay = stoi(dateInput); //Convert string input to int data type

			if (date.rtMonth == (localTime->tm_mon + 1) && date.rtYear == (localTime->tm_year + 1900))
			{ //gets the value of month and year and whether it has the same date as today
				if (date.rtDay <= date.day)
				{  //day con't be any previous day
					dayPrompt();
					dateInput.clear();
					getline(cin >> ws, dateInput);
					passedValid = 0;
					continue;
				}
			}
			//Check first what month is the date, to indicate what is max day
			if(date.rtMonth == 1 || date.rtMonth == 3 || date.rtMonth == 5 || date.rtMonth == 8 || date.rtMonth == 10 || date.rtMonth == 12) //jan, mar, may, july, aug, oct, dec
			{
				if (date.rtDay > 31) {	//day did not correspond to the max day of the month
					dayPrompt();
					dateInput.clear();
					getline(cin >> ws, dateInput);
					passedValid = 0;
				}
			}
			else if (date.rtMonth == 2) //feb
			{
				if (date.rtDay > 28) {	//day did not correspond to the max day of the month
					dayPrompt();
					dateInput.clear();
					getline(cin >> ws, dateInput);
					passedValid = 0;
				}
			}
			else    //april, june, sept, nov
			{
				if (date.rtDay > 30) {	//day did not correspond to the max day of the month
					dayPrompt();
					dateInput.clear();
					getline(cin >> ws, dateInput);
					passedValid = 0;
				}
			}
		} while (!passedValid);

		system("cls");
		cout << logo;
		//prints all of available trip time destinations
		cout << "\n\n\n\n\t\t\t\t      " << char(201);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t\t\t\t      " << char(186) << "            \xfe RETURN FLIGHT \xfe           " << char(186) << endl;
		cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 FLIGHT SCHEDULES \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (A) \xb3 12:00am              "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (B) \xb3 2:00am               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (C) \xb3 4:00am               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (D) \xb3 6:00am               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (E) \xb3 8:00am               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (F) \xb3 10:00am              "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (G) \xb3 12:00pm              "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (H) \xb3 2:00pm               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (I) \xb3 4:00pm               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (J) \xb3 6:00pm               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (K) \xb3 8:00pm               "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "                                        " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "             (L) \xb3 10:00pm              "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(204);  for (int i = 0; i < 40; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "      Please Refer from the Above       "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(186); Color(240); cout << "    And Enter Desired Time (A - L):     "; Color(241); cout << char(186) << endl;
		cout << "\t\t\t\t      " << char(200);      for (int i = 0; i < 40; i++) { cout << char(205); }      cout << char(188) << endl;
		gotoxy(75, 41);
		getline(cin >> ws, schedTime);

		do {
			passedValid = true; //Reset indicator if it passed validation

			while ((schedTime[0] > 'l' || schedTime[0] < 'a') && (schedTime[0] > 'L' || schedTime[0] < 'A') || (schedTime.length() != 1)) 
			{ //input validation if it only contains the letters A-L or it exceeds one character
				schedTime.clear();
				schedPrompt();
				getline(cin, schedTime);
				passedValid = false;
				continue;
			}

			switch (schedTime[0]) { //switch case to determine time
			case 'a': case 'A':
				receipt.rtTime = "12:00am"; //Set string to display in receipt
				date.rtHour = 0; // 12am is 0 in 24 hr format
				break;

			case 'b': case 'B':
				receipt.rtTime = "2:00am"; //Set string to display in receipt
				date.rtHour = 2; // 2am is 2 in 24 hr format
				break;

			case 'c': case 'C':
				receipt.rtTime = "4:00am"; //Set string to display in receipt
				date.rtHour = 4; // 4am is 4 in 24 hr format
				break;

			case 'd': case 'D':
				receipt.rtTime = "6:00am"; //Set string to display in receipt
				date.rtHour = 6; // 6am is 6 in 24 hr format
				break;

			case 'e': case 'E':
				receipt.rtTime = "8:00am"; //Set string to display in receipt
				date.rtHour = 8; // 8am is 8 in 24 hr format
				break;

			case 'f': case 'F':
				receipt.rtTime = "10:00am"; //Set string to display in receipt
				date.rtHour = 10; // 10am is 10 in 24 hr format
				break;

			case 'g': case 'G':
				receipt.rtTime = "12:00pm"; //Set string to display in receipt
				date.rtHour = 12; // 12pm is 12 in 12 hr format
				break;

			case 'h': case 'H':
				receipt.rtTime = "2:00pm"; //Set string to display in receipt 
				date.rtHour = 14; // 2pm is 14 in 24 hr format
				break;

			case 'i': case 'I':
				receipt.rtTime = "4:00pm"; //Set string to display in receipt
				date.rtHour = 16; // 4pm is 16 in 24 hr format
				break;

			case 'j': case 'J':
				receipt.rtTime = "6:00pm"; //Set string to display in receipt
				date.rtHour = 18; // 6pm is 18 in 24 hr format
				break;

			case 'k': case 'K':
				receipt.rtTime = "8:00pm"; //Set string to display in receipt
				date.rtHour = 20; // 8pm is 20 in 24 hr format
				break;

			case 'l': case 'L':
				receipt.rtTime = "10:00pm"; //Set string to display in receipt 
				date.rtHour = 22; // 10pm is 22 in 24 hr format
				break;
			}
		} while (!passedValid);
	}

	system("cls");
	cout << logo;
	// asks user how many passenger reservation
	cout << "\n\n\n\t\t\t ";
	cout << char(201);      for (int i = 0; i < 66; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186); Color(240); cout << "                Please State How Many Passengers:  "; Color(241); cout << setw(16) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
	cout << "\t\t\t " << char(200);      for (int i = 0; i < 66; i++) { cout << char(205); }      cout << char(188) << endl;
	gotoxy(76, 12);
	getline(cin >> ws, numPassngers_input); //Input of the no. of passenger

	do {
		passedValid = true;
		if (!(inputValidation_passed(numPassngers_input))) //Input validation of function that checks if input have unwanted characters
		{
			passengerPrompt();
			numPassngers_input.clear();
			getline(cin >> ws, numPassngers_input);
			passedValid = false;
			continue;
		}

		passenger.count = stoi(numPassngers_input); //Convert string input to int data type

		if (passenger.count < 1 || passenger.count > 8) //Setting maximum of passengers to 8 per booking
		{
			passengerPrompt();
			numPassngers_input.clear();
			getline(cin >> ws, numPassngers_input);
			passedValid = false;
			continue;
		}

	} while (!passedValid);


	do {
		passenger.index++; //Increment index, depending on what is the next number of passenger
		system("cls");
		cout << logo;
		cout << "\n\n\n\n\t\t      " << char(201);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t\t      " << char(186) << " \xfe Please Enter the Names and Corresponding Age of the Passengers Below \xfe " << char(186) << endl;
		cout << "\t\t      " << char(204);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t\t      " << char(186) << setw(40) << " \xfe PASSENGER " << passenger.index << " \xfe " << setw(31) << char(186) << endl;
		cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "                    Surname: "; Color(241); cout << setw(46) << char(186) << endl;
		cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "                 First Name: "; Color(241); cout << setw(46) << char(186) << endl;
		cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "             Middle Initial: "; Color(241); cout << setw(46) << char(186) << endl;
		cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "                        Age: "; Color(241); cout << setw(46) << char(186) << endl;
		cout << "\t\t      " << char(204);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t\t      " << char(186); Color(240); cout << "                        Baggage Weight (Kg): "; Color(241); cout << setw(30) << char(186) << endl;
		cout << "\t\t      " << char(200);      for (int i = 0; i < 74; i++) { cout << char(205); }      cout << char(188) << endl;
		gotoxy(52, 15);
		getline(cin >> ws, name.surname[passenger.index]); //Input of surname

		while (!(onlyAlpha(name.surname[passenger.index]))) //Check whether input contains only alphabets
		{
			gotoxy(1, 15);
			cout << "\t\t      " << char(186); Color(240); cout << "            Invalid Surname: "; Color(241); cout << setw(46) << char(186) << endl;
			gotoxy(52, 15);
			name.surname[passenger.index].clear();
			getline(cin >> ws, name.surname[passenger.index]);
		}

		gotoxy(1, 15);
		cout << "\t\t      " << char(186); Color(240); cout << "                    Surname: "; Color(241);
		gotoxy(52, 17);
		getline(cin >> ws, name.firstname[passenger.index]); //Input of firstname

		while (!(onlyAlpha(name.firstname[passenger.index]))) //Check whether input contains only alphabets
		{
			gotoxy(1, 17);
			cout << "\t\t      " << char(186); Color(240); cout << "         Invalid First Name: "; Color(241); cout << setw(46) << char(186) << endl;
			gotoxy(52, 17);
			name.firstname[passenger.index].clear();
			getline(cin >> ws, name.firstname[passenger.index]);
		}

		gotoxy(1, 17);
		cout << "\t\t      " << char(186); Color(240); cout << "                 First Name: "; Color(241);
		gotoxy(52, 19);
		getline(cin >> ws, name.middle[passenger.index]); //Input of middle initial

		while (!(onlyAlpha(name.middle[passenger.index]))) //Check whether input contains only alphabets
		{
			gotoxy(1, 19);
			cout << "\t\t      " << char(186); Color(240); cout << "        Invalid Middle Name: "; Color(241); cout << setw(46) << char(186) << endl;
			gotoxy(52, 19);
			name.middle[passenger.index].clear();
			getline(cin >> ws, name.middle[passenger.index]);
		}

		gotoxy(1, 19);
		cout << "\t\t      " << char(186); Color(240); cout << "             Middle Initial: "; Color(241);
		gotoxy(52, 21);
		getline(cin >> ws, ageInput); //Input of age per passenger

		do {
			passedValid = true;
			if (!inputValidation_passed(ageInput)) //Input validation of function that checks if input have unwanted characters
			{
				gotoxy(1, 21);
				cout << "\t\t      " << char(186); Color(240); cout << "                Invalid Age: "; Color(241); cout << setw(46) << char(186) << endl;
				gotoxy(52, 21);
				ageInput.clear();
				getline(cin >> ws, ageInput);
				passedValid = false;
				continue;
			}

			passenger.age[passenger.index] = stoi(ageInput);

			if (passenger.age[passenger.index] < 1 || passenger.age[passenger.index] > 120) //Set range of possible age from 1-120
			{
				gotoxy(1, 21);
				cout << "\t\t      " << char(186); Color(240); cout << "                Invalid Age: "; Color(241); cout << setw(46) << char(186) << endl;
				gotoxy(52, 21);
				ageInput.clear();
				getline(cin >> ws, ageInput);
				passedValid = false;
				continue;
			}

			bool haveMinors = false, haveAdults = false;

			if (passenger.age[passenger.index] <= 19)
			{
				haveMinors = true;
			}
			else
				haveAdults = true;

			if (passenger.index == passenger.count && !haveAdults)
			{
				gotoxy(1, 21);
				cout << "\t\t      " << char(186); Color(240); cout << "Must Have Atleast One Adult: "; Color(241); cout << setw(46) << char(186) << endl;
				gotoxy(52, 21);
				ageInput.clear();
				getline(cin >> ws, ageInput);
				passedValid = false;
				continue;
			}
		} while (!passedValid);

		gotoxy(1, 21);
		cout << "\t\t      " << char(186); Color(240); cout << "                        Age: "; Color(240);
		gotoxy(68, 23);
		getline(cin >> ws, baggageInput); //Input of baggage weight

		do {
			passedValid = true;
			if (!inputValidation_passed(baggageInput)) //Input validation of function that checks if input have unwanted characters
			{
				gotoxy(1, 23);
				cout << "\t\t      " << char(186); Color(240); cout << "                Invalid Baggage Weight (Kg): "; Color(241); cout << setw(30) << char(186) << endl;
				gotoxy(68, 23);
				baggageInput.clear();
				getline(cin >> ws, baggageInput);
				passedValid = false;
				continue;

			}

			passenger.baggage[passenger.index] = stoi(baggageInput); //Convert string input to int data type

			if (passenger.baggage[passenger.index] > 30 || passenger.baggage[passenger.index] < 1) //Vlidate whether baggage input is more than the max of 30kg
			{
				gotoxy(1, 23);
				cout << "\t\t      " << char(186); Color(240); cout << "                Invalid Baggage Weight (Kg): "; Color(241); cout << setw(30) << char(186) << endl;
				gotoxy(68, 23);
				baggageInput.clear();
				getline(cin >> ws, baggageInput);
				passedValid = false;
				continue;
			}
		} while (!passedValid);

		gotoxy(1, 23);
		cout << "\t\t      " << char(186); Color(240); cout << "                        Baggage Weight (Kg): "; Color(241); cout << endl;

		if (passenger.baggage[passenger.index] > 8) //Calculate the excess baggage fee per passenger
		{
			fee.baggage[passenger.index] = (passenger.baggage[passenger.index] - 8) * 200;
		}
		else
			fee.baggage[passenger.index] = 0;

		feeCalculation(passenger.index); //Calculation of per each passengers fee
		fee.grossAmnt += fee.perPassenger[passenger.index]; //Add up all passengers fee into gross amount

	} while (passenger.index != passenger.count);

	passenger.index = 1;

	fee.vat = fee.grossAmnt * .12; //Calculate VAT based on multiplying gross amount by 12%
	fee.final = fee.grossAmnt + fee.vat; //Calculate final due amount to pay, by adding VAT and Gross Amount

	cout << fixed << setprecision(2); //Setting max decimals to output during printing of Booking Summary

	// Output: Do Loading before showing the summary
	system("cls");
	cout << logo;
	loading();
	system("cls");

	//Output: prints out booking summary of reservation
	cout << logo;
	cout << "\n\n\n\t\t\t" << char(201);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t" << char(186) << "                         \xfe BOOKING SUMMARY \xfe                       " << char(186) << endl;
	cout << "\t\t\t" << char(204);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(185) << endl;
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 BOOKING DESTINATION \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "  \t\t    Manila --------TO--------    "; Color(241); cout << setw(20) << char(186) << endl;
	gotoxy(70, 13);
	cout << receipt.destination;
	gotoxy(1, 14);
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(204);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(185) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "  Departure Date: " << "\t\t\t\t   "; Color(241); cout << setw(18) << char(186) << endl;
	gotoxy(74, 16);
	cout << date.day << "/" << date.month << "/" << date.year << " " << receipt.time;

	receipt.space = 20; //Set coordinate y to set spaces using gotoxy depending on the contents of the receipt

	gotoxy(1, 17);

	if (flightType == 2) { //Display return date if two-way flight is selected
		cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << "     Return Date: " << "\t\t\t\t   "; Color(241); cout << setw(18) << char(186) << endl;
		gotoxy(74, 18);
		Color(240); cout << date.rtDay << "/" << date.rtMonth << "/" << date.rtYear << " " << receipt.rtTime; Color(241);
		gotoxy(1, 19);
		receipt.space += 2; //Add two spaces in the receipt
	}

	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186) << "                           \xfe PASSENGERS \xfe                          " << char(186) << endl;

	while (passenger.index <= passenger.count)
	{ //Prints out each passengers information and detailed computation of each passengers fee for transparency
		cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << " " << passenger.index << ". " << name.surname[passenger.index] << ", " << name.firstname[passenger.index] << " " << name.middle[passenger.index]; Color(241);
		gotoxy(92, receipt.space);
		cout << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << "     Trip Fare"; Color(241); cout << setw(54) << char(186) << endl;
		receipt.space++; //Adjust Spaces
		gotoxy(79, receipt.space);
		Color(240); cout << "P" << ticketPrice; Color(241); cout << endl;
		receipt.space++; //Adjust Spaces

		if (fee.baggage[passenger.index] != 0) { //prints if passenger has excess baggage
			cout << "\t\t\t" << char(186); Color(240); cout << "     Excess Baggage Fee"; Color(241); cout << setw(45) << char(186) << endl;
			gotoxy(79, receipt.space);
			Color(240); cout << "P" << fee.baggage[passenger.index]; Color(241); cout << endl;
			receipt.space++; //Adjust Spaces
		}

		cout << "\t\t\t" << char(186); Color(240); cout << " Total Passenger's Fee"; Color(241); cout << setw(46) << char(186) << endl; //prints out amount of each total passengers fee
		gotoxy(79, receipt.space);
		Color(240); cout << "P" << fee.perPassenger[passenger.index]; Color(241); cout << endl;
		receipt.space += 2; //Adjust spaces
		passenger.index++; //Increment index
	}

	receipt.space += 2; //Adjust space
	//Output: Indicate that there is a 12% VAT in the calculation
	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "        VAT +12%"; Color(241); cout << setw(52) << char(186) << endl;
	gotoxy(79, receipt.space);
	Color(240); cout << "P" << fee.vat; Color(241); cout << endl; //Print out the calculated VAt
	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "\tT O T A L\t\t\t\t              \t    "; Color(241); cout << char(186) << endl; //prints total amount due
	receipt.space += 4; //Adjust space
	gotoxy(79, receipt.space);
	Color(240); cout << "P" << fee.final; Color(241); cout << endl; //Print out the calculated final due amount
	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(200);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(188) << endl;
	
	//Pause program to let user evaluate the Booking Summary
	cout << "\n\n\t\t\t ";
	any_keypress();
	cout << logo;
	//Output: Payment window that displays final due amount, and asks the user to input paymnet
	cout << "\n\n\n\t\t      " << char(201);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << "\t\t\t               \xfe PAYMENT \xfe    \t                         "; Color(241); cout << char(186) << endl;
	cout << "\t\t      " << char(204);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(185) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Total: "; Color(241); cout << setw(40) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(37) << "Enter Payment: P "; Color(241); cout << setw(38) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Change: "; Color(241); cout << setw(40) << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(200);      for (int i = 0; i < 74; i++) { cout << char(205); }      cout << char(188) << endl;
	passenger.index += 4; //Adjust spaces
	gotoxy(58, 14);
	Color(240); cout << "P " << fee.final; Color(241); cout << endl; //Print out the calculated final due amount

	gotoxy(60, 16);
	getline(cin >> ws, payInput); //Input of payment

	//loop to validate whether input string has any other characters other than numeric
	do {
		passedValid = true;
		if (!(inputValidation_passed(payInput))) //Input validation of function that checks if input have unwanted characters
		{
			gotoxy(1, 16);
			cout << "                     " << char(186); Color(240); cout << setw(37) << "Invalid Payment: P "; Color(241); cout << setw(38) << char(186) << endl;
			gotoxy(60, 16);
			payInput.clear();
			getline(cin >> ws, payInput);
			passedValid = false;
			continue;
		}

		fee.payment = stoi(payInput); //Convert string input into int data

		if (fee.payment < fee.final) //If the etnered payment is less than the due amount, prompt user
		{
			gotoxy(1, 16);
			cout << "                     " << char(186); Color(240); cout << setw(37) << "Invalid Payment: P "; Color(241); cout << setw(38) << char(186) << endl;
			gotoxy(60, 16);
			payInput.clear();
			getline(cin >> ws, payInput);
			passedValid = false;
			continue;
		}

	} while (!passedValid);

	gotoxy(1, 16);
	cout << "\t\t      " << char(186); Color(240); cout << setw(37) << "      Payment: P ";

	if (fee.payment >= fee.final) //Calculate for change
	{
		gotoxy(50, 18);
		cout << "Change: " << "P " << fee.payment - fee.final;
	}

	//pause program so user can review or check the booking summary
	cout << "\n\n\n\n\t\t\t ";
	any_keypress();

	system("cls");
	// Output: Ask user if they want to book again
	cout << logo;
	cout << "\n\n\n\t\t\t\t" << char(201);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "        Thank You for Booking with JIJU!           "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "          Would You Like to Book Again?            "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES       NO                     "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(200);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(188) << endl;

	arrow_keys(); //Use arrow keys as input of Yes or No
	if(runAgain) //If user picks yes, then program reruns from int main()
		main();

	return 0;
}
