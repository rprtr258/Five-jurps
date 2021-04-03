#include "SettingsScene.h"

SettingsScene::SettingsScene() {

}

SettingsScene::~SettingsScene() {

}

void SettingsScene::load(const ImageManager &imageManager) {
    Scene::load("img\\backgrounds\\settings.png");
}

void SettingsScene::updateScene() {

}

SceneChange SettingsScene::clickAt(int x, int y) {
    return MENU_SCENE;
}

void SettingsScene::mouseAt(int x, int y) {

}

void SettingsScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
