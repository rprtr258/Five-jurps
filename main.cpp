#include "View.h"
#include "Model.h"
#include "Controller.h"

int main() {
    View view;
    Controller controller;
    Model model;
    model.resetView(view);
    while (view.getWindow().isOpen()) {
        sf::Event event;
        while(view.getWindow().pollEvent(event)) {
            if(event.type==sf::Event::Closed) {
                view.getWindow().close();
            } else {
                controller.proccesEvent(event, model);
            }
        }
        if(view.getWindow().isOpen()) {
            model.update();
            view.getWindow().clear();
            view.draw();
            view.getWindow().display();
        }
    }
    return 0;
}
