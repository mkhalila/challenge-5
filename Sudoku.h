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

#include <cmath>
using std::sqrt;

// TODO: Your Sudoku class goes here:
class Sudoku : public Searchable {

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

	void clearCol(const int & rowIn, const int & colIn, const int & value) {
		for (size_t row = 0; row < size; ++row) {
			if (row != rowIn) {
				board[row][colIn].erase(value);
			}
		}
	}	

	void clearBox(const int & rowIn, const int & colIn, const int & value) {
    	int y = sqrt(size) * floor(rowIn/sqrt(size));
    	int x = sqrt(size) * floor(colIn/sqrt(size)); 

		for (int i = y; i < y + sqrt(size); ++i) {
			for (int j = x; j < x + sqrt(size); ++j) {
				
				if (i == rowIn && j == colIn) { continue; }
				else { board[i][j].erase(value); }
			}
		}
	}

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
    	int prev = 0;
    	int current = 0;

		while (true) {
			for (size_t x = 0; x < size; ++x) {
				for (size_t y = 0; y < size; ++y) {

          			if (board[x][y].size() == 1) {
            			++current;
						clearRow(x, y, *board[x][y].begin());
						clearCol(x, y, *board[x][y].begin());
						clearBox(x, y, *board[x][y].begin());
					}
          			
          			if (board[x][y].size() == 0) { return false; }
				}
			}
			
			if (prev == current) { break; }
      		prev = current;
      		current = 0;
		}
		
		return true;
	}

	virtual bool isSolution() const override {
		int count = 0;
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				
				if (board[i][j].size() == 1) {
					++count;
				}
			}	
		}
		return count == (size*size);
	}

	virtual void write(ostream & o) const override {
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				
				for (const int & val : board[i][j]) {
					o << val << " ";
				}
				o << endl;
			}	
			o << endl;
		}
	}

	virtual int heuristicValue() const override {}

	virtual vector<unique_ptr<Searchable> > successors() const override {}

};


#endif
