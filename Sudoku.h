#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

#include <vector>
using std::vector;

#include <set>
using std::set;

#include <iostream>
using std::cout;
using std::endl;

// TODO: Your Sudoku class goes here:
class Sudoku {

private:
	int size;
	vector< vector< set<int> > > board;

public:
	Sudoku(const int & sizeIn) 
	: size (sizeIn) {
		//Initialise 2d board of given size
		board.resize(size);
		for (size_t i = 0; i < size; ++i) {
        	board[i] = vector< set<int> >(size);
    	}

    	//Creates set containing (1.. size) ints
    	set<int> initSet;

    	//Sets every square to have a set (1.. size)
    	for (size_t row = 0; row < size; ++row) {
        	for (size_t col = 0; col < size; ++col) {
            	board[row][col] = initSet;
        	}
    	}	
	}
};


#endif
