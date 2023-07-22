#pragma once

#include "Paddle.h"
#include "VectorMath.h"

class Ball : private GameObject{
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
        float m_angle;
        float m_speed;
    public:
        Ball();
        sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal);
        void setVelocity(float angle);
        void resolve(const sf::Vector3f& manifold);
        void setBallPosition(float x, float y);
        void detectCollision(sf::FloatRect paddle1, sf::FloatRect paddle2, int* score1, int* score2);
        void update(float dt, sf::FloatRect paddle1, sf::FloatRect paddle2);
        sf::RectangleShape getSprite();
};