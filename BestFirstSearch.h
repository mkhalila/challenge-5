#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;
using std::shared_ptr;

#include <queue>
using std::priority_queue;

class BestFirstSearch {

protected:
    
    priority_queue<shared_ptr<Searchable>> pQ;

    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        pQ.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        // TODO Implement search, returning a pointer to the solution (if one is found)
        while (!pQ.empty()) {
            
            if (pQ.top()->isSolution()) {
                return pQ.top().get();
            }
                  
            ++nodes; 

            shared_ptr<Searchable> current(std::move(pQ.top()));
            
            pQ.pop();
            
            vector<unique_ptr<Searchable>> successors = current->successors();
            
            for (auto & successor : successors) {
                pQ.push(std::move(successor));
            }
        }
        
        return nullptr;
    
        return nullptr;
    }
};


// Do not edit below this line

#endif
