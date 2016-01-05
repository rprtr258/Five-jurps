#ifndef WINSCENE_H
#define WINSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class WinScene:public Scene {
    public:
        WinScene();
        virtual ~WinScene();

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);

        virtual void load();
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);
    private:
};

#endif
