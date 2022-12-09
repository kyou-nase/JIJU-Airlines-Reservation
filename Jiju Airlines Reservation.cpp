// Jiju Airlines Reservation v.0.0.04

#include <iostream> 	//standard input/output streams
#include <iomanip> 	//setw
#include <cctype> 	//declares a set of functions to classify and transform characters
#include <ctime>	//Functions to get and use date and time information
#include <windows.h> 	//SetConsoleCursorPosition, SetConsoleCursor, gotoxy,GetAsyncKeyState
#include <sstream> 	//Stringstream
#include <string>
#pragma comment(lib, "User32.lib")
#pragma warning(disable: 4996)

using namespace std;

void gotoxy(int x, int y) //set cursor position to an exact coordinates based on the x and y axis of console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;	//setting both x and y coordinate of cursor
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set the cursor
}

void Color(int color) //function to change color of text and backround
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ShowConsoleCursor(bool showCursor) //function to enable or disable cursor
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo); //get current status of cursor
	cursorInfo.bVisible = showCursor; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo); 
}

void arrow_keys() {
	char yn = 'x';
	string logo = "\t\t\t\t\t  \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\t\t\t\t\t  \xba       \xdf\xdf\xdb \xdf\xdb\xdb\xdf  \xdf\xdf\xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba         \xdb  \xde\xdd     \xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba      \xdf\xdc\xdc\xdf \xdc\xdb\xdb\xdc \xdf\xdc\xdc\xdf \xdf\xdc\xdc\xdf      \xba\n \t\t\t\t\t  \xba A    I    R    L    I    N   E\xba\n\t\t\t\t\t  \xba     R E S E R V A T I O N S   \xba\n\t\t\t\t\t  \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc";
	bool running = true;

	gotoxy(50, 14);
	gotoxy(1, 14);
	ShowConsoleCursor(false); //make cursor invisible
	cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << ">YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl;
	yn = 'Y';
	gotoxy(54, 14);
	system("pause>nul");
	while (running) { //run a loop with a bool as a condition

		if (GetAsyncKeyState(VK_RIGHT)) { //detect if left arrow key is pressed
			gotoxy(1, 14);
			cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES"; Color(241); cout << "      >NO" << "                     " << char(186) << endl; //moves arrow and highltght NO
			yn = 'N';
			gotoxy(63, 14);
		}
		if (GetAsyncKeyState(VK_LEFT)) { //detect if right arrow key is pressed
			gotoxy(1, 14);
			cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << ">YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl; //moves arrow and highltght YES
			yn = 'Y';
			gotoxy(54, 14);
		}
		if (GetAsyncKeyState(VK_RETURN)) { //detect if enter key is pressed
			switch (yn) { //switch case of decision of user
			case 'y': case 'Y':
				system("cls");
				running = false; //sets bool value to false to stop loop
				gotoxy(1, 1);
				break;
			case 'n': case 'N': // ends program if NO isthe choice
				system("cls");
				cout << logo;
				cout << "\n\n\n\t\t\t\t\t      Thank You! And Goodbye!";
				exit;
				break;
			}
		}
	}
}

const std::string currentTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	return buf;
}

bool alpha(string name) { //function to check a string if it contains characters other than alphanumerics
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

void ignoreLine() //function to ignore last input of user for cin.fail()
{
    cin.clear();
    cin.ignore();
}

bool inputValidation_passed(string input)
{
    bool valid_pass = true;
    if ((input[0] == '0' && isdigit(input[1]))) // input can't start from 0
        valid_pass = false;
    else
    {
        for (int i = 0; i < input.size(); i++)
        {
            if (isspace(input[i]) || !(isdigit(input[i])) || input[i] == '.') // Checks and validates the input if it contains spaces, starts from 0, or contains '.'
                valid_pass = false;
        }
    }
    return valid_pass;
}

void dayPrompt() //function to print prompt if the day input is invalid
{
	gotoxy(1, 19);
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Invalid Day: "; Color(241); cout << setw(40) << char(186) << endl;
	gotoxy(58, 19);
}

void monthPrompt()
{
	gotoxy(1, 17);
	cout << "\t\t      " << char(186); Color(240); cout << setw(35) << "Invalid Month: "; Color(241); cout << setw(40) << char(186) << endl;
	gotoxy(58, 17);
}

void yearPrompt()    //function to print prompt if the year input is invalid
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
}

