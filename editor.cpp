/*
    Lawrence Glista
    Show the hole
    10/09/2022
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cfloat>
#include "./src/HoleSetup.hpp"
#include "./src/Utils.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2){
        cerr << "Missing hole name in command line\n";
        exit(-1);
    }

    HoleSetup holeSetup = HoleSetup(string(argv[1]) + ".settings", string(argv[1]) + ".hole");
    sf::RenderWindow window(sf::VideoMode(holeSetup.widthOfWindow, holeSetup.heightOfWindow), "Putt Visualizer");

    sf::RectangleShape background(sf::Vector2f(holeSetup.widthOfWindow, holeSetup.heightOfWindow));
    background.setFillColor(sf::Color(0, 135, 5));


    sf::CircleShape hole(holeSetup.hole.radius);
    hole.setPosition(holeSetup.hole.location.x, holeSetup.hole.location.y);
    hole.setFillColor(sf::Color::Black);


    sf::CircleShape ball(4);
    ball.setPosition(holeSetup.golfBall.startingLocation.x, holeSetup.golfBall.startingLocation.y);
    ball.setFillColor(sf::Color::White);

    vector<sf::RectangleShape> walls;

    for (auto &line : holeSetup.walls)
    {
        float width = line.endPoint.x - line.startPoint.x;
        float height = line.endPoint.y - line.startPoint.y;
        if (width == 0) width = 5;
        if (height == 0) height = 5;
        sf::RectangleShape wall(sf::Vector2f(width, height));
        wall.setPosition(line.startPoint.x, line.startPoint.y);
        wall.setFillColor(sf::Color(107, 79, 0));
        walls.push_back(wall);
    }

    window.display();
    
    while (window.isOpen())
    {
        window.clear();
        window.draw(background);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto &wall : walls)
        {
            window.draw(wall);
        }

        window.draw(hole);
        window.draw(ball);
        window.display();
    }
    return 0;
}
