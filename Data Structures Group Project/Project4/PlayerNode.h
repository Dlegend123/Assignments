//PlayerNode.h
#include "Player.h"
#ifndef PLAYERNODE_H
#define PLAYERNODE_H

class PlayerNode {
	
private:

	Player player;
	PlayerNode* next;
	
public:

	PlayerNode():player(),next() {//initializes the attributes of the class
		next = NULL;
	}
	
	PlayerNode(Player&obj) :player(), next() {//assigns player data
		player=obj;
		next = NULL;
	}
	
	Player& getPlayer() {//returns player data
		return player;
	}
	
	PlayerNode* getNext() {//returrns the pointer to the next node
		return next;
	}
	
	void setPlayer(Player& obj) {//assigns player data
		player = obj;
	}
	
	void setNext(PlayerNode *nextPlayer) {//assigns the next node pointer
		next = nextPlayer;
	}
	
	~PlayerNode() {
	}
};
#endif // !PLAYERNODE_H
