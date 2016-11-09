#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;
using std::shared_ptr;

#include <queue>
using std::priority_queue;

#include <iostream>
using std::cout;
using std::endl;

struct CompHValues {
    bool operator()(const shared_ptr<Searchable> & one, const shared_ptr<Searchable> & two) {
        return one->heuristicValue() > two->heuristicValue();
    }
};

class BestFirstSearch {

protected:
    
    priority_queue<shared_ptr<Searchable>, vector<shared_ptr<Searchable>>, CompHValues> pQ;
    int nodes = 0;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        pQ.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        while (!pQ.empty()) {
            if (pQ.top()->isSolution()) 
                return pQ.top().get();

            ++nodes; 

            shared_ptr<Searchable> current(std::move(pQ.top()));
            pQ.pop();
            vector<unique_ptr<Searchable>> successors = current->successors();
            for (auto & successor : successors) {
                pQ.push(std::move(successor));
            }
        }
    
        return nullptr;
    }
};


// Do not edit below this line

#endif
