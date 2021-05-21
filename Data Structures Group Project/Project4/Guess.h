//Guess.h
#include"GuessNode.h"
#ifndef GUESS_H
#define GUESS_H

class Guess {
	
private:

	GuessNode* front;
	GuessNode* rear;
	
public:

	Guess():front(),rear(){//initializes the attributes of the class
		front = NULL;
		rear = NULL;
	}
	
	void enQueue(char d){//adds a node to the queue
		GuessNode* temp = new GuessNode(d);
		if (temp==NULL)
			cout << "Out of memory, unable to enqueue new data into the queue" << endl;
		else {
			if (isEmpty()) {
				front = temp;
				rear = temp;
			}
			else {
				rear->setNext(temp);
				temp->setPrev(rear);
				rear = temp;
			}
		}
	}
	void destroy()
	{
		if (front != NULL)
		{
			GuessNode* temp = new GuessNode();
			while (!isEmpty()) {
				temp = front;
				front = front->getNext();
				delete temp;
			}
			rear = NULL;
		}
	}
	bool isEmpty(){//checks if queue is empty;
		return(front==NULL)?true:false;
	}
	
	~Guess(){
	}
};
#endif
