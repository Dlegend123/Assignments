//Aesthetic.h
#ifndef AESTHETIC_H
#define AESTHETIC_H
#include <windows.h>
#include <io.h>
#include <iostream>
using namespace std;

class Aesthetic {
	
private:

	typedef enum class TextColor{//sets numbers to colours
		TC_RED = 4,
		TC_LIGHTMAGENTA = 13
	}TextColor;

public:

	Aesthetic (){
	}
	
	void static setTextColor(FILE* stream, int color){//Changes the colour of the text

		int outfd = _fileno(stream);
		HANDLE out = (HANDLE)_get_osfhandle(outfd);
		DWORD outType = GetFileType(out);
		DWORD mode;
		if (outType == FILE_TYPE_CHAR && GetConsoleMode(out, &mode))
			SetConsoleTextAttribute(out, color);
	}

	void static gotoxy(int x, int y) {//Moves the position of the cursor
		static HANDLE h = NULL;
		if (!h)
			h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c = { x, y };
		SetConsoleCursorPosition(h, c);
	}
	
	void static display(int choice){
		try {
			system("cls");

			if (cin.fail())
				throw choice;
			else
				if (choice < 1 || choice > 3) {

					Aesthetic::setTextColor(stdout, 4);
					Aesthetic::gotoxy(42, 6);
					cout << "Invalid choice, please try again";
					Aesthetic::setTextColor(stdout, 13);
				}
		}
		
		catch (int x){
			catchBody();
		}

	}

	void static catchBody(){//catch operation
		setTextColor(stdout, 4);
		gotoxy(42, 6);
		cout << "You entered an invalid character.";
		cin.clear();
		cin.ignore();
		setTextColor(stdout, 13);
	}
	
	void static menuLook(){//creates menu table

		gotoxy(39, 9);
		cout << "|_____________________________________|";
		gotoxy(39, 10);
		cout << "|                                     |";
		gotoxy(39, 11);
		cout << "|                                     |";
		gotoxy(39, 12);
		cout << "|                                     |";
		gotoxy(39, 13);
		cout << "|                                     |";
		gotoxy(39, 14);
		cout << "|                                     |";
		gotoxy(39, 15);
		cout << "|_____________________________________|";
		gotoxy(43, 11);
	}
	~Aesthetic (){
	}
};
#endif
