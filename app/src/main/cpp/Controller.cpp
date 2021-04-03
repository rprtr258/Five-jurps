#include "Controller.h"

Controller::Controller() {
    ;
}
void Controller::proccesEvent(sf::Event& event, Model& model) {
    if(event.type == sf::Event::MouseMoved) {
        model.movedMouse(event.mouseMove);
    } else if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            model.click(event.mouseButton.x, event.mouseButton.y);
        }
    }
}
