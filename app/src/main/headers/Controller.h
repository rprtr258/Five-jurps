#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

#include "Model.h"

class Controller {
    public:
        Controller();
        void proccesEvent(sf::Event& event, Model& model);
};

#endif
