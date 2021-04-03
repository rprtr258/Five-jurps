#ifndef ABOUTSCENE_H
#define ABOUTSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class AboutScene:public Scene {
    public:
        AboutScene();
        virtual ~AboutScene();

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);

        virtual void load(const ImageManager &imageManager);
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);
    private:
};

#endif
