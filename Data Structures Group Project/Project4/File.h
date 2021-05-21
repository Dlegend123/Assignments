//File.h
#include "Aesthetic.h"
#include "Puzzle.h"
#include "PuzzleList.h"
#ifndef FILE_H
#define FILE_H
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

class File{
private:
	fstream puzzleFile;

public:
	File() : puzzleFile(){
	}

	void addPuzzle() {//method to add puzzles to file

		string answer, category, question;
		int num;
		puzzleFile.open("Puzzle.txt", ios::app);

		if (puzzleFile.is_open()) {

			try {
				cout << "How many puzzles would you like to add?\n";
				cin >> num;
				if (cin.fail())
					throw num;
				cin.get();
				for (auto i = 0; i < num; i++) {
					cout << "\nEnter the question\n";
					getline(cin, question);
					while (question.length() < 1) {
						system("cls");
						Aesthetic::setTextColor(stdout, 4);
						cout << "You are required to enter a question\n";
						Aesthetic::setTextColor(stdout, 13);
						cout << "\nEnter the question\n";
						getline(cin, question);
					}

					cout << "\nEnter the answer\n";
					getline(cin, answer);
					while (answer.length() < 1) {
						system("cls");
						Aesthetic::setTextColor(stdout, 4);
						cout << "You are required to enter an answer\n";
						Aesthetic::setTextColor(stdout, 13);
						cout << "\nEnter the answer\n";
						getline(cin, answer);
					}

					cout << "\nEnter the category\n";
					getline(cin, category);
					for_each(category.begin(), category.end(), [](char& c) {
						c = ::tolower(c);
						}); //changes all the letters in the category to lower case
					if (category == "person")
						category = "Person";
					else {
						if (category == "place")
							category = "Place";
						else {
							if (category == "thing")
								category = "Thing";
							else if (category == "phrase")
								category = "Phrase";
						}
					}
					while (category != "Person" && category != "Place" && category != "Phrase" && category != "Thing") { //checks if the wrong category was entered
						
						system("cls");
						Aesthetic::setTextColor(stdout, 4);
						cout << "Invalid category\n";
						Aesthetic::setTextColor(stdout, 13);
						cout << "Enter the category\n";
						getline(cin, category);

						for_each(category.begin(), category.end(), [](char& c) {
							c = ::tolower(c);
							});

						if (category == "person")
							category = "Person";
						else {
							if (category == "place")
								category = "Place";
							else {
								if (category == "thing")
									category = "Thing";
								else if (category == "phrase")
									category = "Phrase";
							}
						}
					}
					puzzleFile << category << "\t" << answer << "\t" << question << endl;
				}
				puzzleFile.close();
			}
			catch (int x) {
				Aesthetic::catchBody();
			}
		}
		else {
			cout << "Error opening the file\n";
			system("pause");
		}
	}

	void erasePuzzles() {//method to delete all the puzzles in the file

		if (remove("Puzzle.txt") != 0)
			cout << "The file does not exist\n\n";
		else
			cout << "File successfully deleted\n\n";
		system("pause");
	}

	PuzzleList readFile() {//method to read all the puzzles in the file

		Puzzle puzzle;
		string category, answer, question;
		PuzzleList pList;
		puzzleFile.open("Puzzle.txt", ios::in);

		if (puzzleFile.is_open()) {
			while (puzzleFile >> category >> answer >> question) {   //collects puzzle information from the file
				puzzle.setAnswer(answer);
				puzzle.setQuestion(question);
				puzzle.setCategory(category);
				pList.insertAtFront(puzzle);
			}
			puzzleFile.close();
		}
		return pList;
	}

	~File() {
	}
};
#endif