#include <cmath>
#include <cfloat>
#include "Utils.hpp"
#include "GolfBall.hpp"

GolfBall::GolfBall()
{
    startingLocation = sf::Vector2f(0, 0);
    currentLocation = sf::Vector2f(0, 0);
    velocity = sf::Vector2f(0, 0);
    radius = 4;
}

GolfBall::GolfBall(sf::Vector2f _startingLocation, sf::Vector2f _currentLocation, sf::Vector2f _velocity, float _radius) :
        startingLocation(_startingLocation), currentLocation(_currentLocation), velocity(_velocity),  radius(_radius){}

GolfBall::GolfBall(float x, float y, float _radius)
{
    startingLocation = sf::Vector2f(x, y);
    currentLocation = sf::Vector2f(0, 0);
    velocity = sf::Vector2f(0, 0);
    radius = _radius;
}

GolfBall::GolfBall(const GolfBall& g)
{
    startingLocation = sf::Vector2f(g.startingLocation.x, g.startingLocation.y);
    currentLocation = sf::Vector2f(0, 0);
    velocity = sf::Vector2f(0, 0);
    radius = g.radius;
}

void GolfBall::move()
{
    currentLocation.x += velocity.x;
    currentLocation.y += velocity.y;
    velocity.x *= 0.995f;
    velocity.y *= 0.995f;
    if (sqrtf(velocity.x * velocity.x + velocity.y * velocity.y) < 0.05 or
        std::isnan(velocity.x) or std::isnan(velocity.y))
    {
        velocity.x = 0;
        velocity.y = 0;
    }
}

void GolfBall::reset()
{
    currentLocation = sf::Vector2f(startingLocation.x, startingLocation.y);
    velocity.x = 0;
    velocity.y = 0;
}

bool GolfBall::isInHole(sf::Vector2f holeLocation, float holeRadius)
{
    if (Utils::distanceBetweenVectors(currentLocation, sf::Vector2f(holeLocation.x, holeLocation.y)) < holeRadius){
        float ballSpeed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
        if (ballSpeed < 1) {
            return true;
        }
    }
    return false;
}
