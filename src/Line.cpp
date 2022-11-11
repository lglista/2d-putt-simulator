#include <cmath>
#include "Utils.hpp"
#include "Line.hpp"

Line::Line(){}

float Line::distanceToPoint(sf::Vector2f point) {
    // Return minimum distance between line segment vw and point p
    const float l2 = Utils::distanceBetweenVectorsSquared(sf::Vector2f(startPoint.x, startPoint.y),
                                                            sf::Vector2f(endPoint.x, endPoint.y));
    if (l2 == 0.0) return Utils::distanceBetweenVectors(point,
                                                        sf::Vector2f(startPoint.x, startPoint.y));   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line. 
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    const float t = std::max(0.0f, std::min(1.0f,
             Utils::dotProduct(point - startPoint, endPoint - startPoint) / l2));
    const sf::Vector2f projection = startPoint + t * (endPoint - startPoint);  // Projection falls on the segment
    return Utils::distanceBetweenVectors(point, projection);
}

VerticalLine::VerticalLine(float x, float y, float length)
{
    startPoint.x = x;
    startPoint.y = y;
    endPoint.x = x;
    endPoint.y = y + length;
    flipX = true;
    flipY = false;
}

HorizontalLine::HorizontalLine(float x, float y, float length)
{
    startPoint.x = x;
    startPoint.y = y;
    endPoint.x = x + length;
    endPoint.y = y;
    flipX = false;
    flipY = true;
}
