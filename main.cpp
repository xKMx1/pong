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

class Paddle : private GameObject{
    private:
        int m_index;
        int m_score;
        sf::Keyboard::Scancode m_move_up;
        sf::Keyboard::Scancode m_move_down;

    public:
        Paddle(float xPos, float yPos, sf::Keyboard::Scancode upKey, sf::Keyboard::Scancode downKey){
            m_size.x = 150.0f;
            m_size.y = 30.0f;

            m_score = 0;

            m_move_up = upKey;
            m_move_down = downKey;

            m_position.x = xPos;
            m_position.y = yPos;

            m_sprite.setRotation(90.0f);

            m_sprite.setFillColor(sf::Color(180,180,180));
            m_sprite.setPosition(m_position);
            m_sprite.setSize(m_size);
        }

        void movePaddle(sf::Keyboard::Scancode key){
            if (key == m_move_up && m_position.y >= 0){
                m_position.y -= 15;
                m_sprite.setPosition(m_position);
            }
            if (key == m_move_down && m_position.y <= 650){
                m_position.y += 15;  
                m_sprite.setPosition(m_position);   
            }
        }

        int getPosition(){
            return m_position.y;
        }

        int* getScore(){
            return &m_score;
        }

        sf::RectangleShape getSprite(){
            return m_sprite;
        }
};

class Ball : private GameObject{
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
        float m_angle;
    public:
        Ball(){
            m_size.x = 20;
            m_size.y = 20;

            m_position.x = 400.0f;
            m_position.y = 400.0f;

            m_angle = PI/3;

            m_velocity.x = 0;
            m_velocity.y = 0;

            setVelocity(m_angle);

            m_sprite.setFillColor(sf::Color(180,180,180));
            m_sprite.setPosition(m_position);
            m_sprite.setSize(m_size);
        }

        void setVelocity(float angle){
            m_angle = angle;
            m_velocity.x = cosf(m_angle);
            m_velocity.y = sinf(m_angle);
        }

        void setBallPosition(float x, float y){
            m_position.x = x;
            m_position.y = y;
        }

        void detectCollision(int paddle1Y, int paddle2Y, int* score1, int* score2){
            if(m_position.y >= paddle1Y && m_position.y <= paddle1Y + 150 && m_position.x < 80){            // if checking for collision with the first paddle
                setVelocity(m_angle + PI/2);
            }

            if(m_position.y >= paddle2Y && m_position.y <= paddle2Y + 150 && m_position.x > 695){            // if checking for collision with the second paddle
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
        
        void move(float dt){
                                                            //TODO random angle generator
            setVelocity(m_angle);                           //colision detection and angle cant be m_angle
            m_position += m_velocity * dt;
            m_sprite.setPosition(m_position);
        }


        sf::RectangleShape getSprite(){
            return m_sprite;
        }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pong");
    sf::Texture texture;

    Paddle paddle1(80.0f, 325.0f, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);
    Paddle paddle2(740.0f, 325.0f, sf::Keyboard::Scancode::Up, sf::Keyboard::Scancode::Down);
    Ball ball;

    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    paddle1.movePaddle(event.key.scancode);
                    paddle2.movePaddle(event.key.scancode);
            }
        }

        float dt = 3;
        ball.detectCollision(paddle1.getSprite().getPosition().y, paddle2.getSprite().getPosition().y, paddle1.getScore(), paddle2.getScore());
        ball.move(dt);
        std::cout << *paddle1.getScore() << " | " << *paddle2.getScore() << std::endl;

        window.clear();
        window.draw(paddle1.getSprite());
        window.draw(paddle2.getSprite());
        window.draw(ball.getSprite());
        window.display();
    }
    return 0;
}