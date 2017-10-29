#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <SFML/Graphics.hpp>

#include "Scene.h"

class EditorScene:public Scene {
    public:
        EditorScene();
        virtual ~EditorScene();

        virtual SceneChange clickAt(int x, int y);
        virtual void mouseAt(int x, int y);

        virtual void load(const ImageManager &imageManager);
        virtual void updateScene();
        virtual void draw(sf::RenderWindow &window);
    private:
};

#endif
