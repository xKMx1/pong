#include "Ball.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pong");
    sf::FloatRect windowBounds(sf::Vector2f(20.0f, 20.0f), window.getDefaultView().getSize() - sf::Vector2f(40.0f, 40.0f));
    sf::Texture texture;
    sf::Clock frameClock;

    Paddle paddle1(80.0f, 325.0f, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);
    Paddle paddle2(740.0f, 325.0f, sf::Keyboard::Scancode::Up, sf::Keyboard::Scancode::Down);
    Ball ball;

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error while loading the font!" << std::endl;
    }

    std::string score1String = std::to_string(*paddle1.getScore());
    std::string score2String = std::to_string(*paddle2.getScore());
    score1String.append(score2String);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(score1String);
    scoreText.setCharacterSize(50);
    scoreText.setLetterSpacing(10);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
    scoreText.setPosition(400.0f, 100.0f);

    sf::Window dupaWindow;
    

    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;

        bool wKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool sKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if(wKey){
            paddle1.movePaddle(sf::Keyboard::Scancode::W);
        }
        if(sKey){
            paddle1.movePaddle(sf::Keyboard::Scancode::S);
        }
        if(upKey){
            paddle2.movePaddle(sf::Keyboard::Scancode::Up);
        }
        if(downKey){
            paddle2.movePaddle(sf::Keyboard::Scancode::Down);
        }

        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ball.update(frameClock.restart().asSeconds(), &paddle1, &paddle2, windowBounds);

        std::string score1String = std::to_string(*paddle1.getScore());
        std::string score2String = std::to_string(*paddle2.getScore());
        score1String.append(score2String);
        scoreText.setString(score1String);

        window.clear();
        window.draw(scoreText);
        window.draw(paddle1.getSprite());
        window.draw(paddle2.getSprite());
        window.draw(ball.getSprite());
        window.display();
    }
    return 0;
}