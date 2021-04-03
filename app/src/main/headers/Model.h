#ifndef MODEL_H
#define MODEL_H

#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EditorScene.h"
#include "InfoScene.h"
#include "AboutScene.h"
#include "SettingsScene.h"
#include "WinScene.h"
#include "ImageManager.h"
#include "View.h"

class Model {
    public:
        Model();
        ~Model();
        void update();
        void resetView(View& curView);
        void click(int x, int y);
        void movedMouse(const sf::Event::MouseMoveEvent& info);
    private:
        Scene* currentScene;
        View* view;
        ImageManager *imageManager;
};

#endif
