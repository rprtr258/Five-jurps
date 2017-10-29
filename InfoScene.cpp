#include "InfoScene.h"

InfoScene::InfoScene() {

}

InfoScene::~InfoScene() {

}

void InfoScene::load(const ImageManager &imageManager) {
    Scene::load("img\\backgrounds\\info.png");
}

void InfoScene::updateScene() {

}

SceneChange InfoScene::clickAt(int x, int y) {
    if(x>=15 && x<=64 && y>=29 && y<=78) {
        return MENU_SCENE;
    }
    if(x>=580 && x<=739 && y>=32 && y<=79) {
        return ABOUT_SCENE;
    }
    return NO_CHANGE;
}

void InfoScene::mouseAt(int x, int y) {

}

void InfoScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
