#include "game.h"
#include <SFML/Graphics.hpp>

bool checkCollision(const RecObject &obj1, const RecObject &obj2)
{
    sf::RectangleShape rect1(sf::Vector2f(obj1.width, obj1.height));
    sf::RectangleShape rect2(sf::Vector2f(obj2.width, obj2.height));
    return rect1.getGlobalBounds().intersects(rect2.getGlobalBounds());
}

void RecObject::render(sf::RenderWindow &window)
{
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(color);
    window.draw(rect);
}

void Character::render(sf::RenderWindow &window)
{
    RecObject::render(window);
}

void MovingObject::update(const Timeline &tl)
{
    float dt = tl.getLastDeltaTime();
    x += velocity.x * dt;
    y += velocity.y * dt;
}

void Character::update(const Timeline &tl)
{
    

    MovingObject::update(tl);
}
