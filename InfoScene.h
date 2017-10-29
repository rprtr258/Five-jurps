#ifndef INFOSCENE_H
#define INFOSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class InfoScene:public Scene {
    public:
        InfoScene();
        virtual ~InfoScene();

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);

        virtual void load(const ImageManager &imageManager);
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);
    private:
};

#endif
