#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class SettingsScene:public Scene {
    public:
        SettingsScene();
        virtual ~SettingsScene();

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);

        virtual void load();
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);
    private:
};

#endif
