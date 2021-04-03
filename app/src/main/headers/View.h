#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Scene.h"

class View {
    public:
        View();
        ~View();
        sf::RenderWindow& getWindow();
        void setScene(Scene* newScene);
        Scene* getScene();
        void closeWindow();
        void draw();
    private:
        sf::RenderWindow *mainWindow;
        Scene *currentScene;
};

#endif
