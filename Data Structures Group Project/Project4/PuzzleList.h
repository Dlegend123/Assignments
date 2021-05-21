//PuzzleList.h
#include "Puzzle.h"
#include "PuzzleNode.h"
#ifndef PUZZLELIST_H
#define PUZZLELIST_H

class PuzzleList {
	
private:

	PuzzleNode* head;

public:

	PuzzleList() :head() {//initializes the attributes of the class
		head = NULL;
	}
	
	bool isEmpty() {//checks if list is empty
		return(head == NULL) ? true : false;
	}
	
	bool isFull() {//checks if list is full
		PuzzleNode* temp = new PuzzleNode();
		if (temp == NULL)
			return true;
		else {
			delete temp;
			return false;
		}
	}
	
	void setNext(PuzzleNode* next) {//assigns the next node in the list
		head->setNext(next);
	}

	PuzzleNode* getHead() {//returns head
		return head;
	}
	
	void insertAtFront(Puzzle& last) {//adds puzzle to the front of the list

		if (!isFull()) {
			PuzzleNode* temp = new PuzzleNode(last);
			if (isEmpty()) 
				head = temp;
			else {
				temp->setNext(head);
				head = temp;
			}
		}
		else
			cout << "Out of memory" << endl;
	}
	
	void setHead(PuzzleNode* player) {//assigns head
		head = player;
	}
	
	void destroy() {//deletes all the nodes in the list
		if (!isEmpty()) {
			PuzzleNode* temp = new PuzzleNode();
			while (head != NULL) {
				temp = head;
				head = head->getNext();
				delete temp;
			}
		}
	}

	~PuzzleList() {
	}
};
#endif