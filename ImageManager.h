#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <SFML/Graphics.hpp>

class ImageManager {
    public:
        ImageManager();
        ~ImageManager();

        sf::Texture getArrowTexture(int id) const;
        sf::Texture getTokenTexture(int id) const;
        sf::Texture getCellTexture() const;
    private:
        sf::Image *tokensImage;
};

#endif
