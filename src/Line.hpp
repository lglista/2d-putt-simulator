#pragma once

#include <SFML/Graphics.hpp>

class Line{
public:
    Line();
    float distanceToPoint(sf::Vector2f point);
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    bool flipX;
    bool flipY;
};

class VerticalLine : public Line {
public:
    VerticalLine(float x, float y, float length);
};

class HorizontalLine : public Line {
public:
    HorizontalLine(float x, float y, float length);
};
