#ifndef _GAME_H
#define _GAME_H

#include <string> // last action message
#include <sstream> // last action message
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Defines.h"
#include "Player.h"
#include "Renderer.h"
#include "Collision.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Animation.h"

using namespace Collision;

class Game
{
    public:
        Game(sf::RenderWindow* window, Player* player, Renderer* renderer);
        ~Game();

        void Init();
        void Update();
        void CollisionUpdate();
        void CollisionCheck();

        int GetAliveAsteroids();
        int GetAliveSpaceships();

        Player* GetPlayer()
        {
            return m_player;
        }

        sf::RenderWindow* GetWindow()
        {
            return m_window;
        }

        Renderer* GetRenderer()
        {
            return m_renderer;
        }

		void ClearEnemiesAndBullets();
		void WriteHighscore();
		int GetHighScore();

    private:
        Player* m_player;
        sf::RenderWindow* m_window;
        Renderer* m_renderer;
        std::vector<Treat*> m_treats;
        std::vector<Enemy*> m_enemies;

        sf::Time m_asteroidTime;
        sf::Clock m_asteroidClock;

		sf::Texture explTexture;
		Animation* expl;

		int m_playerLevel; // used for last action message
		int m_highscore;
};

#endif