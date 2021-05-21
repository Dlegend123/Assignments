//Wheel.h
#include "CardNode.h"
#ifndef WHEEL_H
#define WHEEL_H

class Wheel {
	
private:

	CardNode* head;

public:

	Wheel() :head(){//initializes the attributes of the class
		head = NULL;
	}
	
	void setCards(){//adds card to node
		string option[24] = { "2500", "WILD00", "600","700", "600", "650",
							"500.00", "700.00", "BANKRUPT ONE MILLION BANKRUPT", 
							"600","550", "500", "600","BANKRUPT", "650", "Free PLAY",
							"700", "LOSE A TURN", "800", "500", "650", "500",
							"900","BANKRUPT" };
		Card card[24];
		for (int i = 0; i < 24; i++) {
			card[i].setType(i);
			card[i].setValue(option, i);
			addEnd(card[i]);
		}
	}
	
	bool isEmpty(){//checks if list is empty
		return (head == NULL) ? true : false;
	}
	
	bool isFull(){//checks if list is full
		CardNode* temp = new CardNode();
		if (temp == NULL)
			return true;
		else{
			delete temp;
			return false;
		}
	}
	
	void addEnd(Card& card){//adds card to the end of the list
		
		if (!isFull()){
			CardNode* temp = new CardNode(card);
			if (isEmpty()){
				head=temp;
				head->setNext(head);
			}
			else {
				CardNode* temp2 = head;
				while (temp2->getNext() != head)
					temp2 = temp2->getNext();
				temp->setNext(head);
				temp2->setNext(temp);
			}
		}
		else
			cout << "Out of memory" << endl;
	}

	CardNode*getHead(){//returns head
		return head;
	}
	
	void setHead(CardNode*next){//sets head
		head=next;
	}
	
	void destroy() {//deletes all the nodes in the list
		if (!isEmpty()) {
			CardNode* temp = new CardNode();
			CardNode* temp2 = head;

			do {
				temp = temp2;
				temp2 = temp2->getNext();
				delete temp;
			} while (temp2 != head);
		}
	}

	~Wheel(){
	}
};
#endif
