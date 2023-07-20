#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject{
    public:
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::RectangleShape m_sprite;
};

class Paddle : private GameObject{
    private:
        int m_index;
        sf::Keyboard::Scancode m_move_up;
        sf::Keyboard::Scancode m_move_down;

    public:
        void initPaddle(float xPos, float yPos, sf::Keyboard::Scancode upKey, sf::Keyboard::Scancode downKey){
            m_size.x = 100.0f;
            m_size.y = 30.0f;

            m_move_up = upKey;
            m_move_down = downKey;

            m_position.x = xPos;
            m_position.y = yPos;

            m_sprite.setRotation(90.0f);

            m_sprite.setFillColor(sf::Color(180,180,180));
            m_sprite.setPosition(m_position);
            m_sprite.setSize(m_size);
        }

        void movePaddle(sf::Event evnt){
            if (evnt.key.scancode == m_move_up){
                m_position.y += 10;
            }
            if (evnt.key.scancode == m_move_down){
                m_position.y -= 10;     
            }
        }

        sf::RectangleShape getSprite(){
            return m_sprite;
        }
};

class Ball : private GameObject{
    public:
        void initBall(){
            m_size.x = 15;
            m_size.y = 15;

            m_position.x = 400;
            m_position.y = 400;

            m_sprite.setFillColor(sf::Color(180,180,180));
            m_sprite.setPosition(m_position);
            m_sprite.setSize(m_size);
        }
        void move(){

        }

        sf::RectangleShape getSprite(){
            return m_sprite;
        }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pong");
    sf::Texture texture;

    Paddle paddle1;
    Paddle paddle2;
    Ball ball;

    paddle1.initPaddle(100.0f, 350.0f, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);
    paddle1.initPaddle(80.0f, 350.0f, sf::Keyboard::Scancode::Up, sf::Keyboard::Scancode::Down);
    ball.initBall();

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
                    paddle1.movePaddle(event);
                    paddle2.movePaddle(event);
            }
        }

        window.draw(paddle1.getSprite());
        window.draw(paddle2.getSprite());
        window.draw(ball.getSprite());
        // window.clear(sf::Color(255,255,255));s
        window.display();
    }
    return 0;
}