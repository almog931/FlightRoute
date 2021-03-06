
#include "SearchableMatrix.h"
#include <cmath>


/*
 * This func return all the :"children" of some state.
 */
std::vector<State<std::pair<int, int>> *> *SearchableMatrix::getPossibleStates(State<std::pair<int, int>> *state) {
    int i = state->getState()->first;
    int j = state->getState()->second;
    auto temp = new std::vector<State<std::pair<int, int>> *>();

    if (i > 0 && i < row - 1 && j > 0 && j < col - 1) {
        temp->push_back((stateMatrix->at((unsigned) i))->at((unsigned) j + 1));
        temp->push_back((stateMatrix->at((unsigned) i + 1))->at((unsigned) j));
        temp->push_back((stateMatrix->at((unsigned) i))->at((unsigned) j - 1));
        temp->push_back((stateMatrix->at((unsigned) i - 1))->at((unsigned) j));
        return temp;
    }
    if (j + 1 < col) {
        temp->push_back((stateMatrix->at((unsigned) i))->at((unsigned) j + 1));
    }
    if (i + 1 < row) {
        temp->push_back((stateMatrix->at((unsigned) i + 1))->at((unsigned) j));
    }
    if (j - 1 >= 0) {
        temp->push_back((stateMatrix->at((unsigned) i))->at((unsigned) j - 1));
    }
    if (i - 1 >= 0) {
        temp->push_back((stateMatrix->at((unsigned) i - 1))->at((unsigned) j));
    }
    return temp;
}

/*
 * This func set the distance from some state to the goal state.
 */
void SearchableMatrix::setDistance(State<std::pair<int, int>> *state, State<std::pair<int, int>> *goal) {
    state->setDistance(std::abs(state->getState()->first - goal->getState()->first) +
                       std::abs(state->getState()->second - goal->getState()->second));
}

/*
 * This func initial the goal and init states.
 */
void SearchableMatrix::initAndGoal(std::pair<int, int> init, std::pair<int, int> goal) {
    this->goal = stateMatrix->at(goal.first)->at(goal.second);
    this->initial = stateMatrix->at(init.first)->at(init.second);
}

/*
 * This func creates the matrix of states.
 * We run on all the vector of cost's sent to us and create states which
 * will be inside vector of vectors -> MATRIX.
 */
std::vector<std::vector<State<std::pair<int, int>> *> *> *
SearchableMatrix::setStatesMatrix(std::vector<std::vector<double> *> *matrix) {

    int i = 0, j = 0;

    auto tempMatrix = new std::vector<std::vector<State<std::pair<int, int>> *> *>;

    auto tempAllStates = new std::vector<State<std::pair<int, int>> *>();

    for (std::vector<double> *vec : *matrix) { // create matrix of state and array of states.

        auto tempVec = new std::vector<State<std::pair<int, int>> *>;

        for (double c : *vec) {
            auto pair = new std::pair<int, int>(i, j);
            auto s = new State<std::pair<int, int>>(pair, c);

            tempVec->push_back(s);
            j++;
        }
        tempMatrix->push_back(tempVec);
        (*tempAllStates).insert(tempAllStates->end(), tempVec->begin(), tempVec->end());
        j = 0;
        i++;
    }
    allStates = tempAllStates;
    return tempMatrix;
}

/*
 * This func return all the states exist in the matrix.
 */
std::vector<State<std::pair<int, int>> *> *SearchableMatrix::getAllStates() {
    return allStates;
}

/*
 * This func return the initial state.
 */
State<std::pair<int, int>> *SearchableMatrix::getInitial() {
    return initial;
};


/*
 * This func return the goal state.
 */
State<std::pair<int, int>> *SearchableMatrix::getGoal() {
    return this->goal;
};
