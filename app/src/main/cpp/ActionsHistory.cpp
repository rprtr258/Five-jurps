#include "ActionsHistory.h"

ActionsHistory::ActionsHistory() {
    history = new std::vector<Action>();
}

ActionsHistory::~ActionsHistory() {
    delete history;
}

int ActionsHistory::getTurnsCount() {
    return size;
}

void ActionsHistory::doAction(const Action &action) {
    int sizeBuf = history->size();
    if(action.fromx!=action.tox || action.fromy!=action.toy) {
        size++;
        if(sizeBuf<MAX_HISTORY_SIZE) {
            if(pos<sizeBuf) history->erase(history->begin()+pos+1, history->end());
            history->push_back(action);
            pos++;
        } else {
            history->erase(history->begin());
            history->push_back(action);
        }
    }
}

void ActionsHistory::redo(GameField &field) {
    int steps = 0, sizeBuf = history->size();
    if(sizeBuf>0 && pos+HISTORY_STEP<MAX_HISTORY_SIZE) {
        pos++;
        Action &curAction = history->at(pos);
        field.turn(curAction.fromx, curAction.fromy, curAction.tox, curAction.toy);
        steps++;
        size++;
    }
}

void ActionsHistory::undo(GameField &field) {
    int steps = 0, sizeBuf = history->size();
    if(sizeBuf>0 && pos>=0) {
        Action &curAction = history->at(pos);
        field.turn(curAction.fromx, curAction.fromy, curAction.tox, curAction.toy);
        pos--;
        steps++;
        size--;
    }
}
