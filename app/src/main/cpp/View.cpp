#include "View.h"

View::View() {
    mainWindow = new sf::RenderWindow();
    mainWindow->create(sf::VideoMode(800, 600), "Five for five", sf::Style::Titlebar | sf::Style::Close);
    currentScene = NULL;
}

View::~View() {
    delete mainWindow;
}

sf::RenderWindow& View::getWindow() {
    return *mainWindow;
}

void View::setScene(Scene* newScene) {
    currentScene = newScene;
}

Scene* View::getScene() {
    return currentScene;
}

void View::closeWindow() {
    mainWindow->close();
}

void View::draw() {
    currentScene->draw(*mainWindow);
}
