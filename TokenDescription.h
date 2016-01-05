#ifndef TOKENDESCRIPTION_H
#define TOKENDESCRIPTION_H

#include <string>

#include <SFML/Graphics.hpp>

class TokenDescription {
    public:
        TokenDescription(const std::string &text);
        ~TokenDescription();
        void setPosition(int x, int y);
        void setText(const std::string &text);
        void setColor(sf::Color color);
        void draw(sf::RenderWindow &window);
    private:
        sf::Text *descriptionText;
        sf::Font *font;
        sf::Texture *backgroundTexture;
        sf::Sprite *backgroundSprite;
};

#endif
