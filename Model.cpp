#include "Model.h"

Model::Model() {
    currentScene = new MenuScene();
    currentScene->load();
}

Model::~Model() {
    delete currentScene;
}

void Model::update() {

}

void Model::resetView(View& curView) {
    view = &curView;
    view->setScene(currentScene);
}

void Model::click(int x, int y) {
    SceneChange change = currentScene->clickAt(x, y);
    if(change!=NO_CHANGE && change!=QUIT_GAME) delete currentScene;
    switch(change) {
        case GAME_SCENE:
            currentScene = new GameScene();
            break;
        case MENU_SCENE:
            currentScene = new MenuScene();
            break;
        case INFO_SCENE:
            currentScene = new InfoScene();
            break;
        case EDITOR_SCENE:
            currentScene = new EditorScene();
            break;
        case WIN_SCENE:
            currentScene = new WinScene();
            break;
        case SETTINGS_SCENE:
            currentScene = new SettingsScene();
            break;
        case QUIT_GAME:
            view->closeWindow();
            break;
        case NO_CHANGE:
            break;
    }
    if(change!=NO_CHANGE && change!=QUIT_GAME) {
        currentScene->load();
        view->setScene(currentScene);
    }
}

void Model::movedMouse(const sf::Event::MouseMoveEvent& info) {
    currentScene->mouseAt(info.x, info.y);
}
