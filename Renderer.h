#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Treat.h"
#include "Enemy.h"

class Renderer
{
    public:
        Renderer(Player* player);
        ~Renderer();

        void Init(sf::RenderWindow* window);
        void AssignTreats(std::vector<Treat*> treats);
        void DrawKillCounter();
        void AssignBullets(std::vector<Bullet*> bullets);
        void AddEnemy(Enemy* enemy);
        void AddTreat(Treat* treat) { m_treats.push_back(treat); }
        void DeleteTreat(Treat* treat);
        void Update(std::vector<Enemy*> enemies, std::vector<Bullet*> bullets);

        // Drawing objects to screen
        // They get called every update
        void DrawPlayer();
        void DrawTreat(Treat* treat);
        void DrawMoneyCount();
        void DrawPlayerHealth();
		void DrawPlayerLevel();
		void DrawLastActionMessage();
		void DrawScore();
        void DrawPlaneHealth();
        void DrawSand();

		void SetLastActionMessage(std::string message)
		{
			m_message = message;
		}

    private:
        sf::RenderWindow* m_window;
        Player* m_player;
        std::vector<Treat*> m_treats;

		std::string m_message;

        // Background
        sf::Texture m_bgTexture;
        sf::Sprite m_bgSprite;

        sf::Sprite m_bgSprite2;
        int m_totalBgDiff; // Distance from origin to where the first background sprite is
        int m_scrollingSpeed; // Scrolling background

        // Sand
        sf::Texture m_sandTexture;
        sf::Sprite m_sandSprite;

        // Sounds
        sf::SoundBuffer buffer;
        sf::Sound sound;

		sf::Texture explTexture;
		Animation* expl;
};

#endif