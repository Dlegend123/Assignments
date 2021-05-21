//PuzzleNode.h
#include "Puzzle.h"
#ifndef PUZZLENODE_H
#define PUZZLENODE_H

class PuzzleNode {
	
private:

	Puzzle puzzle;
	PuzzleNode* next;
public:

	PuzzleNode():puzzle(),next() {
		next = NULL;
	}

	PuzzleNode(Puzzle&obj):puzzle(),next(){
		puzzle=obj;
		next = NULL;
	}
	
	Puzzle& getPuzzle() {
		return puzzle;
	}
	
	PuzzleNode* getNext() {
		return next;
	}
	
	void setPuzzle(Puzzle& obj) {
		puzzle = obj;
	}
	
	void setNext(PuzzleNode *nextPuzzle) {
		next = nextPuzzle;
	}
	
	~PuzzleNode() {
	}
};
#endif // !PUZZLENODE_H