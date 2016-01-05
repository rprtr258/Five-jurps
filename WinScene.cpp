#include "WinScene.h"

WinScene::WinScene() {

}

WinScene::~WinScene() {

}

void WinScene::load() {
    Scene::load("img\\backgrounds\\win.png");
}

void WinScene::updateScene() {

}

SceneChange WinScene::clickAt(int x, int y) {
    return MENU_SCENE;
}

void WinScene::mouseAt(int x, int y) {

}

void WinScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
