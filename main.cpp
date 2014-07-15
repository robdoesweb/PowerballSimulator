// File Name: A6russellr.cpp
// Written by: Robert Russell
// Description: Final Project, PowerBall.  Generates 5 random numbers between 1 and 59 and 1 PowerBall between
// 1 and 35.  Asks user to pick same format of numbers and matches based on the rules of the PowerBall lottery
// game.
// Challenges: Generating Random Numbers, Comparing two different sets of numbers with different rules.
// Time Spent: Approx 10 hours
// Given Input: (3 sets)         Expected Output: (3 corresponding sets)
// --------------------          -------------------------
// 1) t , 1 2 3 4 5 6            Your Numbers: 1, 2, 3, 4, 5, PowerBall: 6
//								 PowerBall Numbers: ##, ##, ##, ##, ##, PowerBall: ##
//								 You need to match at least the powerball or three white balls to win.
// Revision History
// Date:        Revised By:     Action:
// ------------------------------------------------------------------
// 4/28			RSR				Wrote inArray, printArray functions
// 4/30         RSR             Added in function definitions, tested random numbers
// 5/4          RSR				Finished.
// 5/6          RSR             Fixed srand, added odds of winning, changed powerball to 1-35, fix modulus statement, fix calling GeneratePowerball() twice

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <string.h>

using namespace std;

void displayMenu();

void back();

int randomNum(int, int);

void DisplayInstructions ( );  
//(5 points)
//DisplayInstructions will display a description of the game, how to play, and how to win.

void GetPlayerSelections (int *);  
//(15 points)
// GetPlayerSelections is passed an array.  It will ask the player for input.  
// Player selects 5 numbers from 1-59, and 1 number from 1-35 for the last number.
// Do not allow the player to enter duplicate numbers for the first 5 numbers. (Keep looping until they have selected 6 acceptable numbers.)  Store the player’s selections in the array.

void GeneratePowerball (int *);  
// (15 points)
// GeneratePowerball is passed an array.  
// It randomly generates the 6 numbers according to the rules above and fills the array with these numbers.  
// Make sure there are no duplicates in the first 5 numbers.

int CheckForWin (int *, int *, int); 
// (30 points)
// CheckForWin is passed the two arrays.  
// It displays the Player’s Selections and the Powerball Numbers.
// It returns an integer 1-9 that represents one of the winning combinations or returns 0 for no win.  
// Remember that the numbers do not have to be in order to win.

void reset(int *);
//sets all items in array to 0

int DisplayPrize (int );  
//(15 points)
// DisplayPrize takes an integer from 0-9 and displays whether it’s a win or a loss, what the prize is and what the odds are of winning that prize. 
// It returns the amount won (0 if no win).

void printArr(int *arr, int elem);
//prints a passed array

void copyArray(int *array1, int *array2, int elem);
//copies first array into second arrray

//number of balls
const int NUMBALLZ = 6;

//debug global
int debug = 0;

//screen colors
const char green[] = "Color 27";
const char red[] = "Color 47";
const char l1[] = "Color 71";
const char l2[] = "Color 78";




int main() {

	system(l2);
	system("Color 34");
	int playerBalance = 0;
	int PlayerNumbers[] = {0,0,0,0,0,0};
	int WinningNumbers[] = {0,0,0,0,0,0};
	int *playerPB = &PlayerNumbers[5];
	int *winningPB = &WinningNumbers[5];
	int matches = 0;
	srand(time(NULL));

	displayMenu();
	bool done = false;
	while (done == false) {
		char choice = 'k';
		cin >> choice;
		choice = toupper(choice);
		switch (choice) {
			case 'k':
				cout << "Please choose a menu option.";
				back();
			break;

			case 'I':
				system(l2);
				DisplayInstructions();
				back();
			break;

			case 'T':
				reset(PlayerNumbers);
				reset(WinningNumbers);
				playerBalance -= 2;
				GeneratePowerball(WinningNumbers);
				if (debug == 1) {
					cout << "\n\nGenerated numbers: ";
					printArr(WinningNumbers, 6);
				}
				GetPlayerSelections(PlayerNumbers);
				system("cls");
				cout << "\nYour Numbers: \n";
				printArr(PlayerNumbers, 6);
				cout << "\nPowerBall Numbers: \n";
				printArr(WinningNumbers, 6);
				matches = CheckForWin(PlayerNumbers, WinningNumbers, NUMBALLZ);
				playerBalance += DisplayPrize(matches);
				back();
			break;

			case 'B':
				cout << "\n\nYou're balance is: $" << playerBalance << endl;
				back();
			break;

			case 'X':
				done = true;
			break;

			default:
				cout << "\nPlease choose a letter.";
				back();
			break;
		}
	}
	system("PAUSE");
}

