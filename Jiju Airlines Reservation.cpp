// Jiju Airlines Reservation v.0.0.01

#include <iostream> 	//standard input/output streams
#include <iomanip> 	//setw
#include <cctype> 	//declares a set of functions to classify and transform characters
#include <ctime>	//Functions to get and use date and time information
#include <windows.h> 	//SetConsoleCursorPosition, SetConsoleCursor, gotoxy,GetAsyncKeyState
#include <sstream> 	//Stringstream
#include <string>
#pragma comment(lib, "User32.lib")

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

bool input_validation(string input)
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

int main() {
	string receipt_flighttype, logo = "\t\t\t\t\t  \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\t\t\t\t\t  \xba       \xdf\xdf\xdb \xdf\xdb\xdb\xdf  \xdf\xdf\xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba         \xdb  \xde\xdd     \xdb \xdb  \xdb      \xba\n   \t\t\t\t\t  \xba      \xdf\xdc\xdc\xdf \xdc\xdb\xdb\xdc \xdf\xdc\xdc\xdf \xdf\xdc\xdc\xdf      \xba\n \t\t\t\t\t  \xba A    I    R    L    I    N   E\xba\n\t\t\t\t\t  \xba     R E S E R V A T I O N S   \xba\n\t\t\t\t\t  \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc";
	int x; 
	char yn = 'x', flighttype[1000];
	bool running = true;

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
	gotoxy(50, 14);
	gotoxy(1, 14);
	ShowConsoleCursor(false); //make cursor invisible
	cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << "\x10YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl;
	yn = 'Y';
	gotoxy(54, 14);

	system("pause>nul");
	while (running) { //run a loop with a bool as a condition

		if (GetAsyncKeyState(VK_RIGHT)) { //detect if left arrow key is pressed
			gotoxy(1, 14);
			cout << "\t\t\t\t" << char(186); Color(240); cout << "                  YES"; Color(241); cout << "      \x10NO" << "                     " << char(186) << endl; //moves arrow and highltght NO
			yn = 'N';
			gotoxy(63, 14);
		}
		if (GetAsyncKeyState(VK_LEFT)) { //detect if right arrow key is pressed
			gotoxy(1, 14);
			cout << "\t\t\t\t"; Color(241); cout << char(186) << "                 " << "\x10YES"; Color(240); cout << "       NO                     "; Color(241); cout << char(186) << endl; //moves arrow and highltght YES
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
				cout << "\n\n\n\t\t\t\t\t      Thank You! And Goodbye!\n\n\n";
				return 0;
				break;
			}
		}
	}
    cout << logo;
	//do loading berfore program starts
	cout<<"\n\n\n\n\n\t\t\t\t\t\xfe JIJU Airlines Reservations is Loading \xfe\n\n";
	char a=177, b=219;
	cout<<"\t\t\t\t\t\t";
	for (int i=0;i<=22;i++)
	cout<<a;
	cout<<"\r";
	cout<<"\t\t\t\t\t\t";
	for (int i=0;i<=22;i++)
	{
		cout<<b;
	  	for (int j=0;j<=3e7;j++);
	}
	system("cls");
	
	cout << logo;
	cout << "\n\n\t\t\t ";
	cout << char(201);      for(int i=0; i<66; i++){cout << char(205);}      cout << char(187) << endl;
	cout <<"\t\t\t "<< char(186) << setw(67) << char(186) << endl;
	cout <<"\t\t\t "<< char(186) << setw(67) << char(186) << endl;
	cout <<"\t\t\t "<< char(186) ;Color(240);cout << "                     Press Any Key to Proceed  ";Color(241);cout <<setw(20) << char(186) << endl;
	cout <<"\t\t\t "<< char(186) << setw(67) << char(186) << endl;
	cout <<"\t\t\t "<< char(186) << setw(67) << char(186) << endl;
	cout <<"\t\t\t "<< char(200);      for(int i=0; i<66; i++){cout << char(205);}      cout << char(188) << endl;
	system("pause>nul");
	system("cls");
	ShowConsoleCursor(true); //make cursor visible

	cout << logo;
    cout << "\n\n\n\n\t\t\t  "<< char(201);  for(int i=0; i<63; i++){cout << char(205);}  cout << char(187)<<endl;
	cout << "\t\t\t  "<< char(186) << "                                                               " << char(186) << endl;
	cout << "\t\t\t  "<< char(186) ;Color(240);cout << "     WHAT TYPE OF RESERVATION WOULD YOU LIKE TO MAKE(1-2):     " ;Color(241);cout << char(186) << endl;
	cout << "\t\t\t  "<< char(186) << "                                                               " << char(186) << endl;
	cout << "\t\t\t  "<< char(204);  for(int i=0; i<31; i++){cout << char(205);}  cout << char(203);  for(int i=0; i<31; i++){cout << char(205);}  cout << char(185) << endl;
	cout << "\t\t\t  "<< char(186) << "\t\t\t          " << char(186) << "\t\t\t          " << char(186) << endl;
	cout << "\t\t\t  "<< char(186) ;Color(240);cout << "          (1) One-Way          " ;Color(241);cout << char(186) ;Color(240);cout << "         (2)Round Trip         " ;Color(241);cout << char(186) << endl;
	cout << "\t\t\t  "<< char(186) << "\t\t\t          " << char(186) << "\t\t\t          " << char(186) << endl;
	cout << "\t\t\t  "<< char(200);  for(int i=0; i<31; i++){cout << char(205);}  cout << char(202);  for(int i=0; i<31; i++){cout << char(205);}  cout << char(188) << endl;
	gotoxy (1, 12);
	cout << "\t\t\t  "<< char(186) ;Color(240);cout << "     WHAT TYPE OF RESERVATION WOULD YOU LIKE TO MAKE(1-2):     " ;Color(241);cout << char(186) << endl;
	gotoxy (86, 12);
    cin >> flighttype;

    while (flighttype[0] != '2'&&flighttype[0] != '1'||flighttype[1]>0){ //Input Validation
		gotoxy(1, 12);
		cout << "\t\t\t  "<< char(186) ;Color(240);cout << "   INVALID INPUT, PLEASE RE-ENTER TYPE OF RESERVATION (1-2):   " ;Color(241);cout << char(186) << endl;
		gotoxy(87, 12);
		flighttype[1]=0;
		cin >> flighttype;
	}

	if (flighttype[0] == '1'){ //Set string to indicate in reciept later on
		receipt_flighttype = "One-Way";
	}
	else {
		receipt_flighttype = "Round Trip";
	}
	system("cls");
}
