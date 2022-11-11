#pragma once

#include <SFML/Graphics.hpp>

class GolfBall {
public:
    GolfBall();
    GolfBall(sf::Vector2f _startingLocation, sf::Vector2f _currentLocation, sf::Vector2f _velocity, float radius);
    GolfBall(float x, float y, float radius);
    GolfBall(const GolfBall& g);
    void move();
    void reset();
    bool isInHole(sf::Vector2f holeLocation, float radius);

    sf::Vector2f startingLocation;
    sf::Vector2f currentLocation;
    sf::Vector2f velocity;
    float radius;
};
