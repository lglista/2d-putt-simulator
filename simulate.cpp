/*
    Lawrence Glista
    Simulate a ball being putt at a hole
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
#include <thread>
#include "./src/HoleSetup.hpp"
#include "./src/Utils.hpp"
#include <memory>
#include <fstream>
#include <cstdio>

using namespace std;

void simulate(HoleSetup& holeSetup, int height_start, int height_end, string filename)
{
    unique_ptr<GolfBall> golfBall = make_unique<GolfBall>(holeSetup.golfBall);
    ofstream distance_file;
    distance_file.open(filename);
    for (int height_of_click = height_start; height_of_click < height_end; height_of_click += holeSetup.increment)
    {
        for (int width_of_click = 0; width_of_click < holeSetup.widthOfWindow; width_of_click += holeSetup.increment)
        {
            if (height_of_click == golfBall->startingLocation.y &&
                width_of_click == golfBall->startingLocation.x){
                    distance_file << "999999 ";
                    continue;
            }
            golfBall->reset();
            sf::Vector2f distanceVec(width_of_click - golfBall->startingLocation.x, height_of_click - golfBall->startingLocation.y);
            float length = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
            sf::Vector2f unitVec(distanceVec.x/length, distanceVec.y/length);
            golfBall->velocity.x = unitVec.x*abs(length / holeSetup.velocityDivisor);
            golfBall->velocity.y = unitVec.y*abs(length / holeSetup.velocityDivisor);

            bool stay_on_this_shot = true;
            while (stay_on_this_shot)
            {
                for (auto &line : holeSetup.walls) 
                {
                    if (line.distanceToPoint(golfBall->currentLocation) < golfBall->radius)
                    {
                        if (line.flipX)
                        {
                            if (golfBall->velocity.x > 0) golfBall->currentLocation.x = line.startPoint.x - golfBall->radius;
                            else golfBall->currentLocation.x = line.startPoint.x + golfBall->radius;
                            golfBall->velocity.x *= -1;
                        }
                        if (line.flipY)
                        { 
                            if (golfBall->velocity.y > 0) golfBall->currentLocation.y = line.startPoint.y - golfBall->radius;
                            else golfBall->currentLocation.y = line.startPoint.y + golfBall->radius;
                            golfBall->velocity.y *= -1;
                        }
                    }
                }

                golfBall->move();

                if (golfBall->isInHole(holeSetup.hole.location, holeSetup.hole.radius))
                {   
                    distance_file << "0 ";
                    stay_on_this_shot = false;
                    continue;
                }

                if (golfBall->velocity.x == 0 && golfBall->velocity.y == 0)
                {
                    distance_file << to_string(Utils::distanceBetweenVectors(golfBall->currentLocation, holeSetup.hole.location)) << " ";
                    stay_on_this_shot = false;
                    continue;
                }
            }
        }
        distance_file << "\n";
    }
    distance_file.close();
}

int main(int argc, char** argv) {
    if (argc < 2){
        cerr << "Missing hole name in commond line\n";
        exit(-1);
    }

    HoleSetup holeSetup = HoleSetup(string(argv[1]) + ".settings", string(argv[1]) + ".hole");

    int div_height = holeSetup.heightOfWindow / 8;
    int div_width = holeSetup.widthOfWindow / 8;

    vector<thread> threads;

    for (int i = 0; i < 8; ++i)
    {
        if (i < 7){
            thread t(simulate, std::ref(holeSetup), (holeSetup.heightOfWindow / 8) * i, (holeSetup.heightOfWindow / 8) * (i + 1), to_string(i));
            threads.push_back(move(t));
            //threads.push_back(t);
        }
        else {
            thread t(simulate, std::ref(holeSetup), (holeSetup.heightOfWindow / 8) * i, holeSetup.heightOfWindow, to_string(i));
            threads.push_back(move(t));
            //threads.push_back(t);
        }
    }

    for (int i = 0; i < 8; ++i){
        threads[i].join();
    }

    sf::RenderWindow window(sf::VideoMode(holeSetup.widthOfWindow, holeSetup.heightOfWindow), "Putt Visualizer");

    int row = 0;
    sf::RectangleShape pixel(sf::Vector2f(holeSetup.increment, holeSetup.increment));
    for (int i = 0; i < 8; ++i)
    {
        ifstream distance_file;
        distance_file.open(to_string(i));
        string line;
        while( getline(distance_file, line))
        {
            stringstream ss(line);
            string word;
            int column = 0;
            while (getline(ss, word, ' '))
            {
                float value = stof(word);
                pixel.setPosition(column, row);
                if (value == 0) pixel.setFillColor(sf::Color::White);
                else pixel.setFillColor(Utils::distanceToRGB(value, holeSetup.maxDistanceForColorSpectrum));
                window.draw(pixel);
                column += holeSetup.increment;
            }
            row += holeSetup.increment;
        }

        distance_file.close();
    }

    for (int i = 0; i < 8; ++i)
    {
        string filename = to_string(i);
        remove(filename.c_str());
    }

    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                sf::Texture texture;
                string screenshot_name = argv[1];
                screenshot_name = "screenshots/" + screenshot_name.substr(0, screenshot_name.size() - 9) + ".png";
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                if (texture.copyToImage().saveToFile(screenshot_name))
                {
                    std::cout << "screenshot saved to " << screenshot_name << std::endl;
                }
                window.close();
            }
        }
    }

    return 0;
}
