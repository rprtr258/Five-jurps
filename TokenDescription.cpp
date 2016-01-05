#include "TokenDescription.h"

TokenDescription::TokenDescription(const std::string &text) {
    font = new sf::Font();
    font->loadFromFile("times.ttf");
    descriptionText = new sf::Text(text, *font, 25);
    descriptionText->setColor(sf::Color(235, 78, 239));
    descriptionText->setPosition(0, 0);
    descriptionText->setStyle(sf::Text::Style::Italic | sf::Text::Style::Bold);

    backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile("img\\token_tip.png");

    backgroundSprite = new sf::Sprite();
    backgroundSprite->setTexture(*backgroundTexture);
    backgroundSprite->setPosition(0, 0);
    backgroundSprite->setColor(sf::Color(155, 165, 155));
}

TokenDescription::~TokenDescription() {
    delete descriptionText;
    delete font;
    delete backgroundTexture;
    delete backgroundSprite;
}

void TokenDescription::setPosition(int x, int y) {
    descriptionText->setPosition(x+25, y-25);
    backgroundSprite->setPosition(x+20, y-20);
}

void TokenDescription::setText(const std::string &text) {
    descriptionText->setString(text);
}

void TokenDescription::setColor(sf::Color color) {
    backgroundSprite->setColor(color);
}

void TokenDescription::draw(sf::RenderWindow &window) {
    window.draw(*backgroundSprite);
    window.draw(*descriptionText);
}
