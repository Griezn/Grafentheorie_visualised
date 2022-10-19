//
// Created by seppe on 10/19/2022.
//

#ifndef GRAFEN_GRAAF_H
#define GRAFEN_GRAAF_H
#include <SFML/Graphics.hpp>

class Knoop;
class Boog;

class Knoop : public sf::Drawable, public sf::Transformable{
public:
    Knoop(float x, float y);

    void select();
    void unSelect();

    int graad_;

    std::vector<Boog*> bogen_;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::CircleShape shape_;
};

///////////////////////////////////////////////////////

class Boog : public sf::Drawable, public sf::Transformable{
public:
    Boog(Knoop* k1, Knoop* k2);
    Boog(Knoop& k1, Knoop& k2, int gewicht);

    int gewicht;

    std::pair<Knoop*, Knoop*> knopen_;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vertex line_[2];
};

///////////////////////////////////////////////////////

class Graaf : public sf::Drawable{
public:
    Graaf() = default;

    void addKnoop(float x, float y);
    void addBoog(float x, float y);
    Knoop* findKnoop(float x, float y);

protected:
    std::vector<Knoop> knopen_;
    std::vector<Boog> bogen_;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<Knoop*> temp;

};


#endif //GRAFEN_GRAAF_H
