#ifndef ACTION_H
#define ACTION_H

class ActionsHistory;

class Action {
    friend ActionsHistory;
    public:
        Action(int fromx_, int fromy_, int tox_, int toy_);
        ~Action();
    private:
        int fromx, fromy, tox, toy;
};

#endif
