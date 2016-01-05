#include "GameField.h"

GameField::GameField() {
    field = new Field();

    description = new TokenDescription("KEK");

    emptyCellTexture = new sf::Texture();
    emptyCellTexture->loadFromFile("img\\cell_empty.png");
    for(int i=0;i<4;i++) {
        arrowsTextures[i] = new sf::Texture();
    }
    arrowsTextures[0]->loadFromFile("img\\cell_arrow_up.png");
    arrowsTextures[1]->loadFromFile("img\\cell_arrow_right.png");
    arrowsTextures[2]->loadFromFile("img\\cell_arrow_down.png");
    arrowsTextures[3]->loadFromFile("img\\cell_arrow_left.png");

    tokenTextures[0] = new sf::Texture();
    tokenTextures[1] = new sf::Texture();
    tokenTextures[0]->loadFromFile("img\\cell_black_token.png");
    tokenTextures[1]->loadFromFile("img\\cell_white_token.png");
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
    }
    delete field;
    delete tokenTextures[0];
    delete tokenTextures[1];
}

void GameField::turn(int fromx, int fromy, int tox, int toy) {
    field->doTurn(fromx, fromy, tox, toy);
    resetTextures(true, showGoal);
}

Action GameField::click(int x, int y, int concrx, int concry) {
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
            while(newx>=0 && newx<field->getSize() && newy>=0 && newy<field->getSize() && field->getCellType(newx, newy, false)==Empty) {
                fieldCells[newx][newy]->setTexture(*arrowsTextures[arrows[i][2]]);
                field->setCell(newx, newy, arrows[i][2] + 3);
                newx += arrows[i][0];
                newy += arrows[i][1];
            }
        }
    } else if(concrx>=252+(5.0-field->getSize())*24.0+48*x+11 && concrx<=252+(5.0-field->getSize())*24.0+48*x+35 &&
              field->getCellType(x, y, showGoal)==Arrow) {
        int swapx = x, swapy = y, dir = field->getCellValue(x, y, showGoal) - 3;
        while(!field->isToken(swapx, swapy, showGoal)) {
            swapx-=arrows[dir][0];
            swapy-=arrows[dir][1];
        }
        delete action;
        action = new Action(swapx, swapy, x, y);
        field->doTurn(x, y, swapx, swapy);
        resetTextures(true, showGoal);
        click(x, y, concrx, concry);
    } else if(field->getCellType(x, y, showGoal)==None) {
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
                case None:
                    break;
                case Empty:
                    fieldCells[i][j]->setTexture(*emptyCellTexture);
                    break;
                case Black:
                    fieldCells[i][j]->setTexture(*tokenTextures[0]);
                    break;
                case White:
                    fieldCells[i][j]->setTexture(*tokenTextures[1]);
                    break;
                case Arrow:
                    fieldCells[i][j]->setTexture(*arrowsTextures[field->getCellValue(i, j, showGoal)-3]);
                    break;
            }
        }
    }
}

std::string GameField::getProgress() const {
    std::ostringstream ostr;
    ostr << field->getProgress()*100/field->getMaxProgress() << '%';
    return ostr.str();
}

int GameField::getSize() const {
    return field->getSize();
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
        if(field->getCellType(x, y, showGoal)==Black) {
            ostr << field->getCellValue(x, y, showGoal);
            description->setColor(sf::Color(58, 45, 66));
        } else if(field->getCellType(x, y, showGoal)==White) {
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

void GameField::load(SaveLoader &loader) {
    loader.load(*field);
    int size = field->getSize();
    for(int i=0;i<size;i++) {
        fieldCells.push_back(std::vector<sf::Sprite*>(size));
        squareTextures.push_back(std::vector<sf::Sprite*>(size));
    }
    float fshift = (5.0-field->getSize())*24.0;
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            fieldCells[i][j] = new sf::Sprite();
            fieldCells[i][j]->setPosition(252+fshift+i*48, 190+j*48);
            squareTextures[i][j] = new sf::Sprite();
            squareTextures[i][j]->setPosition(252+fshift+i*48, 190+j*48);
            if(field->getCellType(i, j, showGoal)!=None) {
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
            if(field->isToken(i, j, showGoal) || field->getCellType(i, j, showGoal)==Arrow) {
                window.draw(*squareTextures[i][j]);
            }
            if(field->getCellType(i, j, showGoal)!=None) {
                window.draw(*fieldCells[i][j]);
            }
        }
    }
    if(showDescription) {
        description->draw(window);
    }
}
