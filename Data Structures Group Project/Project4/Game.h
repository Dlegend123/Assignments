//Game.h
#include "Wheel.h"
#include "Contestants.h"
#include "PuzzleList.h"
#include "Guess.h"
#ifndef GAME_H
#define GAME_H
#include<time.h>
#include <conio.h>
#include<string>

class Game {

private:

	PuzzleList pList;
	Contestants conList;
	Wheel wheel;

public:

	Game() :pList(), conList(), wheel() {
		wheel.setCards();
	}

	void spinWheel() {

		File obj;
		pList = obj.readFile();//stores the puzzles in nodes of a list
		PuzzleList person, place, thing, phrase;

		if (!pList.isEmpty()) {
			int pe = 0, pl = 0, th = 0, ph = 0;
			while (!pList.isEmpty()) {//separate the puzzles by their category

				if (pList.getHead()->getPuzzle().getCategory() == "Person") {
					person.insertAtFront(pList.getHead()->getPuzzle());
					pe++;
				}
				else {
					if (pList.getHead()->getPuzzle().getCategory() == "Place") {
						place.insertAtFront(pList.getHead()->getPuzzle());
						pl++;
					}
					else {
						if (pList.getHead()->getPuzzle().getCategory() == "Thing") {
							thing.insertAtFront(pList.getHead()->getPuzzle());
							th++;
						}
						else {
							phrase.insertAtFront(pList.getHead()->getPuzzle());
							ph++;
						}
					}
				}
				pList.setHead(pList.getHead()->getNext());
			}
			if (ph > 0 && pl > 0 && pe > 0 && th > 0) {

				cout << "Welcome to 'Wheel of Fortune'! \n" << endl;
				setPlayers();
				runGame(person, place, thing, phrase, ph, pl, pe, th);
				showWinnerInfo();
				conList.destroy();
				wheel.destroy();
			}
			else
				cout << "There aren't enough puzzles from each category in the file\n";
		}
		else
			cout << "There aren't any puzzles in the file\n";
		Aesthetic::gotoxy(40, 28);
		system("pause");
		
	}

	void setPlayers() {//accepts and store players' information in nodes of a list
		Player player;
		string pName = "";
		for (int t = 0; t < 3; t++) {

			cout << "Enter the name of Player " << t + 1 << endl;
			getline(cin, pName);
			cout << endl;
			while (pName.length() < 1) {
				system("cls");
				Aesthetic::setTextColor(stdout, 4);
				cout << "You are required to enter a name\n";
				Aesthetic::setTextColor(stdout, 13);
				cout << "Enter the name of Player " << t + 1 << endl;
				getline(cin, pName);
			}
			player.setName(pName);
			player.setNum(t + 1);
			conList.addEnd(player);
		}
	}

