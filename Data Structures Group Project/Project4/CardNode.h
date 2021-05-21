//CardNode.h
#include "Card.h"
#ifndef CARDNODE_H
#define CARDNODE_H

class CardNode {
	
private:

	Card card;
	CardNode* next;
	
public:

	CardNode() :card(), next() {//initializes the attributes of the class
		next = NULL;
	}
	
	CardNode(Card& obj){//assigns card data
		card = obj;
	}
	
	Card& getCard() {//returns card data
		return card;
	}
	
	CardNode* getNext() {//returrns the pointer to the next node
		return next;
	}
	
	void setCard(Card& obj) {//sets card data
		card = obj;
	}
	
	void setNext(CardNode* nextCard) {//assigns the next node pointer
		next = nextCard;
	}
	
	~CardNode() {
	}
};
#endif // !CARDNODE_H
