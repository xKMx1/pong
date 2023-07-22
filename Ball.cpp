#include "Ball.h"

Ball::Ball() {
    m_speed = 300.0f;

    m_size.x = 20;
    m_size.y = 20;

    m_sprite.setOrigin(10.0f, 10.0f);

    m_position.x = 400.0f;
    m_position.y = 400.0f;

    m_velocity.x = 1.0f;
    m_velocity.y = 0.5f;

    m_velocity = normalise(m_velocity);

    m_sprite.setFillColor(sf::Color(180, 180, 180));
    m_sprite.setPosition(m_position);
    m_sprite.setSize(m_size);
}

sf::Vector3f Ball::getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal)
    {
        //the collision normal is stored in x and y, with the penetration in z
        sf::Vector3f manifold;

        if (overlap.width < overlap.height){
            manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
            manifold.z = overlap.width;
        }
        else{
            manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
            manifold.z = overlap.height;
        }
        
        return manifold;
    }

void Ball::resolve(const sf::Vector3f& manifold)
{
    //move the ball out of the solid object by the penetration amount
    sf::Vector2f normal(manifold.x, manifold.y);

    m_position += normal * manifold.z;
    m_sprite.setPosition(m_position);

    //reflect the current velocity to make the ball bounce
    m_velocity = reflect(m_velocity, normal);
}

void Ball::update(float dt, sf::FloatRect paddle1, sf::FloatRect paddle2, sf::FloatRect screenBound) {
    m_position += m_velocity * dt * m_speed;
    m_sprite.setPosition(m_position);

    sf::FloatRect overlap;

    if (paddle1.intersects(this->getSprite().getGlobalBounds(), overlap))
    {
        auto collisionNormal = paddle1.getPosition() - m_sprite.getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        resolve(manifold);
    }

    if (paddle2.intersects(this->getSprite().getGlobalBounds(), overlap))
    {
        auto collisionNormal = paddle2.getPosition() - m_sprite.getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        resolve(manifold);
    }

    if (!screenBound.intersects(this->getSprite().getGlobalBounds(), overlap))
    {
        auto collisionNormal = paddle2.getPosition() - m_sprite.getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        resolve(manifold);
    }
}

sf::RectangleShape Ball::getSprite() {
    return m_sprite;
}
