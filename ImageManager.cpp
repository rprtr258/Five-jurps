#include "ImageManager.h"

ImageManager::ImageManager() {
    tokensImage->loadFromFile("img\\tokens.png");
}

ImageManager::~ImageManager() {
    delete tokensImage;
}

sf::Texture ImageManager::getArrowTexture(int id) const {
    sf::Texture arrowTexture;
    arrowTexture.loadFromImage(*tokensImage, sf::IntRect(id * 48, 0, 48, 48));
    return arrowTexture;
}

sf::Texture ImageManager::getTokenTexture(int id) const {
    sf::Texture tokenTexture;
    tokenTexture.loadFromImage(*tokensImage, sf::IntRect(id * 48, 48, 48, 48));
    return tokenTexture;
}

sf::Texture ImageManager::getCellTexture() const {
    sf::Texture cellTexture;
    cellTexture.loadFromImage(*tokensImage, sf::IntRect(0, 144, 48, 48));
    return cellTexture;
}
