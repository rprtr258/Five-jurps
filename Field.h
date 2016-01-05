#ifndef FIELD_H
#define FIELD_H

#include <vector>

#include <SFML/Graphics.hpp>

enum CellType{None = -1, Empty, Black, White, Arrow};
typedef unsigned int size_t;

class Field {
    public:
        Field();
        ~Field();
        int getProgress() const;
        int getMaxProgress() const;
        CellType getCellType(const int &x, const int &y, bool showGoal) const;
        int getCellValue(const int &x, const int &y, bool showGoal) const;
        int isToken(const int &x, const int &y, bool showGoal) const;
        void setCell(const int &x, const int &y, int value);
        void set(std::vector<std::vector<int> > newMap, std::vector<std::vector<int> > newGoal);
        int getSize() const;
        bool hasArrows();
        void clearFromArrows();
        void doTurn(const int &fromx, const int &fromy, const int &tox, const int &toy);
    private:
        std::vector<std::vector<int> > map, goal;
        int size;
};

#endif
