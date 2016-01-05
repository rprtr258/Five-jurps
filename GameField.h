#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <sstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "TokenDescription.h"
#include "Action.h"
#include "Field.h"
#include "SaveLoader.h"

class GameField {
    public:
        GameField();
        ~GameField();
        Action click(int x, int y, int concrx, int concry);
        void turn(int fromx, int fromy, int tox, int toy);
        void highlightCell(int x, int y, int mouseX, int mouseY);
        void unHighlightAll();
        void unHighlight();
        void setViewGoal(bool bshowGoal);
        void hideTip();
        void resetTextures(bool clearArrows, bool showGoal);
        int getSize() const;
        std::string getProgress() const;
        void load(SaveLoader &loader);
        void draw(sf::RenderWindow &window);
    private:
        bool highlighted = false, showDescription = false, showGoal = false;
        TokenDescription *description;
        std::vector<std::vector<sf::Sprite*> > fieldCells, squareTextures;
        sf::Texture *emptyCellTexture, *arrowsTextures[4], *tokenTextures[2];
        Field *field;
        //10-19 - Black Tokens
        //20-29 - White tokens
        //-1    - Nothing
        //0     - Empty cell
        //3-6   - Arrows
};

#endif
