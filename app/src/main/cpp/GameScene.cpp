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

void GameScene::load(const ImageManager &imageManager) {
    loader = new SaveLoader("save.txt");

    Scene::load("img\\backgrounds\\game.png");

    menuButtonTexture = new sf::Texture();
    menuButtonTexture->loadFromFile("img\\buttons\\button_menu.png");

    menuButtonSprite = new sf::Sprite();
    menuButtonSprite->setTexture(*menuButtonTexture);
    menuButtonSprite->setPosition(36, 30);

    actionsButtonTexture = new sf::Texture();
    actionsButtonTexture->loadFromFile("img\\buttons\\button_actions.png");

    actionsButtonsSprite = new sf::Sprite();
    actionsButtonsSprite->setTexture(*actionsButtonTexture);
    actionsButtonsSprite->setPosition(426, 523);

    tipButtonTexture = new sf::Texture();
    tipButtonTexture->loadFromFile("img\\buttons\\button_tip.png");

    tipButtonSprite = new sf::Sprite();
    tipButtonSprite->setTexture(*tipButtonTexture);
    tipButtonSprite->setPosition(100, 30);

    field = new GameField();
    field->load(*loader, imageManager);

    font = new sf::Font();
    font->loadFromFile("fonts\\parsek.ttf");

    turnCounterText = new sf::Text("0", *font, 40);
    turnCounterText->setPosition(560, 515);
    turnCounterText->setColor(sf::Color::Black);

    progressText = new sf::Text(field->getProgress(), *font, 40);
    progressText->setPosition(30, 515);
    progressText->setColor(sf::Color::Blue);

    history = new ActionsHistory();
}

void GameScene::updateScene() {

}

SceneChange GameScene::clickAt(int x, int y) {
    SceneChange stateChange = NO_CHANGE;
    std::ostringstream ostr;
    if(menuButtonSprite->getGlobalBounds().contains(x, y))
        stateChange = MENU_SCENE;
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
    int fieldx = cellAtMouse(x, y).x, fieldy = cellAtMouse(x, y).y;
    if(fieldx>=0 && fieldx<field->getSize() && fieldy>=0 && fieldy<field->getSize()) {
        history->doAction(field->click(fieldx, fieldy));
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
    int fieldx = cellAtMouse(x, y).x, fieldy = cellAtMouse(x, y).y;
    if(fieldx>=0 && fieldx<field->getSize() && fieldy>=0 && fieldy<field->getSize()) {
        if((field->getField().getCellType(fieldx, fieldy, false)==ARROW && checkArrowBounds(x, y)) ||
           (field->getField().getCellType(fieldx, fieldy, false)!=ARROW)) {
            field->highlightCell(fieldx, fieldy, x, y);
        }
    }
}

sf::Vector2i GameScene::cellAtMouse(int x, int y) {
    int sx = 252+(5-field->getSize())*24, sy = 190+(5-field->getSize())*24;
    return sf::Vector2i((x-sx<0?-1:(x-sx)/48), (y-sy<0?-1:(y-sy)/48));
}

bool GameScene::checkArrowBounds(int x, int y) {
    int sx = 252+(5-field->getSize())*24, sy = 190+(5-field->getSize())*24;
    int fieldx = (x-sx<0?-1:(x-sx)/48), fieldy = (y-sy<0?-1:(y-sy)/48);
    int fx = sx + fieldx*48, fy = sy + fieldy*48;
    if(x>=fx+11 && x<=fx+48-13 &&
       y>=fy+11 && y<=fy+48-13) {
        return true;
    } else {
        return false;
    }
}

void GameScene::draw(sf::RenderWindow &window) {
    Scene::draw(window);
    window.draw(*actionsButtonsSprite);
    field->draw(window);
    window.draw(*progressText);
    window.draw(*turnCounterText);

    window.draw(*tipButtonSprite);
    window.draw(*menuButtonSprite);
}
