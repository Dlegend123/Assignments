//GuessNode.h
#ifndef GUESSNODE_H
#define GUESSNODE_H

class GuessNode{
	
private:

	char guess;
	GuessNode* prev;
	GuessNode* next;
	
public:

	GuessNode():prev(),next(){//initializes the attributes of the class
		guess = '\0';
		prev = NULL;
		next = NULL;
	}
	
	GuessNode(char letter) :prev(), next() {
		guess = letter;
		prev = NULL;
		next = NULL;
	}
	
	void setGuess(char letter){//sets the guessed letter
		guess = letter;
	}
	
	char getGuess(){//returns the guessed letter
		return guess;
	}

	void setNext(GuessNode* nGuess){//sets the next node pointer
		next = nGuess;
	}
	
	GuessNode* getNext(){//returns the next node pointer
		return next;
	}
	
	void setPrev(GuessNode* pGuess){//sets the previous node pointer
		prev = pGuess;
	}
	
	GuessNode* getPrev(){//returns the previous node pointer
		return prev;
	}
	
	~GuessNode() {
	}
};
#endif