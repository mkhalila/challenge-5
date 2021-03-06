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
	vector< vector<bool> > singleVisited;
	vector< vector<bool> > doubleVisited;
	vector< vector<bool> > counted;
	int singles;

	bool clearRow(const size_t & rowIn, const size_t & colIn, const int & value) {
		for (size_t col = 0; col < size; ++col) {
			if (col != colIn) {
				board[rowIn][col].erase(value);
				if (board[rowIn][col].size() == 0) 
					return false;
				if (board[rowIn][col].size() == 1 && counted[rowIn][col] == false) {
					counted[rowIn][col] = true;
					++singles;
				}
			}
		}
		return true;
	}

	bool clearCol(const size_t & rowIn, const size_t & colIn, const int & value) {
		for (size_t row = 0; row < size; ++row) {
			if (row != rowIn) {
				board[row][colIn].erase(value);
				if (board[row][colIn].size() == 0) 
					return false;
				if (board[row][colIn].size() == 1 && counted[row][colIn] == false) {
					counted[row][colIn] = true;
					++singles;
				}
			}
		}
		return true;
	}	

	bool clearBox(const size_t & rowIn, const size_t & colIn, const int & value) {
    	int y = sqrt(size) * floor(rowIn/sqrt(size));
    	int x = sqrt(size) * floor(colIn/sqrt(size)); 

		for (size_t i = y; i < y + sqrt(size); ++i) {
			for (size_t j = x; j < x + sqrt(size); ++j) {
				
				if (i == rowIn && j == colIn) { continue; }
				else { 
					board[i][j].erase(value); 
					if (board[i][j].size() == 0)
						return false;
					if (board[i][j].size() == 1 && counted[i][j] == false) {
						counted[i][j] = true;
						++singles;
					}	
				}
			}
		}
		return true;
	}

public:

	Sudoku(const int & sizeIn) 
	: size (sizeIn) {

		//Initialise 2d board of given size
		board.resize(size);
		singleVisited.resize(size);
		doubleVisited.resize(size);
		counted.resize(size);

		for (size_t i = 0; i < size; ++i) {
        	board[i] = vector< set<int> >(size);
        	singleVisited[i] = vector<bool>(size);
        	doubleVisited[i] = vector<bool>(size);
        	counted[i] = vector<bool>(size);
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
            	singleVisited[row][col] = false;
            	doubleVisited[row][col] = false;
            	counted[row][col] = false;
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
		counted[row][col] = true;
		++singles;
    	size_t prev = 0;
    	size_t current = 0;

		while (true) {
			for (size_t x = 0; x < size; ++x) {
				for (size_t y = 0; y < size; ++y) {

          			if (board[x][y].size() == 0) { return false; }

					if (board[x][y].size() == 1) {
						if (singleVisited[x][y] == true) {
							continue;
						}
						singleVisited[x][y] = true;
            			++current;
						if (!clearRow(x, y, *board[x][y].begin())) return false;
						if(!clearCol(x, y, *board[x][y].begin())) return false;
						if(!clearBox(x, y, *board[x][y].begin())) return false;
					}

					if (board[x][y].size() == 2) {
						if (doubleVisited[x][y] == true) {
							continue;
						}
						++current;

						//Look for another set of size 2 in this row
						for (size_t z = 0; z < size; ++z) {
							if ((y != z) && (board[x][y] == board[x][z])) {
								doubleVisited[x][y] = true;
								doubleVisited[x][z] = true;
								auto itr = board[x][y].begin();
								size_t first = *itr;
								++itr;
								size_t second = *itr;
								for (size_t col = 0; col < size; ++col) {
									if ((col != y) && (col != z)) {
										board[x][col].erase(first);
										if (board[x][col].size() == 0)
											return false;
										board[x][col].erase(second);
										if (board[x][col].size() == 0)
											return false;
										if (board[x][col].size() == 1 && counted[x][col] == false) {
											counted[x][col] = true;
											++singles;
										}	
									}
								}
								break;
							}
						}

						//Look for another set of size 2 in this col
						for (size_t z = 0; z < size; ++z) {
							if ((x != z) && (board[x][y] == board[z][y])) {
								doubleVisited[x][y] = true;
								doubleVisited[z][y] = true;
								auto itr = board[x][y].begin();
								size_t first = *itr;
								++itr;
								size_t second = *itr;
								for (size_t row = 0; row < size; ++row) {
									if ((row != x) && (row != z)) {
										board[row][y].erase(first);
										if (board[row][y].size() == 0)
											return false;
										board[row][y].erase(second);
										if (board[row][y].size() == 0)
											return false;
										if (board[row][y].size() == 1 && counted[row][y] == false) {
											counted[row][y] = true;
											++singles;
										}	
									}
								}
								break;
							}
						}

						//Look for another set of size 2 in sub-grid
						size_t rowStart = sqrt(size) * floor(x/sqrt(size));
    					size_t colStart = sqrt(size) * floor(y/sqrt(size)); 
    					int foundX = -1;
    					int foundY = -1;

						for (size_t i = rowStart; i < (rowStart + sqrt(size)); ++i) {
							for (size_t j = colStart; j < (colStart + sqrt(size)); ++j) {
								if ( (i != x) && (j != y) && (board[x][y] == board[i][j]) ) {
									foundX = i;
									foundY = j;
									break;
								}
							}
						}

						doubleVisited[x][y] = true;
						if (foundX > -1) doubleVisited[foundX][foundY] = true;

						auto boxItr = board[x][y].begin();
						size_t first = *boxItr;
						++boxItr;
						size_t second = *boxItr;

						for (size_t i = rowStart; i < (rowStart + sqrt(size)); ++i) {
							for (size_t j = colStart; j < (colStart + sqrt(size)); ++j) {
								if ( (foundX > -1) && (i != x) && (i != foundX) && (j != y) && (j != foundY) ) {
									board[i][j].erase(first);
									board[i][j].erase(second);
									if (board[i][j].size() == 1 && counted[i][j] == false) {
											counted[i][j] = true;
											++singles;
									}	
								}
							}
						}
					}
				}
			}
			
			if (prev == current) { break; }
      		prev = current;
      		current = 0;
		}
		
		return true;
	}

	virtual bool isSolution() const override {
		size_t count = 0;
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

	virtual int heuristicValue() const override {
		return (size*size) - singles;
	}

	virtual vector< unique_ptr<Searchable> > successors() const override {
		vector< unique_ptr<Searchable> > success;

		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				
				if (board[i][j].size() > 1) {
					for (const auto & val : board[i][j]) {
						Sudoku * sudCopy = new Sudoku(*this);
						bool isSuccess = sudCopy->setSquare(i, j, val);
						if (isSuccess) {
							success.push_back(unique_ptr<Searchable>(sudCopy));
						} else {
							delete sudCopy;
						}
					}
					if ((success.size() == 1) && !(success[0]->isSolution())) {
						return success[0]->successors();
					}
					return success;
				}
			}	
		}

		return success;
	}

};


#endif
