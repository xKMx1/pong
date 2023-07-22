#include "Ball.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pong");
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

        ball.update(frameClock.restart().asSeconds(), paddle1.getSprite().getGlobalBounds(), paddle2.getSprite().getGlobalBounds());
        ball.detectCollision(paddle1.getSprite().getGlobalBounds(), paddle2.getSprite().getGlobalBounds(), paddle1.getScore(), paddle2.getScore());

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