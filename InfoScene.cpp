#include "InfoScene.h"

InfoScene::InfoScene() {

}

InfoScene::~InfoScene() {

}

void InfoScene::load() {
    Scene::load("img\\backgrounds\\info.png");
}

void InfoScene::updateScene() {

}

SceneChange InfoScene::clickAt(int x, int y) {
    return MENU_SCENE;
}

void InfoScene::mouseAt(int x, int y) {

}

void InfoScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
