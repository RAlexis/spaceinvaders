#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Defines.h"
#include "Vehicle.h"
#include "Bullet.h"
#include "Animation.h"

// When we have files including each other (e.g. Player.h and Vehicle.h, we have to also declare the class names)
class Vehicle;

#define DEFAULT_PLAYER_HP 100
#define PLAYER_MOVE_VALUE 12.5f

enum PlayerState
{
    PLAYER_STATE_ALIVE = 0,
    PLAYER_STATE_DEAD  = 1
};

class Player
{
	float m_xpMultiplier;

    public:
        Player();
        ~Player();

        void Update();
        void Die();

		void SetScore(int score)
		{
			m_score = score;
		}

		int GetScore()
		{
			return m_score;
		}

        void CollisionCheck(sf::Vector2f &currentPos);
        void HandleGroundMovement();
        void HandleAirMovement();

        void LoadAndInitPlayerSprite();
        void UpdateSpriteDirection();
        void UpdateSpaceshipSpriteDirection();
        void LoadAndInitPlaneSprite();
        void LoadAndInitHelicopterSprite();
        void ResetFlyingSettings();

        void SetPosition(sf::Vector2f position)
        {
            m_position = position;
        }

        sf::Vector2f GetPosition()
        {
            //return m_position;
            return m_sprite.getPosition();
        }

        sf::Sprite GetSprite()
        {
            return m_sprite;
        }

        void ModMoney(int value)
        {
            m_money += value;
        }

        int GetMoney()
        {
            return m_money;
        }

        void SetHealth(int value)
        {
            m_health = value;

			// if we have this here
			// we won't be able to print the last action message...
			//if (m_health <= 0)
			//	Die();
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

        void SetFlying(bool value)
        {
            m_flying = value;
        }

        bool IsFlying()
        {
            return m_flying;
        }

        Vehicle* GetVehicle()
        {
            return m_vehicle;
        }

		void SetLevel(int level)
		{
			m_level = level;
		}

		int GetLevel()
		{
			return m_level;
		}

        void SetState(int value)
        {
            m_state = value;
        }

        int GetState()
        {
            return m_state;
        }

        bool IsAlive()
        {
            return m_state == PLAYER_STATE_ALIVE;
        }

        // If we don't use & we get a crash
        std::vector<Bullet*>& GetBullets()
        {
            return m_bullets;
        }

        bool IsShooting()
        {
            return m_isShooting;
        }

        void SetShooting(bool shooting)
        {
            m_isShooting = shooting;
        }

        void AddKill()
        {
            ++m_kills;
        }

        int GetKills()
        {
            return m_kills;
        }

        void SetMoving(bool moving)
        {
            m_moving = moving;
        }

        bool IsMoving()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    return true;

            return false;
        }

        bool IsMovingLeftAndUp()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return true;

            return false;
        }

        bool IsMovingRightAndUp()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return true;

            return false;
        }

        bool IsMovingLeft()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                return true;

            return false;
        }

        bool IsMovingRight()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                return true;

            return false;
        }

        bool IsMovingLeftAndDown()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return true;

            return false;
        }

        bool IsMovingRightAndDown()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return true;

            return false;
        }

		// Also handles leveling up
		void AddXp(int enemyType);

		int GetXp()
		{
			return m_xp;
		}
        
    private:
        sf::Time m_time;
        sf::Clock m_clock;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2i m_source; // @todo rename this to m_facing
        bool m_moving;

        sf::Vector2f m_position;

		int m_level;
        int m_money;
        int m_health;
        int m_maxHealth;
		int m_score; // this is the current score

        bool m_isShooting;
        int m_kills; // Kill counter
		// This basically prevents us from getting infinite levels when we stay at the number of kills we need in order to level up
		int m_KillCounterWhenLastLeveledUp;
		int m_xp;

        // Plane sprite and movement is handled in Player, the stats and the rest of it in Plane
        Vehicle* m_vehicle;
        bool m_flying;

        int m_state; // Dead/alive

        std::vector<Bullet*> m_bullets;

        // Bullet sounds
        sf::SoundBuffer bulletBuffer;
        sf::Sound bulletSound;

        // Spaceship movement sound
        sf::SoundBuffer spaceshipBuffer;
        sf::Sound spaceshipSound;

		sf::Texture bulletTexture;
		Animation* bulletAnimation;
};

#endif