#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class MenuScene:public Scene {
    public:
        MenuScene();
        virtual ~MenuScene();
        virtual void load();
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);
    private:
        sf::Texture* buttonsTextures[5];
        sf::Sprite* buttonsSprites[5];
        const int BUTTON_Y_SHIFT = 200, BUTTON_X_SHIFT = 49, BUTTON_WIDTH = 160, BUTTON_HEIGHT = 48, BUTTON_SPACE = 80;
};

#endif
