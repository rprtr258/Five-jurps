#include "Field.h"

Field::Field() {
}

Field::~Field() {

}

int Field::getProgress() const {
    int progress = 0;
    for(size_t i=0;i<map.size();i++) {
        for(size_t j=0;j<map[i].size();j++) {
            CellType type = EMPTY;
            if(goal[j][i]>=10 && goal[j][i]<20) {
                type = BLACK;
            } else if(goal[j][i]>=20 && goal[j][i]<30) {
                type = WHITE;
            }
            if(isToken(j, i, false) && type!=EMPTY && map[j][i]==goal[j][i]) {
                progress++;
            }
        }
    }
    return progress;
}

int Field::getMaxProgress() const {
    int progress = 0;
    for(size_t i=0;i<map.size();i++) {
        for(size_t j=0;j<map[i].size();j++) {
            if(isToken(j, i, false)) {
                progress++;
            }
        }
    }
    return progress;
}

int Field::isToken(const int &x, const int &y, bool showGoal) const {
    if(getCellType(x, y, showGoal)==WHITE) {
        return 1;
    }
    if(getCellType(x, y, showGoal)==BLACK) {
        return 2;
    }
    return 0;
}

CellType Field::getCellType(const int &x, const int &y, bool showGoal)  const {
    const std::vector<std::vector<int> > &field = (showGoal?goal:map);
    if(field[x][y]==-1) return NONE;
    if(field[x][y]==0) return EMPTY;
    if(field[x][y]>=3 && field[x][y]<=6) return ARROW;
    if(field[x][y]>=10 && field[x][y]<20) return BLACK;
    if(field[x][y]>=20 && field[x][y]<30) return WHITE;
    return NONE;
}

int Field::getCellValue(const int &x, const int &y, bool showGoal)  const {
    const std::vector<std::vector<int> > &field = (showGoal?goal:map);
    if(isToken(x, y, showGoal)) {
        if(getCellType(x, y, showGoal)==BLACK) {
            return field[x][y] - 10 + 1;
        } else if(getCellType(x, y, showGoal)==WHITE) {
            return field[x][y] - 20 + 1;
        }
    }
    return field[x][y];
}

void Field::setCell(const int &x, const int &y, int value) {
    map[x][y] = value;
}

void Field::set(std::vector<std::vector<int> > newMap, std::vector<std::vector<int> > newGoal) {
    map = newMap;
    goal = newGoal;
    size = map.size();
}

int Field::getSize() const {
    return size;
}

bool Field::hasArrows() {
    bool has = false;
    for(size_t i=0;i<map.size();i++) {
        for(size_t j=0;j<map[i].size();j++) {
            has = has || getCellType(j, i, false)==ARROW;
        }
    }
    return has;
}

void Field::clearFromArrows() {
    for(size_t i=0;i<map.size();i++) {
        for(size_t j=0;j<map[i].size();j++) {
            if(getCellType(j, i, false)==ARROW) {
                map[j][i] = 0;
            }
        }
    }
}

void Field::doTurn(const int &fromx, const int &fromy, const int &tox, const int &toy) {
    std::swap(map[fromx][fromy], map[tox][toy]);
}
