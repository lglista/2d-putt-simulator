#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Utils
{
    float distanceBetweenVectorsSquared(sf::Vector2f a, sf::Vector2f b);
    float distanceBetweenVectors(sf::Vector2f a, sf::Vector2f b);
    float dotProduct(sf::Vector2f a, sf::Vector2f b);
    sf::Color HSVtoRGB(float H, float S, float V);
    sf::Color distanceToRGB(float distance, float maxDistance);
}
