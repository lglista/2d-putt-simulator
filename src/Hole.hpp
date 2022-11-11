#pragma once

#include <SFML/Graphics.hpp>

class Hole{
public:
    float radius;
    sf::Vector2f location;

    Hole() {
        radius = 10;
        location.x = 500;
        location.y = 500;
    }

    Hole(float _radius, sf::Vector2f _location) : radius(_radius), location(_location) {}
};