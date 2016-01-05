#ifndef SCENE_H
#define SCENE_H

#include <string>

#include <SFML/Graphics.hpp>

#include "SceneChange.h"

class Scene {
    public:
        Scene();
        virtual ~Scene();

        void load(const char* backgroundPath);

        virtual void load() = 0;
        virtual void updateScene() = 0;
        virtual void draw(sf::RenderWindow &window);

        virtual SceneChange clickAt(int x, int y) = 0;
        virtual void mouseAt(int x, int y) = 0;
    protected:
        sf::Sprite* backgroundSprite;
        sf::Texture* backgroundTexture;
};

#endif