void reset(int *arr) {
	int *nPt;
	nPt = arr + NUMBALLZ; //one past last elem
	while (arr < nPt) {
		*arr = 0;
		arr++;
	}
}

void displayMenu() {
	system("Color 34");
	cout << "\n************************POWERBALL************************\n" << endl;
	cout << "                          MENU                           \n" << endl;
	cout << "[i] Instructions\n[t] New Ticket\n[b] View Balance\n[x] Exit" << endl;
	cout << "\n\nEnter your choice and press return: ";
}

void back() {
	//clear the screen and return to main menu
	system("PAUSE");
	system("cls");
	displayMenu();
}

void DisplayInstructions() {
	system("cls");

	cout << "************************POWERBALL************************\n" <<endl ;
	cout << "Players win by matching one of these 9 Ways to Win:\n" ;

	cout << setw(26) << "Match all 5 + PowerBall =" << setw(12) << " Grand Prize\n" ;
	cout << "Odds: 1 in 175,223,510.00\n\n";

	cout << setw(26) << "Match 5 =" << setw(12) << " $1,000,000\n" ;
	cout << "Odds: 1 in 5,153,632.65\n\n";

	cout << setw(26) << "Match 4 + PowerBall =" << setw(12) << " $10,000\n";
	cout << "Odds: 1 in 648,975.96\n\n";

	cout << setw(26) << "Match 4 =" << setw(12) << " $100\n" ;
	cout << "Odds: 1 in 19,087.53\n\n";

	cout << setw(26) << "Match 3 + PowerBall =" << setw(12) << " $100\n" ;
	cout << "Odds: 1 in 12,244.83\n\n";

	cout << setw(26) << "Match 3 =" << setw(12) << " $7\n" ;
	cout << "Odds: 1 in 360.14\n\n";

	cout << setw(26) << "Match 2 + PowerBall =" << setw(12) << " $7\n" ;
	cout << "Odds: 1 in 706.43\n\n";

	cout << setw(26) << "Match 1 + PowerBall =" << setw(12) << " $4\n" ;
	cout << "Odds: 1 in 110.81\n\n";

	cout << setw(26) << "Match PowerBall" << setw(12) << " $4\n" ;
	cout << "Odds: 1 in 55.41\n\n";
}

int randomNum(int min, int max) {
	int rand1 = rand() % max + 1;
}

//this works. 4/29
int inArray(int Value, int *arr, int sizeOf) {
	//cout << "\nCalled inArray(" << Value << ", " << *arr << ", " << sizeOf << ")";
	int numOf = 0;

	for (int i = 0; i < sizeOf; i++) {
		if (Value == *arr) {
			numOf++;
			//cout << "\n Array Value:" << *arr << " == " << Value << " Value";
		} else {
			arr++;
		}
	}

	return numOf;
}


//this works. 4/29
int CheckForWin (int *pSelect, int *generated, int sizeOf) {
	int winCode = 0;
	int numOfMatches = 0;
	int *oPt = pSelect;
	int playerPB = *(pSelect + 5);
	int winningPB = *(generated + 5);

	if (debug == 1) {
		cout << "\nPlayerPB = " << playerPB;
		cout << "\nwinningPB = " << winningPB;
	}

	for (int i = 0; i < (sizeOf - 1); i++) {
		if (inArray(*pSelect, generated, sizeOf - 1) != 0) {
			numOfMatches++;
		}

		pSelect++;
	}

	switch (numOfMatches) {
		case 0:
			if (playerPB == winningPB) {
				winCode = 1;
			} else {
				winCode = 0;
			}
		break;

		case 1:
			if (playerPB == winningPB) {
				winCode = 2;
			} else {
				winCode = 0;
			}
		break;

		case 2:
			if (playerPB == winningPB) {
				winCode = 3;
			} else {
				winCode = 0;
			}
		break;

		case 3:
			if (playerPB == winningPB) {
				winCode = 5;
			} else {
				winCode = 4;
			}
		break;

		case 4:
			if (playerPB == winningPB) {
				winCode = 7;
			} else {
				winCode = 6;
			}
		break;

		case 5:
			if (playerPB == winningPB) {
				winCode = 9;
			} else {
				winCode = 8;
			}
		break;
	}

return winCode;

	
}



