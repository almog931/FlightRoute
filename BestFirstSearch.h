#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H


#include <queue>
#include <bits/unordered_set.h>
#include <algorithm>
#include "AbstractSearcher.h"
#include "State.h"

/*
template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::less<typename Container::value_type>
>
class MyQueue : public std::priority_queue<T, Container, myComparator<T>> {
public:
    typedef typename
    std::priority_queue<
            T,
            Container,
            Compare>::container_type::const_iterator const_iterator;

    const_iterator find(const T &val) const {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last) {
            if (*first == val) return first;
            ++first;
        }
        return last;
    }
};
*/

template <class T>
class BestFirstSearch : public AbstractSearcher<T> {


public:

    BestFirstSearch(){
        this->numOfNodes=0;
    };


    std::vector<State<T>*>* search(Searchable<T>* s) {
        this->initialize(s->getAllStates());
        // initial open
        State<T>* first = s->getInitial();
        first->setPathCost(first->getNodeCost());
        this->open.push(first);

        while (!this->open.empty()) {
            // get the most lower path cost.
            State<T>* n = this->open.top();
            this->open.pop();
            this->visited.at(n) = BLACK;
            // check if it is the goal.
            if (n->equals(s->getGoal())) {
                std::vector<State<T>*>* v =  this->backTrace(n);
                return v;
            }
            // get all the neighbors.
            std::vector<State<T>*>* succerssors = (s->getPossibleStates(n));

            for (State<T>* it : *succerssors) {

                if (it->getNodeCost() == -1){
                    continue;
                }
                double currentPathCost = n->getPathCost() + it->getNodeCost();
                // if s is not in open and not in closed.
                if (this->visited.at(it) == WHITE) {
                    this->visited.at(it) = GRAY;
                    it->setFather(n);
                    it->setPathCost(currentPathCost);
                    this->open.push(it);
                    this->numOfNodes++;

                } else if (currentPathCost < it->getPathCost()) {
                    this->numOfNodes++;
                    it->setFather(n);
                    it->setPathCost(currentPathCost);
                    if (this->visited.at(it) == BLACK) {
                        this->visited.at(it) = GRAY;
                        this->open.push(it);
                    }
                }
            }
        }
        return nullptr;
    }
};




#endif //MILESTONE2_BESTFIRSTSEARCH_H
