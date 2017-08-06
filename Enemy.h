#ifndef _ENEMY_H
#define _ENEMY_H

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Animation.h"

//#define DEFAULT_ENEMY_HEALTH 95

#define SPACESHIP_SPEED 7.5f
#define ASTEROID_SPEED 10.0f

enum EnemyState
{
    ENEMY_STATE_DEAD  = 0,
    ENEMY_STATE_ALIVE = 1,
	ENEMY_STATE_DEAD_NO_EXPL = 2 // No explosion
};

enum EnemyDamage
{
	ENEMY_DEFAULT_COLLISION_DAMAGE = 50
};

class Enemy
{
	const float m_enemyHealth = 95.0f;
    public:
        Enemy(int type, sf::Vector2f position, int playerLevel, Animation* anim);
        ~Enemy();

        void InitAsteroidSprite();
        void InitSpaceshipSprite();
        void InitCreatureSprite(); // @todo

        void UpdateSpaceship();
        void HandleAsteroidMovement();

        void Update();

        void TakeDamage(int damage);

        void SetHealth(int value)
        {
            m_health = value;
        }

        int GetHealth()
        {
            return m_health;
        }

        void SetMaxHealth(int value)
        {
            m_maxHealth = value;
        }

        int GetMaxHealth()
        {
            return m_maxHealth;
        }

        sf::Sprite GetSprite()
        {
            return m_sprite;
        }

        void SetState(bool state)
        {
            m_state = state;
        }

        bool GetState()
        {
            return m_state;
        }

        bool IsAlive()
        {
            return m_state == ENEMY_STATE_ALIVE;
        }

        void SetType(int type)
        {
            m_type = type;
        }

        int GetType()
        {
            return m_type;
        }

        Animation* GetExplosion()
        {
			return expl;
        }

		void updateAnimPos()
		{
			expl->sprite.setPosition(m_sprite.getPosition());
		}

		bool FinishedAnim()
		{
			return expl->finished;
		}

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        int m_health;
        int m_maxHealth;

        bool m_state;
        int m_type; // Enemy type

        sf::Vector2f m_position;
		
		//sf::Texture explTexture;
        Animation* expl;
};

#endif