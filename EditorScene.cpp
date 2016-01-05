#include "EditorScene.h"

EditorScene::EditorScene() {

}

EditorScene::~EditorScene() {

}

void EditorScene::load() {
    Scene::load("img\\backgrounds\\editor.png");
}

void EditorScene::updateScene() {

}

SceneChange EditorScene::clickAt(int x, int y) {
    return MENU_SCENE;
}

void EditorScene::mouseAt(int x, int y) {

}

void EditorScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
}
