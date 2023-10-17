//
// Created by gabriele on 13/12/21.
//

#include "DistanceCalc.h"

const float vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    const sf::Vector2f dVec = vec2 - vec1;
    return sqrt(pow(dVec.x, 2) + pow(dVec.y, 2));
}