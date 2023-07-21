#pragma once

#include "Paddle.h"

class Ball : private GameObject{
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
        float m_angle;
    public:
        Ball();
        void setVelocity(float angle);
        void setBallPosition(float x, float y);
        void detectCollision(int paddle1Y, int paddle2Y, int* score1, int* score2);
        void move(float dt);
        sf::RectangleShape getSprite();
};