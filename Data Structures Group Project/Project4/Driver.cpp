//Driver.cpp
#include "Aesthetic.h"
#include "File.h"
#include"Game.h"

#include<iostream>
using namespace std;


int main(){
	
	Aesthetic ::setTextColor(stdout, 13);//Sets text colour to light magenta
	int choice=0, option=0;
	Game game;
	
	do {
		Aesthetic ::gotoxy(40, 7);
		cout << "_____________________________________";
		Aesthetic ::gotoxy(39, 8);
		cout << "|                                     |";
		Aesthetic ::gotoxy(55, 8);
		cout << "Main Menu";
		Aesthetic ::menuLook();
		cout << " 1. File Options";
		Aesthetic ::gotoxy(43, 12);
		cout << " 2. Wheel of Fortune";
		Aesthetic ::gotoxy(43, 13);
		cout << " 3. Exit";
		Aesthetic ::gotoxy(44, 14);
		cin >> choice; //accepts user choice
		cin.get();
		system("cls");
		switch (choice) {
		case 1:
			do{
				File obj;
				Aesthetic ::gotoxy(40, 7);
				cout << "_____________________________________";
				Aesthetic ::gotoxy(39, 8);
				cout << "|                                     |";
				Aesthetic ::gotoxy(52, 8);
				cout << "File Options";
				Aesthetic ::menuLook();
				cout << " 1. Add  puzzle";
				Aesthetic ::gotoxy(43, 12);
				cout << " 2. Erase all puzzles";
				Aesthetic ::gotoxy(43, 13);
				cout << " 3. Return to main menu";
				Aesthetic ::gotoxy(44, 14);
				cin >> option; //accepts user choice
				cin.get();
				system("cls");
				switch (option) {//checks user's choice and operates accordingly
				case 1:
					obj.addPuzzle();
					break;
				case 2:
					obj.erasePuzzles();
					break;
				}
				Aesthetic ::display(option);
			} while (option != 3);

			break;
		case 2:
				game.spinWheel();			
			break;
		}
		Aesthetic ::display(choice);
	} while (choice != 3);
	
	return 0;
}

