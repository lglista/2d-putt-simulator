#include <fstream>
#include <sstream>
#include <sstream>
#include <vector>
#include "HoleSetup.hpp"

HoleSetup::HoleSetup()
{
    hole = Hole();
    golfBall = GolfBall();
    walls = std::vector<Line>();
    widthOfWindow = 1000;
    heightOfWindow = 1000;
    increment = 20;
    velocityDivisor = 150;
}

HoleSetup::HoleSetup(std::string settingsFilePath, std::string holeFilePath)
{
    HoleSetup();
    readSettingsFile("config/" + settingsFilePath);
    readHoleFile("config/" + holeFilePath);
}

void HoleSetup::readSettingsFile(std::string settingsFilePath)
{
    using namespace std;
    string line;
    ifstream settings_file(settingsFilePath);

    while (getline(settings_file, line))
    {
        stringstream ss(line);
        string word;

        getline(ss, word, ' ');
        if (word == "WindowWidth"){
            getline(ss, word, ' ');
            widthOfWindow = stoi(word);
            if (widthOfWindow < 1) widthOfWindow = 1;
        }
        else if (word == "WindowHeight"){
            getline(ss, word, ' ');
            heightOfWindow = stoi(word);
            if (heightOfWindow < 1) heightOfWindow = 1;
        }
        else if (word == "Increment"){
            getline(ss, word, ' ');
            increment = stoi(word);
            if (increment < 1) increment = 1;
        }
        else if (word == "VelocityDivisor"){
            getline(ss, word, ' ');
            velocityDivisor = stoi(word);
            if (velocityDivisor < 1) velocityDivisor = 1;
        }
        else if (word == "MaxDistanceForColorSpectrum"){
            getline(ss, word, ' ');
            maxDistanceForColorSpectrum = stof(word);
            if (maxDistanceForColorSpectrum < 0) maxDistanceForColorSpectrum = 1;
        }
    }

    settings_file.close();
}

void HoleSetup::readHoleFile(std::string holeFilePath)
{
    using namespace std;
    string line;
    ifstream hole_file(holeFilePath);

    while (getline(hole_file, line))
    {
        stringstream ss(line);
        string word;

        getline(ss, word, ' ');
        if (word == "Ball"){
            getline(ss, word, ' ');
            int x = stof(word);

            getline(ss, word, ' ');
            int y = stof(word);

            getline(ss, word, ' ');
            int radius = stof(word);

            golfBall = GolfBall(x, y, radius);
        }
        else if (word == "Hole"){
            getline(ss, word, ' ');
            int x = stof(word);

            getline(ss, word, ' ');
            int y = stof(word);

            getline(ss, word, ' ');
            float radius = stof(word);

            if (radius < 0) radius = 1;
            hole = Hole(radius, sf::Vector2f(x, y));
        }
        else if (word == "VerticalWall"){
            getline(ss, word, ' ');
            int x = stof(word);

            getline(ss, word, ' ');
            int y = stof(word);

            getline(ss, word, ' ');
            int length = stof(word);

            VerticalLine vLine = VerticalLine(x, y, length);
            walls.push_back(vLine);
        }
        else if (word == "HorizontalWall"){
            getline(ss, word, ' ');
            int x = stof(word);

            getline(ss, word, ' ');
            int y = stof(word);

            getline(ss, word, ' ');
            int length = stof(word);

            HorizontalLine hLine = HorizontalLine(x, y, length);
            walls.push_back(hLine);
        }
    }

    hole_file.close();
}
