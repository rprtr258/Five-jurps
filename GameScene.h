#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <sstream>

#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "GameField.h"
#include "ActionsHistory.h"
#include "SaveLoader.h"

class GameScene:public Scene {
    public:
        GameScene();
        virtual ~GameScene();
        virtual void load(const ImageManager &imageManager);
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);
    private:
        sf::Vector2i cellAtMouse(int x, int y);
        bool checkArrowBounds(int x, int y);
    private:
        sf::Sprite *menuButtonSprite, *actionsButtonsSprite, *tipButtonSprite;
        sf::Texture *menuButtonTexture, *actionsButtonTexture, *tipButtonTexture;
        GameField *field;
        sf::Text *progressText, *turnCounterText;;
        sf::Font *font;
        bool showTip = false;
        ActionsHistory *history;
        SaveLoader *loader;
};

#endif
