#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

#include <vector>
using std::vector;

#include <set>
using std::set;

// TODO: Your Sudoku class goes here:
class Sudoku {

private:
	int size;
	vector< vector< set<int> > > board;

public:
	Sudoku(const int & sizeIn) 
	: size (sizeIn) {}
};


#endif
