#include "GameScene.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {
    delete tipButtonTexture;
    delete tipButtonSprite;

    delete menuButtonTexture;
    delete menuButtonSprite;

    delete actionsButtonTexture;
    delete actionsButtonsSprite;

    delete turnCounterText;
    delete font;
    delete progressText;
    delete history;
    delete loader;
}

void GameScene::load() {
    loader = new SaveLoader("save.txt");

    Scene::load("img\\backgrounds\\game.png");

    menuButtonTexture = new sf::Texture();
    menuButtonTexture->loadFromFile("img\\button_menu.png");

    menuButtonSprite = new sf::Sprite();
    menuButtonSprite->setTexture(*menuButtonTexture);
    menuButtonSprite->setPosition(36, 30);

    actionsButtonTexture = new sf::Texture();
    actionsButtonTexture->loadFromFile("img\\button_actions.png");

    actionsButtonsSprite = new sf::Sprite();
    actionsButtonsSprite->setTexture(*actionsButtonTexture);
    actionsButtonsSprite->setPosition(426, 523);

    tipButtonTexture = new sf::Texture();
    tipButtonTexture->loadFromFile("img\\button_tip.png");

    tipButtonSprite = new sf::Sprite();
    tipButtonSprite->setTexture(*tipButtonTexture);
    tipButtonSprite->setPosition(100, 30);

    field = new GameField();
    field->load(*loader);

    font = new sf::Font();
    font->loadFromFile("parsek.ttf");

    turnCounterText = new sf::Text("0", *font, 40);
    turnCounterText->setPosition(560, 515);
    turnCounterText->setColor(sf::Color::Black);

    progressText = new sf::Text("0%", *font, 40);
    progressText->setPosition(30, 515);
    progressText->setColor(sf::Color::Blue);

    history = new ActionsHistory();
}

void GameScene::updateScene() {

}

SceneChange GameScene::clickAt(int x, int y) {
    SceneChange stateChange = NO_CHANGE;
    std::ostringstream ostr;
    if(menuButtonSprite->getGlobalBounds().contains(x, y)) stateChange = MENU_SCENE;
    if(actionsButtonsSprite->getGlobalBounds().contains(x, y)) {
        if(x<actionsButtonsSprite->getGlobalBounds().left+116) { //undo
            history->undo(*field);
        } else if(x>actionsButtonsSprite->getGlobalBounds().left+212) { //redo
            history->redo(*field);
        }
    }
    if(tipButtonSprite->getGlobalBounds().contains(x, y)) {
        showTip = !showTip;
        field->setViewGoal(showTip);
    }
    int fieldx = (x - 252-(5.0-field->getSize())*24.0)/48, fieldy = (y - 178-(5.0-field->getSize())*24.0)/48;
    if(x-252-(5.0-field->getSize())*24.0>=0 && y-178-(5.0-field->getSize())*24.0>=0 && fieldx>=0 && fieldx<field->getSize() && fieldy>=0 && fieldy<field->getSize()) {
        history->doAction(field->click(fieldx, fieldy, x, y));
    } else {
        field->unHighlight();
    }
    ostr << history->getTurnsCount();
    turnCounterText->setString(ostr.str());
    progressText->setString(field->getProgress());
    return stateChange;
}

void GameScene::mouseAt(int x, int y) {
    menuButtonSprite->setColor(sf::Color::White);
    tipButtonSprite->setColor(sf::Color::White);
    actionsButtonsSprite->setColor(sf::Color::White);
    field->unHighlightAll();

    if(menuButtonSprite->getGlobalBounds().contains(x, y)) {
        menuButtonSprite->setColor(sf::Color::Red);
    }
    if(tipButtonSprite->getGlobalBounds().contains(x, y)) {
        tipButtonSprite->setColor(sf::Color::Red);
    }
    sf::FloatRect action = actionsButtonsSprite->getGlobalBounds();
    if(action.contains(x, y) && (x<action.left+116 || x>action.left+212)) {
        actionsButtonsSprite->setColor(sf::Color::Red);
    }
    int fieldx = (x - 252-(5.0-field->getSize())*24.0)/48, fieldy = (y - 178-(5.0-field->getSize())*24.0)/48;
    if(x-252>=0 && y-178>=0 && fieldx>=0 && fieldx<field->getSize() && fieldy>=0 && fieldy<field->getSize()) {
        field->highlightCell(fieldx, fieldy, x, y);
    }
}

void GameScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
    window.draw(*menuButtonSprite);
    window.draw(*actionsButtonsSprite);
    field->draw(window);
    window.draw(*progressText);
    window.draw(*turnCounterText);
    window.draw(*tipButtonSprite);
}
