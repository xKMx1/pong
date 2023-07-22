#include "VectorMath.h"

float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}

sf::Vector2f normalise(sf::Vector2f source)
{
    float length = std::sqrt(dot(source, source));
    if (length != 0) source /= length;
    return source;
}

sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal)
{
    return -2.f * dot(velocity, normal) * normal + velocity;
}
