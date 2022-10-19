#ifndef FOURIER_ENGINE_H
#define FOURIER_ENGINE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "grafen/Graaf.h"

enum class state{
    RUN,
    EXIT,
    POINT,
    LINE
};

class Engine{
public:
    Engine();

    void run();

private:
    std::shared_ptr<sf::RenderWindow> window_;
    int width_, height_;

    sf::Event event_;
    state currentState_;

    void pollEvents();
    void mouseHandler(sf::Event& event);
    void render();

    Graaf g1;
};

Engine::Engine():
width_(1024),
height_(768),
currentState_(state::RUN),
event_(),
window_(nullptr)
{
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(width_, height_), "Grafen DEMO");
    window_->setFramerateLimit(60);
}

void Engine::run() {
    while (currentState_ != state::EXIT){
        pollEvents();
        render();
    }
}

void Engine::pollEvents() {
    while (this->window_->pollEvent(event_)){
        switch (event_.type) {
            case sf::Event::Closed:
                this->currentState_ = state::EXIT;
                break;
            case sf::Event::Resized:
                this->width_ = event_.size.width;
                this->height_ = event_.size.height;
                break;
            case sf::Event::MouseButtonPressed:
                if (event_.mouseButton.button == sf::Mouse::Button::Left){
                    mouseHandler(event_);
                }
                break;
            case sf::Event::KeyPressed:
                if (event_.key.code == sf::Keyboard::Key::P){
                    this->currentState_ = state::POINT;
                } else if(event_.key.code == sf::Keyboard::Key::L){
                    this->currentState_ = state::LINE;
                }
        }
    }
}

void Engine::render() {
    this->window_->clear();
    // draw calls

    this->window_->draw(g1);

    this->window_->display();
}

void Engine::mouseHandler(sf::Event& event) {
    switch (currentState_) {
        case state::POINT:
                g1.addKnoop(event_.mouseButton.x, event_.mouseButton.y);
            break;
        case state::LINE:
            g1.addBoog(event_.mouseButton.x, event_.mouseButton.y);
            break;
    }
}

#endif //FOURIER_ENGINE_H
