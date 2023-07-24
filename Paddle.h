#pragma once

#include "GameObject.h"

class Paddle : private GameObject{
    private:
        int m_index;
        int m_score;
        sf::Keyboard::Scancode m_move_up;
        sf::Keyboard::Scancode m_move_down;

    public:
        Paddle(float xPos, float yPos, sf::Keyboard::Scancode upKey, sf::Keyboard::Scancode downKey);
        void movePaddle(sf::Keyboard::Scancode key);
        void incrementScore();
        int getPosition();
        int* getScore();
        sf::RectangleShape getSprite();
};