//Contestants.h
#include "Player.h"
#include "PlayerNode.h"
#ifndef CONTESTANTS_H
#define CONTESTANTS_H

class Contestants {
	
private:

	PlayerNode* head;

public:

	Contestants():head(){//initializes the attributes of the class
		head = NULL;
	}
	
	bool isEmpty(){//checks if list is empty
		return (head == NULL)?true:false;
	}
	
	bool isFull(){//checks if list is full
		PlayerNode* temp = new PlayerNode();
		if (temp == NULL)
			return true;
		else {
			delete temp;
			return false;
		}
	}
	
	void setNext(PlayerNode* nextPlayer){
		head->setNext(nextPlayer);
	}
	
	PlayerNode* getHead(){//returns head
		return head;
	}
	
	void  addEnd(Player& last) {//adds player to the end of the list
		if (!isFull()){
			PlayerNode* temp = new PlayerNode(last);
			if (isEmpty()){
				head=temp;
				head->setNext(head);
			}
			else {
				PlayerNode* temp2 = head;
				while (temp2->getNext() != head)
					temp2 = temp2->getNext();
				temp->setNext(head);
				temp2->setNext(temp);
			}
		}
		else
			cout << "Out of memory" << endl;
	}
	
	void setHead(PlayerNode* player){//sets head 
		head = player;
	}
	
	void destroy() {//deletes all the nodes in the list

		if (!isEmpty()) {
			PlayerNode* temp = new PlayerNode();
			PlayerNode* temp2=head;
			
			do{
				temp=temp2;
				temp2=temp2->getNext();
				delete temp;
			}while (head!= temp2);
		}
	}

	~Contestants() {
	}
};
#endif