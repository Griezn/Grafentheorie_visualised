//
// Created by seppe on 10/19/2022.
//

#include "Graaf.h"

Knoop::Knoop(float x, float y):graad_(0), shape_(3.f){
    this->setOrigin(shape_.getRadius(), shape_.getRadius());
    this->setPosition(x, y);
}

void Knoop::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();

    target.draw(shape_, states);
}

void Knoop::select() {
    shape_.setFillColor(sf::Color::Red);
}

void Knoop::unSelect() {
    shape_.setFillColor(sf::Color::White);
}

///////////////////////////////////////////////////////

Boog::Boog(Knoop* k1, Knoop* k2):gewicht(1){
    knopen_ = {k1, k2};
    line_[0] = sf::Vertex(k1->getPosition());
    line_[1] = sf::Vertex(k2->getPosition());

    k1->bogen_.emplace_back(this);
    k1->graad_++;
    k2->bogen_.emplace_back(this);
    k2->graad_++;
}

Boog::Boog(Knoop& k1, Knoop& k2, int gewicht) : gewicht(gewicht) {
    knopen_ = {&k1, &k2};
    line_[0] = sf::Vertex(k1.getPosition());
    line_[1] = sf::Vertex(k2.getPosition());

    k1.bogen_.emplace_back(this);
    k1.graad_++;
    k2.bogen_.emplace_back(this);
    k2.graad_++;
}

void Boog::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(line_, 2, sf::Lines );
}

///////////////////////////////////////////////////////

void Graaf::addKnoop(float x, float y) {
    this->knopen_.emplace_back(x, y);
}

void Graaf::addBoog(float x, float y) {
    auto k = findKnoop(x, y);

    if (k != nullptr){
        k->select();
        temp.emplace_back(k);
    }

    if (temp.size() == 2){
        temp[0]->unSelect();
        temp[1]->unSelect();

        this->bogen_.emplace_back(temp[0], temp[1]);
        temp.clear();
    }
}

void Graaf::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto& knoop : knopen_){
        target.draw(knoop, states);
    }
    for (const auto& boog : bogen_){
        target.draw(boog, states);
    }
}

Knoop *Graaf::findKnoop(float x, float y) {
    for (auto& knoop:knopen_) {
        if (x >= knoop.getPosition().x - 3 && x <= knoop.getPosition().x + 3) {
            if (y >= knoop.getPosition().y - 3 && y <= knoop.getPosition().y + 3) {
                return &knoop;
            }
        }
    }
    return nullptr;
}

