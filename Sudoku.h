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

	void clearRow(const int & rowIn, const int & colIn, const int & value) {
		for (size_t col = 0; col < size; ++col) {
			if (col != colIn) {
				board[rowIn][col].erase(value);
			}
		}
	}

	void clearCol(const int & row, const int & col, const int & value) {}	

	void clearBox(const int & row, const int & col, const int & value) {}

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
    	for (size_t i = 1; i < size+1; ++i) {
    		initSet.insert(i);
    	}

    	//Sets every square to have a set (1.. size)
    	for (size_t row = 0; row < size; ++row) {
        	for (size_t col = 0; col < size; ++col) {
            	board[row][col] = initSet;
        	}
    	}	
	}

	int getSquare(const int & row, const int & col) const {
		if (board[row][col].size() == 1) {
			return *board[row][col].begin();
		}
		return -1;
	}

	bool setSquare(const int & row, const int & col, const int & value) {
		board[row][col] = {value};

		for (size_t row = 0; row < size; ++row) {
			for (size_t col = 0; col < size; ++col) {

				if (board[row][col].size() == 0) { return false; }

				else if (board[row][col].size() == 1) {
					clearRow(row, col, *board[row][col].begin());
					clearCol(row, col, value);
					clearBox(row, col, value);
				}							
			}	
		}
		return true;
	}

};


#endif
