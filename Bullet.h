#ifndef _BULLET_H
#define _BULLET_H

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Animation.h"

#define BULLET_SPEED 5.0f

class Bullet
{
    public:
        Bullet(sf::Vector2f position, int playerLevel, Animation* anim);
        ~Bullet();

        void Update();

        sf::Sprite GetSprite()
        {
            return m_sprite;
        }

        sf::RectangleShape GetShape()
        {
            return m_shape;
        }

        sf::Vector2f GetPosition()
        {
            return m_shape.getPosition();
        }

        void SetPosition(sf::Vector2f position)
        {
            m_shape.setPosition(position);
        }

        bool IsAlive()
        {
            return m_alive;
        }

        void Die()
        {
            m_alive = false;
        }

		void SetDamage(int damage)
		{
			m_damage = damage;
		}

		int GetDamage()
		{
			return m_damage;
		}

		Animation* GetAnimation()
		{
			return m_anim;
		}

    private:
        sf::Sprite m_sprite;
        sf::RectangleShape m_shape;

        float m_distanceTraveled;
		float m_range; // How far the bullet will go
		int m_damage;
        
        bool m_alive;

		Animation* m_anim;
};

#endif