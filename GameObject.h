#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>

#define PI 3.1415

class GameObject{
    public:
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::RectangleShape m_sprite;
};