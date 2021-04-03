#include "Scene.h"

Scene::Scene() {
    ;
}

Scene::~Scene() {
    delete backgroundSprite;
    delete backgroundTexture;
}

void Scene::load(const char* backgroundPath) {
    backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile(backgroundPath);
    backgroundSprite = new sf::Sprite();
    backgroundSprite->setTexture(*backgroundTexture);
    backgroundSprite->setPosition(0.0f, 0.0f);
}

void Scene::draw(sf::RenderWindow &window) {
    window.draw(*backgroundSprite);
}
