#include "AboutScene.h"

AboutScene::AboutScene() {

}

AboutScene::~AboutScene() {

}

void AboutScene::load(const ImageManager &imageManager) {
    Scene::load("img\\backgrounds\\about.png");
}

void AboutScene::updateScene() {

}

SceneChange AboutScene::clickAt(int x, int y) {
    if(x>=29 && x<=78 && y>=27 && y<=76) {
        return MENU_SCENE;
    }
    return NO_CHANGE;
}

void AboutScene::mouseAt(int x, int y) {

}

void AboutScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
