#include "GameField.h"

GameField::GameField() {
    field = new Field();

    description = new TokenDescription("KEK");

    emptyCellTexture = new sf::Texture();
    for(int i=0;i<4;i++) {
        arrowsTextures[i] = new sf::Texture();
        tokenTextures[i] = new sf::Texture();
    }
}

GameField::~GameField() {
    delete description;
    delete emptyCellTexture;
    int size = field->getSize();
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            delete fieldCells[i][j];
            delete squareTextures[i][j];
        }
    }
    for(int i=0;i<4;i++) {
        delete arrowsTextures[i];
        delete tokenTextures[i];
    }
    delete field;
}

void GameField::turn(int fromx, int fromy, int tox, int toy) {
    field->doTurn(fromx, fromy, tox, toy);
    resetTextures(true, showGoal);
}

Action GameField::click(int x, int y) {
    Action *action;
    int arrows[4][3] = {{ 0, -1, 0},
                        { 1,  0, 1},
                        { 0,  1, 2},
                        {-1,  0, 3}};
    int newx, newy;
    action = new Action(x, y, x, y);
    if(field->isToken(x, y, showGoal) && !showGoal) {
        resetTextures(true, false);
        for(int i=0;i<4;i++) {
            newx = x + arrows[i][0];
            newy = y + arrows[i][1];
            while(newx>=0 && newx<field->getSize() && newy>=0 && newy<field->getSize() && field->getCellType(newx, newy, false)==EMPTY) {
                fieldCells[newx][newy]->setTexture(*arrowsTextures[arrows[i][2]]);
                field->setCell(newx, newy, arrows[i][2] + 3);
                newx += arrows[i][0];
                newy += arrows[i][1];
            }
        }
    } else if(field->getCellType(x, y, showGoal)==ARROW) {
        int swapx = x, swapy = y, dir = field->getCellValue(x, y, showGoal) - 3;
        while(!field->isToken(swapx, swapy, showGoal)) {
            swapx-=arrows[dir][0];
            swapy-=arrows[dir][1];
        }
        delete action;
        action = new Action(swapx, swapy, x, y);
        field->doTurn(x, y, swapx, swapy);
        resetTextures(true, showGoal);
        click(x, y);
    } else if(field->getCellType(x, y, showGoal)==NONE) {
        unHighlightAll();
        resetTextures(true, showGoal);
    }
    fieldCells[x][y]->setColor(sf::Color::Cyan);
    return Action(*action);
}

void GameField::resetTextures(bool clearArrows, bool showGoal) {
    if(clearArrows) {
        field->clearFromArrows();
    }
    //CellType{None, Empty, Black, White, Arrow};

    int size = field->getSize();
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            switch(field->getCellType(i, j, showGoal)) {
                case NONE:
                    break;
                case EMPTY:
                    fieldCells[i][j]->setTexture(*emptyCellTexture);
                    break;
                case BLACK:
                    fieldCells[i][j]->setTexture(*tokenTextures[0]);
                    break;
                case WHITE:
                    fieldCells[i][j]->setTexture(*tokenTextures[1]);
                    break;
                case ARROW:
                    fieldCells[i][j]->setTexture(*arrowsTextures[field->getCellValue(i, j, showGoal)-3]);
                    break;
            }
        }
    }
}

std::string GameField::getProgress() const {
    std::ostringstream ostr;
    ostr << field->getProgress() << "/" << field->getMaxProgress();
    return ostr.str();
}

int GameField::getSize() const {
    return field->getSize();
}

Field GameField::getField() const {
    return (*field);
}

void GameField::highlightCell(int x, int y, int mouseX, int mouseY) {
    if(highlighted) {
        int size = field->getSize();
        for(int i=0;i<size;i++) {
            for(int j=0;j<size;j++) {
                fieldCells[i][j]->setColor(sf::Color::White);
            }
        }
    }
    fieldCells[x][y]->setColor(sf::Color::Cyan);
    highlighted = true;
    showDescription = false;
    if(field->isToken(x, y, showGoal)) {
        std::ostringstream ostr;
        showDescription = true;
        description->setPosition(mouseX, mouseY);
        if(field->getCellType(x, y, showGoal)==BLACK) {
            ostr << field->getCellValue(x, y, showGoal);
            description->setColor(sf::Color(58, 45, 66));
        } else if(field->getCellType(x, y, showGoal)==WHITE) {
            ostr << field->getCellValue(x, y, showGoal);
            description->setColor(sf::Color(72, 138, 102));
        }
        description->setText(ostr.str());
    }
}

void GameField::unHighlightAll() {
    if(highlighted) {
        resetTextures(false, showGoal);
        int size = field->getSize();
        for(int i=0;i<size;i++) {
            for(int j=0;j<size;j++) {
                fieldCells[i][j]->setColor(sf::Color::White);
                squareTextures[i][j]->setColor(sf::Color::White);
            }
        }
        highlighted = false;
        showDescription = false;
    }
}

void GameField::unHighlight() {
    resetTextures(true, showGoal);
    showDescription = false;
    highlighted = false;
}

void GameField::setViewGoal(bool bshowGoal) {
    showGoal = bshowGoal;
    resetTextures(true, showGoal);
}

void GameField::hideTip() {
    showDescription = false;
}

void GameField::load(SaveLoader &loader, const ImageManager &imageManager) {
    loader.load(*field);
    for(int i=0;i<4;i++) {
        *(arrowsTextures[i]) = imageManager.getArrowTexture(i);
        *(tokenTextures[i]) = imageManager.getTokenTexture(i);
    }
    *emptyCellTexture = imageManager.getCellTexture();
    int size = field->getSize();
    for(int i=0;i<size;i++) {
        fieldCells.push_back(std::vector<sf::Sprite*>(size));
        squareTextures.push_back(std::vector<sf::Sprite*>(size));
    }
    int fshift = (5-field->getSize())*24;
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            fieldCells[i][j] = new sf::Sprite();
            fieldCells[i][j]->setPosition(252+fshift+i*48, 190+fshift+j*48);
            squareTextures[i][j] = new sf::Sprite();
            squareTextures[i][j]->setPosition(252+fshift+i*48, 190+fshift+j*48);
            if(field->getCellType(i, j, showGoal)!=NONE) {
                squareTextures[i][j]->setTexture(*emptyCellTexture);
            }
        }
    }
    resetTextures(true, showGoal);
}

void GameField::draw(sf::RenderWindow &window) {
    int size = field->getSize();
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if(field->isToken(i, j, showGoal) || field->getCellType(i, j, showGoal)==ARROW) {
                window.draw(*squareTextures[i][j]);
            }
            if(field->getCellType(i, j, showGoal)!=NONE) {
                window.draw(*fieldCells[i][j]);
            }
        }
    }
    if(showDescription) {
        description->draw(window);
    }
}