	void runGame(PuzzleList& person, PuzzleList& place, PuzzleList& thing, PuzzleList& phrase, int ph, int pl, int pe, int th) {

		char letter = '\0';
		int ignore = 3, validity, prevPos = 0, wheelPos, i;
		srand(time(NULL));

		float* rTotal = NULL;
		for (int round = 0; round < 3; round++) {

			Guess guess;//declares queue object to store guessed letters
			i = 1 + rand() % (4) * 1;
			
			setPList(i, person, place, thing, phrase);

			i = 1 + rand() % (getCTotal(ph, pl, pe, th)) * 1;

			float p1Total = 0, p2Total = 0, p3Total = 0;

			for (int r = 1; r < i; r++)
				pList.setHead(pList.getHead()->getNext());

			string tempAns = pList.getHead()->getPuzzle().getAnswer();

			string answer = "";

			for (int x = 0; x < tempAns.length(); x++) {
				if (isspace(tempAns[x]))
					answer[x] = tempAns[x];
				else
					answer += ('_');
			}

			while (answer != tempAns) {

				if (ignore != 1) {

					wheelPos = 51 + rand() % (100 - 51) * 1;
					wheelPos += prevPos;
					prevPos = wheelPos %= 24;
					validity = 0;

					for (i = 0; i < wheelPos; i++)
						wheel.setHead(wheel.getHead()->getNext());

					//points to the address of the current player's round total
					if (conList.getHead()->getPlayer().getNum() == 1)
						rTotal = &p1Total;
					else {
						if (conList.getHead()->getPlayer().getNum() == 2)
							rTotal = &p2Total;
						else
							rTotal = &p3Total;
					}
				}

				if (wheel.getHead()->getCard().getType() == "MONEY") {

					if (ignore != 1)
						*rTotal += wheel.getHead()->getCard().getValue();//stores the current player's round total
					ignore = 3;
					system("cls");

					roundInfo(*rTotal, round + 1);//show round information
					Aesthetic::gotoxy(39, 10);
					cout << pList.getHead()->getPuzzle().getQuestion();//displays the puzzle's question
					Aesthetic::gotoxy(50, 20);
					cout << answer;//displays the answer for the puzzle
					Aesthetic::gotoxy(40, 28);
					system("pause");

					int choice = 0;
					do {
						roundInfo(*rTotal, round + 1);
						Aesthetic::gotoxy(40, 7);
						cout << "_____________________________________";
						Aesthetic::gotoxy(39, 8);
						cout << "|                                     |";
						Aesthetic::gotoxy(52, 8);
						cout << "Letter Choice";
						Aesthetic::menuLook();
						cout << "1. Enter a letter" << endl;
						Aesthetic::gotoxy(43, 12);
						cout << "2. Buy a vowel for $500.00";
						Aesthetic::gotoxy(43, 13);
						cin >> choice;
						cin.get();
						system("cls");

						switch (choice) {
						case 1:
						{
							cout << "Enter the letter\n";
							letter = _getch();
							i = 0;
							while (i < answer.length() && ignore != 1)//checks if the letter entered was already guessed
							{
								if (answer[i] == letter)
									ignore = 1;
								i++;
							}
							if (ignore == 1) {
								cout << "The letter has already been guessed\n";
								system("pause");
							}
						}
						break;
						case 2:
						{
							i = 0;
							int flag = 2;
							char q = letter;
							while (flag != 0 && tempAns[i] != '\0') {//checks for a vowel in the puzzle's answer and allows it to be displayed'
								if (tempAns[i] != answer[i]) {
									if (tempAns[i] == 'a' || tempAns[i] == 'e' || tempAns[i] == 'i' || tempAns[i] == 'o' || tempAns[i] == 'u') {
										letter = tempAns[i];
										flag = 0;
									}
								}
								i++;
							}
							if (q != letter) {
								*rTotal -= 500;//subtracts the cost for the vowel from the round total
								ignore = 0;
							}
							else {
								cout << "There are no more vowels in the answer\n";
								ignore = 1;
								system("pause");
							}
						}
						break;
						}
						try {
							if (cin.fail())
								throw choice;
							else
								if (choice < 1 || choice > 2) {

									Aesthetic::setTextColor(stdout, 4);
									Aesthetic::gotoxy(42, 6);
									cout << "Invalid choice, please try again";
									Aesthetic::setTextColor(stdout, 13);
								}
						}
						catch (int choice) {
							Aesthetic::catchBody();
						}

					} while (choice != 1 && choice != 2);
					if (ignore != 1) {
						int occurence = 0;
						int temp = occurence;
						for (i = 0; i < tempAns.length(); i++) {
							if (tempAns[i] == letter) {
								answer[i] = tempAns[i];
								occurence++;
							}
						}
						if (temp < occurence)
							guess.enQueue(letter);
						else {
							validity = 1;
							cout << "The letter '" << letter << "'isn't apart of the word\n";
							system("pause");
						}
						*rTotal += (wheel.getHead()->getCard().getValue() * occurence);//calculates round total
						if (answer == tempAns)
							conList.getHead()->getPlayer().setTotal(conList.getHead()->getPlayer().getTotal() + *rTotal);
					}
				}
				else {
					if (wheel.getHead()->getCard().getType() == "BANKRUPTCY")
						conList.getHead()->getPlayer().setTotal(conList.getHead()->getPlayer().getTotal() - *rTotal);
					else
						conList.setHead(conList.getHead()->getNext());
				}
				if (validity == 1)
					conList.setHead(conList.getHead()->getNext());
			}
			guess.destroy();
		}
		pList.destroy();
	}
	
	void setPList(int i, PuzzleList& person, PuzzleList& place, PuzzleList& thing, PuzzleList& phrase) {//copies puzzle information
		if (i == 1)
			pList = person;
		else {
			if (i == 2)
				pList = place;
			else
				pList = (i == 3) ? thing : phrase;
		}
	}

	int getCTotal(int ph, int pl, int pe, int th) {//returns the amount of puzzles for a particular category
		if (pList.getHead()->getPuzzle().getCategory() == "Person")
			return pe;
		else {
			if (pList.getHead()->getPuzzle().getCategory() == "Place")
				return pl;
			else {
				if (pList.getHead()->getPuzzle().getCategory() == "Thing")
					return th;
				else
					return ph;
			}
		}
	}
	
	void roundInfo(float rTotal,int round){//shows round information
		
		Aesthetic ::gotoxy(3, 2);
		cout << "Current Player: Player " << conList.getHead()->getPlayer().getNum();
		Aesthetic ::gotoxy(35, 2);
		cout<< "Round: "<<round;
		Aesthetic ::gotoxy(50, 2);
		cout << "Round Total: $" << conList.getHead()->getPlayer().getTotal() + rTotal;
	}

	void showWinnerInfo() {//Displays  the winner's information
		Player winner = conList.getHead()->getPlayer();
		Player* ptr = &conList.getHead()->getPlayer();
		conList.setHead(conList.getHead()->getNext());
		Player sameTotal,fullDraw;
		while (&conList.getHead()->getPlayer()!=ptr) {

			if (winner.getTotal() <= conList.getHead()->getPlayer().getTotal()) {
				if (conList.getHead()->getPlayer().getTotal() == sameTotal.getTotal())
					fullDraw = conList.getHead()->getPlayer();
				else {
					if (winner.getTotal() == conList.getHead()->getPlayer().getTotal())
						sameTotal = conList.getHead()->getPlayer();
					else
						winner = conList.getHead()->getPlayer();
				}
			}
			conList.setHead(conList.getHead()->getNext());
		}
		Aesthetic::gotoxy(31, 8);
		if (sameTotal.getTotal() != winner.getTotal()) {

			cout << "Congratulations " << winner.getName() << ",you are our new winner ";
			Aesthetic::gotoxy(37, 10);
			cout << "Player's Game Total: $ " << winner.getTotal();
		}
		else {
			if (fullDraw.getTotal() != winner.getTotal()) 
				cout << sameTotal.getName() << " and " << winner.getName() << " drew for second place";
			else 
				cout << "All players have the same game total";
			Aesthetic::gotoxy(37, 10);
			cout << "Players' Game Total: $ " << winner.getTotal();
		}
	}
	~Game() {

	}
};
#endif