// Press Any Key to Proceed
void any_keypress() {
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

int main() {
	string schedTime, num_of_passengers, dateInput, receipt_flightType, destination, receipt_destination, logo = "\t\t\t\t\t  \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\t\t\t\t\t  \xba       \xdf\xdf\xdb \xdf\xdb\xdb\xdf  \xdf\xdf\xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba         \xdb  \xde\xdd     \xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba      \xdf\xdc\xdc\xdf \xdc\xdb\xdb\xdc \xdf\xdc\xdc\xdf \xdf\xdc\xdc\xdf      \xba\n \t\t\t\t\t  \xba A    I    R    L    I    N   E\xba\n\t\t\t\t\t  \xba     R E S E R V A T I O N S   \xba\n\t\t\t\t\t  \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc";
	struct date	//Structure for seperate date inputs
	{
		int year, month, day, hour;
	} date;
	struct receipt	//Structure for each string to display in the receipt
	{
		string flightType, destination, time;
	} receipt;

	int x, flightType;
	double ticketPrice;
	char yn = 'x';
	bool running = true, passedValid = true;
	stringstream convertString(dateInput);

	time_t timeNow = time(0); 				//get current time from local system
	tm* localTime = localtime(&timeNow);

	// Input: Welcome Screen [Y/N]
	system("color f1"); //set the main color of text and backround of program
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
	//do loading berfore program starts
	loading();
	system("cls");

	// Input: Press any Key to Proceed
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
	while ((flightType != 2 && flightType != 1) || cin.fail()) {
		ignoreLine();
		gotoxy(1, 12);
		cout << "\t\t\t  " << char(186); Color(240); cout << "   INVALID INPUT, PLEASE RE-ENTER TYPE OF RESERVATION (1-2):   "; Color(241); cout << char(186) << endl;
		gotoxy(87, 12);
		flightType = 0;
		cin >> flightType;
	}

	if (flightType == 1) { //Set string to indicate in reciept later on
		receipt_flightType = "One-Way";
	}
	else {
		receipt_flightType = "Round Trip";
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
	ignoreLine();
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
		receipt_destination = "Batanes"; 	//receipt_destination is a string to refer to later for the receipt
		ticketPrice = 8650;			//sets the ticket price for the calculations
		break;
	case 'b': case 'B':
		receipt_destination = "Bacolod";
		ticketPrice = 4543;
		break;
	case 'c': case 'C':
		receipt_destination = "Palawan";
		ticketPrice = 5882;
		break;
	case 'd': case 'D':
		receipt_destination = "Davao";
		ticketPrice = 4096;
		break;
	}

	// Input: Date Schedule 
	system("cls");
	cout << logo;
	//prints out and input of schedule of flight
	cout << "\n\n\n\t\t      " << char(201);  for (int i = 0; i < 74; i++) { cout << char(205); }  cout << char(187) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << "       When would you like your reservation flight to be scheduled?       "; Color(241); cout << char(186) << endl;
	cout << "\t\t      " << char(186) << setw(75) << char(186) << endl;
	cout << "\t\t      " << char(186); Color(240); cout << "             Kindly indicate the Date of the Year, Month, Day.            "; Color(241); cout << char(186) << endl;
	screenDateInput();
	gotoxy(58, 15);
	getline(cin >> ws, dateInput); //input of year of schedule

	do	//loop to validate input
	{
		if (!(inputValidation_passed(dateInput)))
		{
			yearPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.year = stoi(dateInput);
		// Check whether input did not pass input validation or value is not the expected year
		if ((date.year < (1900 + localTime->tm_year) || date.year >(1901 + localTime->tm_year)))
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
	getline(cin >> ws, dateInput); //input of month of date schedule

	do	//loop to validate input
	{
		passedValid = true;
		if (!(inputValidation_passed(dateInput)))
		{
			monthPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.month = stoi(dateInput);

		if (date.year == localTime->tm_year + 1900 && (date.month < localTime->tm_mon + 1 || date.month > 12)) //check if the selected year is current year
		{
			monthPrompt();
			dateInput.clear();
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

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

	do
	{
		passedValid = true;
		if (!(inputValidation_passed(dateInput)))
		{
			dayPrompt();
			dateInput = "";
			getline(cin >> ws, dateInput);
			passedValid = false;
			continue;
		}

		date.day = stoi(dateInput);

		if (date.month == (localTime->tm_mon + 1) && date.year == (localTime->tm_year + 1900))
		{ //gets the value of month and year and whether it has the same date as today
			if (date.day < (localTime->tm_mday))
			{  //day con't be any previous day
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
				continue;
			}
		}

		switch (date.month) {		//check first what month is the date
		case 1: case 3: case 5: case 8: case 10: case 12: //jan, mar, may, july, aug, oct, dec
			if (date.day > 31) {	//day did not correspond to the max day of the month
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
			}
		case 2: //feb
			if (date.day > 28) {	//day did not correspond to the max day of the month
				dayPrompt();
				dateInput.clear();
				getline(cin >> ws, dateInput);
				passedValid = 0;
			}
		case 4: case 6: case 7: case 9: case 11: //april, june, sept, nov
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
	//prints all of available trip time destinations
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
	getline(cin >> ws, schedTime);

	do {
		passedValid = true; // Reset indicator if it passed validation

		while ((schedTime[0] > 'l' || schedTime[0] < 'a') && (schedTime[0] > 'L' || schedTime[0] < 'A') || (schedTime.length() != 1)) { //input validation if it only contains the letters A-L or it exceeds one character
			schedTime = "";
			schedPrompt();
			getline(cin, schedTime);
			passedValid = false;
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
		if (date.year == localTime->tm_year + 1900 && date.month == localTime->tm_mon + 1 && date.day == localTime->tm_mday && date.hour >= (localTime->tm_hour + 1))
		{
			passedValid = false;
			schedTime = "";
			schedPrompt();
			ignoreLine();
			getline(cin, schedTime);
		}
		else {
			passedValid = true;
		}
	} while (!passedValid);


	// STILL IN DEVELOPMENT
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
	getline(cin >> ws, num_of_passengers); //input of the no. of passenger
	do {
		stringstream convertString(num_of_passengers);
		convertString >> num_of_passengers;
		if (!(inputValidation_passed(num_of_passengers)))
		{
			gotoxy(1, 11);
			cout << "\t\t\t " << char(186); Color(241); cout << setw(35) << "                           Please Retry"; Color(241); cout << setw(28) << char(186) << endl;
			gotoxy(1, 12);
			cout << "\t\t\t " << char(186) << setw(67) << char(186) << endl;
			gotoxy(1, 13);
			cout << "\t\t\t " << char(186); Color(240); cout << " And Enter an Approriate Number of Passenger Reservation(1-10):   "; Color(241); cout << char(186) << endl;
			gotoxy(90, 13);
			num_of_passengers = "";
			getline(cin >> ws, num_of_passengers);
			passedValid = false;
		}
		else {
			passedValid = true;
			break;
		}

	}
	while (!passedValid);



	// IGNORE THIS LINE FIRST(WILL BE USED IN THE LAST SECTION)
	//pause program so user can review or check the booking summary
	system("cls");
	//prints out booking summary of reservation
	cout << logo;
	cout << "\n\n\n\t\t\t" << char(201);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t" << char(186) << "                         \xfe BOOKING SUMMARY \xfe                       " << char(186) << endl;
	cout << "\t\t\t" << char(204);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(185) << endl;
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 BOOKING DESTINATION \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "  \t\t    Manila --------TO--------    "; Color(241); cout << setw(20) << char(186) << endl;
	gotoxy(70, 13);
	cout << receipt_destination;
	gotoxy(1, 14);
	cout << "\t\t\t" << char(186) << "\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0" << char(186) << endl;
	cout << "\t\t\t" << char(204);      for (int i = 0; i < 67; i++) { cout << char(205); }      cout << char(185) << endl;
	cout << "\t\t\t" << char(186); Color(240); cout << "  Departure Date: " << "\t\t\t\t   "; Color(241); cout << setw(18) << char(186) << endl;
	gotoxy(78, 16);
	cout << date.day << "/" << date.month << "/" << date.year;

	/*
	gotoxy(1, 17);
	x = 20;
	if (flightType == '2') { //display return date if two-way flight
		cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << "     Return Date: " << "\t\t\t\t   "; Color(241); cout << setw(18) << char(186) << endl;
		gotoxy(78, 18);
		Color(240); cout << day1 << "/" << month1 << "/" << year1; Color(241);
		gotoxy(1, 19);
		x += 2;
	}

	cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
	cout << "\t\t\t" << char(186) << "                           \xfe PASSENGERS \xfe                          " << char(186) << endl;
	while (ctr1 != pssngr) { //prints out each passengers details and computation for their corresponding passengers fee
		cout << "\t\t\t" << char(186) << "   \t\t\t\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << " " << index1 << ". " << surname[index1] << ", " << frstname[index1] << " " << mi[index1]; Color(241);
		gotoxy(92, x);
		cout << char(186) << endl;
		cout << "\t\t\t" << char(186); Color(240); cout << "     Trip Fare"; Color(241); cout << setw(54) << char(186) << endl;
		x++;
		
		gotoxy(79, x);
		Color(240); cout << "P" << ticketPrice; Color(241); cout << endl;
		x++;

		if (BaggageFee[index1] != 0) { //prints if passenger has excess baggage
			cout << "\t\t\t" << char(186); Color(240); cout << "     Excess Baggage Fee"; Color(241); cout << setw(45) << char(186) << endl;
			gotoxy(79, x);
			Color(240); cout << "P" << BaggageFee[index1]; Color(241); cout << endl;
			x++;
		}
		cout << "\t\t\t" << char(186); Color(240); cout << " Total Passenger's Fee"; Color(241); cout << setw(46) << char(186) << endl; //prints out amount of each total passengers fee
		gotoxy(79, x);
		Color(240); cout << "P" << pssngr_fee[index2]; Color(241); cout << endl;
		x += 2;
		++ctr1;
		++index1;
		++index2;
		++index3;
	}
	*/

	// pause program so user can review or check the booking summary
	cout << "\n\n\t\t\t ";
	any_keypress();

	// Output: Book Again
	cout << logo;
	cout << "\n\n\n\t\t\t\t" << char(201);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(187) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "        Thank You for Booking with JIJU!           "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "          Would You Like to Book Again?            "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES       NO                     "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(186); Color(240); cout << "                                                   "; Color(241); cout << char(186) << endl;
	cout << "\t\t\t\t" << char(200);      for (int i = 0; i < 51; i++) { cout << char(205); }      cout << char(188) << endl;
	arrow_keys();
}