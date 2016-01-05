#ifndef ACTIONSHISTORY_H
#define ACTIONSHISTORY_H

#include <vector>

#include "Action.h"
#include "GameField.h"


class ActionsHistory {
    public:
        ActionsHistory();
        ~ActionsHistory();
        int getTurnsCount();
        void doAction(const Action &action);
        void redo(GameField &field);
        void undo(GameField &field);
    private:
        std::vector<Action> *history;
        int pos = -1, size = 0;
        const int MAX_HISTORY_SIZE = 100, HISTORY_STEP = 5;
};

#endif
