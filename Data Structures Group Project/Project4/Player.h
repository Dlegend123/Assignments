//Player.h
#ifndef  PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
using namespace std;

class Player {

private:

	string pName;
	int pNum;
	float total;

public:

	Player(){//initializes the attributes of the class
		pNum = 1;
		total = 0;
		pName.assign("Empty");
	}

	void setName(string name){//sets the player's name'
		pName = name;
	}
	
	void setTotal(float sum){//sets the player's game total'
		total = sum;
	}
	
	void setNum(int number){//sets the player's number'
		pNum = number;
	}
	
	float getTotal(){//returns the player's game total'
		return total;
	}
	
	int getNum(){//returns the player's number'
		return pNum;
	}
	
	string getName(){//returns the player's name'
		return pName;
	}
	
	~Player() {
	}
};


#endif