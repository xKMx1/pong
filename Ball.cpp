#include "Ball.h"

Ball::Ball() {
    m_size.x = 20;
    m_size.y = 20;

    m_position.x = 400.0f;
    m_position.y = 400.0f;

    m_angle = PI / 3;

    m_velocity.x = 0;
    m_velocity.y = 0;

    setVelocity(m_angle);

    m_sprite.setFillColor(sf::Color(180, 180, 180));
    m_sprite.setPosition(m_position);
    m_sprite.setSize(m_size);
}

void Ball::setVelocity(float angle) {
    m_angle = angle;
    m_velocity.x = cosf(m_angle);
    m_velocity.y = sinf(m_angle);
}

void Ball::setBallPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
}

void Ball::detectCollision(int paddle1Y, int paddle2Y, int* score1, int* score2){
    if(m_position.y >= paddle1Y && m_position.y <= paddle1Y + 75 && m_position.x < 78){            // if checking for collision with the first paddle
        setVelocity(m_angle + PI/2);
    }

    if(m_position.y >= paddle1Y + 76 && m_position.y <= paddle1Y + 150 && m_position.x < 78){            // if checking for collision with the first paddle
        setVelocity(m_angle - PI/2);
    }

    if(m_position.y >= paddle2Y && m_position.y <= paddle2Y + 75 && m_position.x > 693){            // if checking for collision with the second paddle
        setVelocity(m_angle - PI/2);
    }

    if(m_position.y >= paddle2Y +76 && m_position.y <= paddle2Y + 150 && m_position.x > 693){            // if checking for collision with the second paddle
        setVelocity(m_angle + PI/2);
    }

    if(m_position.y < 0){                   // if checking for top bound
        setVelocity(m_angle - PI/2);
    }

    if(m_position.y > 780){                 // if checking for bottom bound
        setVelocity(m_angle + PI/2);
    }

    if(m_position.x < 0){
        *score2 += 1;
        setBallPosition(400.0f, 400.0f);
        m_sprite.setPosition(m_position);
    }

    if(m_position.x > 780){
        *score1 += 1;
        setBallPosition(400.0f, 400.0f);
        m_sprite.setPosition(m_position);
    }
}

void Ball::move(float dt) {
    setVelocity(m_angle); // colision detection and angle can't be m_angle
    m_position += m_velocity * dt;
    m_sprite.setPosition(m_position);
}

sf::RectangleShape Ball::getSprite() {
    return m_sprite;
}