int DisplayPrize(int winCode) {
	if (winCode > 0) {
		system(green);
		cout <<"\n\nYou Won!!!\n\n";
	}
	switch (winCode) {
		case 0:
			system(red);
			cout << "\nYou need to match at least the powerball or three white balls to win.\n";
			return 0;
		break;

		case 1:
			cout << setw(26) << "Match PowerBall" << setw(12) << " $4\n";
			cout << "Odds: 1 in 55.41\n";
			return 4;
		break;

		case 2:
			cout << setw(26) << "Match 1 + PowerBall =" << setw(12) << " $4\n";
			cout << "Odds: 1 in 110.81\n";
			return 4;
		break;

		case 3:
			cout << setw(26) << "Match 2 + PowerBall =" << setw(12) << " $7\n";
			cout << "Odds: 1 in 706.43\n";
			return 7;
		break;

		case 4:
			cout << setw(26) << "Match 3 =" << setw(12) << " $7\n";
			cout << "Odds: 1 in 1 in 360.14\n";
			return 7;
		break;

		case 5:
			cout << setw(26) << "Match 3 + PowerBall =" << setw(12) << " $100\n";
			cout << "Odds: 1 in 12,244.83\n";
			return 100;
		break;

		case 6:
			cout << setw(26) << "Match 4 =" << setw(12) << " $100\n";
			cout << "Odds: 1 in 19,087.53\n";
			return 100;
		break;

		case 7:
			cout << setw(26) << "Match 4 + PowerBall =" << setw(12) << " $10,000\n";
			cout << "Odds: 1 in 648,975.96\n";
			return 10000;
		break;

		case 8:
			cout << setw(26) << "Match 5 =" << setw(12) << " $1,000,000\n";
			cout << "Odds: 1 in 5,153,632.65\n";
			return 1000000;
		break;

		case 9:
			cout << setw(26) << "Match all 5 + PowerBall =" << setw(12) << " Grand Prize\n $100,000,000";
			cout << "Odds: 1 in 175,223,510.00\n";
			return 100000000;
		break;

		default:
		if (debug = 1) {
			cout << "\n\n**function DisplayPrize(int) called incorrrectly.**\n\n";
		} return 0;
		break;
	}
}

//this works 4/29
void copyArray(int *array1, int *array2, int elem) {
	int *nPt;
	nPt = array1 + elem;
	while (array1 < nPt) {
		//cout << "Hey its working!";
		*array2 = *array1;
		array1++;
		array2++;
	}

	// for (int i = 0; i < elem; i++) {
	// 	*array2 = *array1;
	// 	array2++;
	// 	array1++;
	// }
}

//this works 4/29
void printArr(int *arr, int elem) {

	int *nPt = arr + elem;
	while(arr < nPt) {
		if ((arr + 1) == nPt) {
			cout << "PowerBall: " << *arr;
		} else {
			cout << *arr << "  ";
		}
		
		arr++;
	}
	cout << endl;
}

void GetPlayerSelections(int *playerNumbers) {
	//max pointer
	int *nPt = playerNumbers + NUMBALLZ;
	//original pointer
	int *oPt = playerNumbers;
	int tryThis;
	if (debug != 1) {
		system("cls");
	}
	cout << "Pick your lottery numbers...\n";

	while (nPt > playerNumbers) {
		if ((playerNumbers + 1) == nPt) {
			cout << "\nPick a PowerBall number between 1-35: ";
			cin >> tryThis;

			//check to make sure it's 1-59
			if (tryThis > 0 && tryThis < 36) {
				//check for dups
				if (inArray(tryThis, oPt, NUMBALLZ) == 0) {
					//cool, picked a good number, add it to the array and increment the pointer
					*playerNumbers = tryThis;
					playerNumbers++;
					//TODO: this can be commented out
					//cout << tryThis << " entered at " << playerNumbers;
				} else {
					cout << "\nDon't choose the same number twice.";
				}
			} else {
				cout << "\nPick a whole number between 1-35";
			}
		} else {
			cout << "\nEnter an integer between 1-59: ";
			cin >> tryThis;

			//check to make sure it's 1-59
			if (tryThis > 0 && tryThis < 60) {
				//check for dups
				if (inArray(tryThis, oPt, NUMBALLZ) == 0) {
					//cool, picked a good number, add it to the array and increment the pointer
					*playerNumbers = tryThis;
					playerNumbers++;
					//TODO: this can be commented out
					//cout << tryThis << " entered at " << playerNumbers;
				} else {
					cout << "\nDon't choose the same number twice.";
				}
			} else {
				cout << "\nPick a whole number between 1-59";
			}
		}
	}
}

void GeneratePowerball (int *generatedNumbers) { 
	int *nPt = generatedNumbers + NUMBALLZ; 
	int *oPt = generatedNumbers; 
	int tryThis; 
	tryThis = randomNum(0,59);
	

	while (nPt > generatedNumbers) {
		while (inArray(tryThis, oPt, NUMBALLZ) > 0) {
			if ((generatedNumbers + 1) == nPt) {
				tryThis = randomNum(0,35);
			} else {
				tryThis = randomNum(0,59);
			}
		}
		*generatedNumbers = tryThis;
		generatedNumbers++;
	}

	cout << "Generated Powerball." << endl;
}