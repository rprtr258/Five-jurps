#include "MenuScene.h"

MenuScene::MenuScene() {

}

MenuScene::~MenuScene() {
    for(int i=0;i<5;i++) {
        delete buttonsSprites[i];
        delete buttonsTextures[i];
    }
}

void MenuScene::load() {
    Scene::load("img\\backgrounds\\menu.png");
    for(int i=0;i<5;i++) {
        buttonsTextures[i] = new sf::Texture();
        buttonsSprites[i] = new sf::Sprite();
    }
    buttonsTextures[0]->loadFromFile("img\\button_play.png");
    buttonsTextures[1]->loadFromFile("img\\button_info.png");
    buttonsTextures[2]->loadFromFile("img\\button_editor.png");
    buttonsTextures[3]->loadFromFile("img\\button_settings.png");
    buttonsTextures[4]->loadFromFile("img\\button_quit.png");
    for(int i=0;i<5;i++) {
        buttonsSprites[i]->setTexture(*buttonsTextures[i]);
        buttonsSprites[i]->setPosition(BUTTON_X_SHIFT, BUTTON_Y_SHIFT+BUTTON_SPACE*i);
    }
}

void MenuScene::updateScene() {

}

SceneChange MenuScene::clickAt(int x, int y) {
    if(y>=BUTTON_Y_SHIFT + 0*BUTTON_SPACE && y<=BUTTON_Y_SHIFT + BUTTON_HEIGHT + 0*BUTTON_SPACE &&
       x>=BUTTON_X_SHIFT && x<=BUTTON_X_SHIFT + BUTTON_WIDTH) {
        return GAME_SCENE;
    }
    if(y>=BUTTON_Y_SHIFT + 1*BUTTON_SPACE && y<=BUTTON_Y_SHIFT + BUTTON_HEIGHT + 1*BUTTON_SPACE &&
       x>=BUTTON_X_SHIFT && x<=BUTTON_X_SHIFT + BUTTON_WIDTH) {
        return INFO_SCENE;
    }
    if(y>=BUTTON_Y_SHIFT + 2*BUTTON_SPACE && y<=BUTTON_Y_SHIFT + BUTTON_HEIGHT + 2*BUTTON_SPACE &&
       x>=BUTTON_X_SHIFT && x<=BUTTON_X_SHIFT + BUTTON_WIDTH) {
        return EDITOR_SCENE;
    }
    if(y>=BUTTON_Y_SHIFT + 3*BUTTON_SPACE && y<=BUTTON_Y_SHIFT + BUTTON_HEIGHT + 3*BUTTON_SPACE &&
       x>=BUTTON_X_SHIFT && x<=BUTTON_X_SHIFT + BUTTON_WIDTH) {
        return SETTINGS_SCENE;
    }
    if(y>=BUTTON_Y_SHIFT + 4*BUTTON_SPACE && y<=BUTTON_Y_SHIFT + BUTTON_HEIGHT + 4*BUTTON_SPACE &&
       x>=BUTTON_X_SHIFT && x<=BUTTON_X_SHIFT + BUTTON_WIDTH) {
        return QUIT_GAME;
    }
    return NO_CHANGE;
}

void MenuScene::mouseAt(int x, int y) {
    int button = -1;
    for(int i=0;i<5;i++) {
        if(buttonsSprites[i]->getGlobalBounds().contains(x, y)) {
            buttonsSprites[i]->setColor(sf::Color::Red);
            button = i;
        }
    }
    for(int i=0;i<5;i++) {
        if(i!=button) {
            buttonsSprites[i]->setColor(sf::Color::White);
        }
    }
}

void MenuScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
    for(int i=0;i<5;i++) {
        window.draw(*buttonsSprites[i]);
    }
}
