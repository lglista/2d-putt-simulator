#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Hole.hpp"
#include "GolfBall.hpp"
#include "Line.hpp"

class HoleSetup {
public:
    HoleSetup();
    HoleSetup(std::string settingsFilePath, std::string holeFilePath);
    HoleSetup(HoleSetup &&) = default;

    Hole hole;
    GolfBall golfBall;
    std::vector<Line> walls;
    
    int widthOfWindow;
    int heightOfWindow;
    int increment;
    int velocityDivisor;
    float maxDistanceForColorSpectrum;

private:
    void readSettingsFile(std::string settingsFilePath);
    void readHoleFile(std::string holeFilePath);
};