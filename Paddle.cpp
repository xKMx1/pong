#include "Paddle.h"

Paddle::Paddle(float xPos, float yPos, sf::Keyboard::Scancode upKey, sf::Keyboard::Scancode downKey){
    m_size.x = 30.0f;
    m_size.y = 150.0f;

    m_score = 0;

    m_move_up = upKey;
    m_move_down = downKey;

    m_sprite.setOrigin(m_size.x/2, m_size.y/2);

    m_position.x = xPos;
    m_position.y = yPos;

    m_sprite.setFillColor(sf::Color(180,180,180));
    m_sprite.setPosition(m_position);
    m_sprite.setSize(m_size);
}

void Paddle::movePaddle(sf::Keyboard::Scancode key){
    if (key == m_move_up && m_position.y >= m_size.y/2){
        m_position.y -= 15;
        m_sprite.setPosition(m_position);
    }
    if (key == m_move_down && m_position.y <= 650 + m_size.y/2){
        m_position.y += 15;  
        m_sprite.setPosition(m_position);   
    }
}

void Paddle::resetScore(){
    m_score = 0;
}

void Paddle::setPosition(float y){
    m_position.y = y;
    m_sprite.setPosition(m_position);
}

int Paddle::checkForWin(){
    if(m_score == 10){
        return 1;
    }
    else return 0;
}

void Paddle::incrementScore(){
    m_score++;
}

int Paddle::getPosition(){
    return m_position.y;
}

int* Paddle::getScore(){
    return &m_score;
}

sf::RectangleShape Paddle::getSprite(){
    return m_sprite;
}