#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f position, int playerLevel, Animation* anim) :
	m_anim(anim)
{
    m_shape = sf::RectangleShape(sf::Vector2f(5, 15));
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Cyan);

	//anim->sprite.setPosition(position);
    m_alive = true;
    m_distanceTraveled = 0.0f;
	SetDamage(45.0f + playerLevel * 1.25f);
	m_range = 245.0f + playerLevel * 3.0f;
	//std::cout << "range is " << m_range << std::endl;
	//std::cout << "Damage: " << GetDamage() << std::endl;
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	if (!IsAlive())
		return;

    // Doesn't lag as much
    if (GetPosition().x <= 0 || GetPosition().y <= 0 || GetPosition().x >= WINDOW_WIDTH || GetPosition().y >= WINDOW_HEIGHT)
    {
        Die();
        return;
    }

    if (m_distanceTraveled > m_range)
    {
        Die();
        return;
    }

	//m_anim->sprite.setPosition(m_anim->sprite.getPosition().x, m_anim->sprite.getPosition().y - BULLET_SPEED);
	//m_anim->sprite.setPosition(m_shape.getPosition().x, m_shape.getPosition().y - BULLET_SPEED);
    m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y - BULLET_SPEED);
    m_distanceTraveled += BULLET_SPEED;
}