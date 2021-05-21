//Puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H
#include <string>
#include <iostream>
using namespace std;

class Puzzle{
	
private:

	string category;
	string answer;
	string question;
public:


	Puzzle(){//initializes the attributes of the class
		category = "Person";
		answer = "hello";
		question = "type";
	}
	
	void setAnswer(string phrase){//accept answer to puzzle
		answer = phrase;
	}
	
	void setQuestion(string quest){//sets the puzzle's question'
		question = quest;
	}
	
	string getAnswer(){//returns answer 
		return answer;
	}
	
	string getQuestion(){//returns question
		return question;
	}
	
	void setCategory(string cName){//sets category
		category = cName;
	}
	
	string getCategory(){//returns category
		return category;
	}
	~Puzzle() {

	}
};
#endif