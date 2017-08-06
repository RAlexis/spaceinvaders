#include "Game.h"

// If I assign the pointers in the constructor body I will get a compilation error
Game::Game(sf::RenderWindow* window, Player* player, Renderer* renderer)
    : m_player(player), m_window(window), m_renderer(renderer)
{
	m_playerLevel = 1;
	m_highscore = GetHighScore();
    Init();

	explTexture.loadFromFile("images/explosions/type_B.png");
	expl = new Animation(explTexture, 0, 0, 192, 192, 64, 1);
}

Game::~Game()
{

}

void Game::CollisionCheck()
{
	//! Not implemented
	// (*treat)-> is needed because the vector contains pointers!
	/*std::vector<Treat*>::iterator treat = m_treats.begin();
	while (treat != m_treats.end())
	{
		if (PixelPerfectTest(m_player->GetSprite(), (*treat)->GetSprite()) && m_player->IsAlive())
		{
			m_player->ModMoney((*treat)->GetMoneyValue());
			m_renderer->DeleteTreat((*treat));
			// @todo find a way around this, as it causes a crash!
			//delete *treat;
			//treat = m_treats.erase(treat);
		}
		++treat;
	}*/

	/*std::vector<Enemy*>::iterator enemy = m_enemies.begin();
	while (enemy != m_enemies.end())
	{
		if (PixelPerfectTest(m_player->GetSprite(), (*enemy)->GetSprite()) && (*enemy)->IsAlive() && m_player->IsAlive())
		{
			if (m_player->IsFlying())
				m_player->GetVehicle()->Die();
			else
				m_player->Die();

			(*enemy)->SetState(ENEMY_STATE_DEAD);
			//(*enemy)->GetSprite().setPosition(-500, -500);

			//delete *enemy;
			//enemy = m_enemies.erase(enemy);
		}

		// @ this creates a loooot of lag
		for (auto bullet : GetPlayer()->GetBullets())
			if ((*enemy)->GetSprite().getGlobalBounds().intersects(bullet->GetShape().getGlobalBounds()) && (*enemy)->IsAlive() && bullet->IsAlive())
			{
				(*enemy)->SetState(ENEMY_STATE_DEAD);
				bullet->Die();
			}

		++enemy;
	}*/

	//!!! An enemy will only get deleted when we start shooting again
	// To-Do: find a fix for this!
	std::vector<Bullet*>::iterator start_bullets = GetPlayer()->GetBullets().begin();
	while (start_bullets != GetPlayer()->GetBullets().end())
	{
		(*start_bullets)->Update();
		if ((*start_bullets)->IsAlive())
		{
			std::vector<Enemy*>::iterator enemy = m_enemies.begin();
			// Change to iterator and erase dead enemies
			//for (auto enemy : m_enemies)
			while (enemy != m_enemies.end())
			{
				// (*enemy)->GetSprite().getGlobalBounds().intersects(bullet->GetShape().getGlobalBounds()) && (*enemy)->IsAlive() && bullet->IsAlive())
				if ((*enemy)->GetSprite().getGlobalBounds().intersects((*start_bullets)->GetShape().getGlobalBounds()) && (*enemy)->IsAlive())
				//if (PixelPerfectTest((*enemy)->GetSprite(), (*start_bullets)->GetAnimation()->sprite) && (*enemy)->IsAlive() && (*start_bullets)->IsAlive())
				{
					(*start_bullets)->Die();

					if ((*enemy)->GetType() == ENEMY_TYPE_ASTEROID)
					{
						(*enemy)->SetState(ENEMY_STATE_DEAD);
						GetPlayer()->AddXp(ENEMY_TYPE_ASTEROID);
						//sExplosion_ship.sprite.setPosition((*enemy)->GetSprite().getPosition());
						//sExplosion_ship.update();
						//GetWindow()->draw(sExplosion_ship.sprite);
					}
					else
					{
						(*enemy)->TakeDamage((*start_bullets)->GetDamage());
						if ((*enemy)->GetHealth() == 0)
						{
							(*enemy)->SetState(ENEMY_STATE_DEAD);
							GetPlayer()->AddKill();
							GetPlayer()->AddXp(ENEMY_TYPE_SPACESHIP);
						}
					}

					++enemy;
				}
				//else if (((*enemy)->GetState() == ENEMY_STATE_DEAD && (*enemy)->FinishedAnim()))// || (*enemy)->GetState() == ENEMY_STATE_DEAD_NO_EXPL)
					//enemy = m_enemies.erase(enemy);
				//else if ((*enemy)->GetExplosion()->isEnd() && (*enemy)->IsAlive() == false)
				else if ((*enemy)->GetState() == ENEMY_STATE_DEAD_NO_EXPL)
					printf("should");
					//enemy = m_enemies.erase(enemy);
				//{
					//printf("deleting");
					//delete (*enemy)->GetExplosion();
					//enemy = m_enemies.erase(enemy);
					//++enemy;
				//}
				else //if ((*enemy)->IsAlive())
					++enemy;
			}
			++start_bullets;
		}
		else
			start_bullets = GetPlayer()->GetBullets().erase(start_bullets);
	}

	std::vector<Enemy*>::iterator enemy = m_enemies.begin();
	while (enemy != m_enemies.end())
	{
		if (PixelPerfectTest((*enemy)->GetSprite(), GetPlayer()->GetSprite()) && (*enemy)->GetState() == ENEMY_STATE_ALIVE)
		{
			(*enemy)->SetState(ENEMY_STATE_DEAD);
			GetPlayer()->SetHealth(GetPlayer()->GetHealth() - ENEMY_DEFAULT_COLLISION_DAMAGE);

			// yay, more hacks
			if (GetPlayer()->GetHealth() <= 0)
			{
				std::ostringstream message;
				message << "You have died at level " << GetPlayer()->GetLevel() << ". Game is being reset.";
				GetRenderer()->SetLastActionMessage(message.str());

				// Reset the game basically
				// Doesn't really look that smooth in-game, but whatever
				ClearEnemiesAndBullets();

				if (GetPlayer()->GetScore() > m_highscore)
					WriteHighscore();

				GetPlayer()->Die();

				break;
			}
		}

		// Hackfix
		if ((*enemy)->GetSprite().getPosition().y >= WINDOW_HEIGHT)
			enemy = m_enemies.erase(enemy);

		//if ((*enemy)->GetState() == ENEMY_STATE_DEAD_NO_EXPL)
			//printf("should\n");
			//enemy = m_enemies.erase(enemy);
			//(*enemy)->GetExplosion()->finished = true;
		else if ((*enemy)->GetExplosion()->isEnd() && (*enemy)->GetState() != ENEMY_STATE_ALIVE)
			enemy = m_enemies.erase(enemy);
		else if ((*enemy)->GetExplosion()->isEnd() && (*enemy)->IsAlive())
		{
			(*enemy)->GetExplosion()->finished = false;
			(*enemy)->GetExplosion()->Frame = 0;
		}

		++enemy;
	}

	// Last action message for player level up
	if (GetPlayer()->GetLevel() != m_playerLevel)
	{
		std::ostringstream message;
		message << "You have reached level " << GetPlayer()->GetLevel() << '.';
		GetRenderer()->SetLastActionMessage(message.str());
		++m_playerLevel;
	}
}

void Game::ClearEnemiesAndBullets()
{
	m_enemies.clear();
	GetPlayer()->GetBullets().clear();
}

// writing high score to file
void Game::WriteHighscore()
{
	printf("writing highscore %d\n", GetPlayer()->GetScore());
	std::ofstream file("highscore.txt");
	file << GetPlayer()->GetScore();
}

int Game::GetHighScore()
{
	std::ifstream file("highscore.txt");
	int highscore;
	file >> highscore;

	printf("GOT HS %d\n", highscore);

	return highscore;
}

int Game::GetAliveAsteroids()
{
    int cnt = 0;
    for (auto enemy : m_enemies)
        if (enemy->IsAlive() && enemy->GetType() == ENEMY_TYPE_ASTEROID)
            ++cnt;

    return cnt;
}

int Game::GetAliveSpaceships()
{
    int cnt = 0;
    for (auto enemy : m_enemies)
        if (enemy->IsAlive() && enemy->GetType() == ENEMY_TYPE_SPACESHIP)
            ++cnt;

    return cnt;
}

// Main updating fuction
void Game::Update()
{
    // @todo move this to class Game so we don't store shit twice
    m_renderer->Update(m_enemies, m_player->GetBullets()); // Draws objects on screen
    m_player->Update();

    m_asteroidTime = m_asteroidClock.getElapsedTime();
    if (m_asteroidTime.asSeconds() >= 2)
    {
        sf::Vector2f asteroidPos;
        asteroidPos.x = rand() % (WINDOW_WIDTH - 200) + 100;
        asteroidPos.y = 0;
        Enemy* asteroid1 = new Enemy(ENEMY_TYPE_ASTEROID, asteroidPos, GetPlayer()->GetLevel(), expl);
        m_enemies.push_back(asteroid1);
        m_renderer->AddEnemy(asteroid1);
        m_asteroidClock.restart();
    }

    if (GetAliveSpaceships() <= 5)
    {
		//printf("spawning\n");
        sf::Vector2f enemyPos;
        enemyPos.x = rand() % (WINDOW_WIDTH - 200) + 100;
        enemyPos.y = 0;
        Enemy* enemy = new Enemy(ENEMY_TYPE_SPACESHIP, enemyPos, GetPlayer()->GetLevel(), expl);
        m_enemies.push_back(enemy);
        m_renderer->AddEnemy(enemy);
    }

    // We have to update the enemies in one loop
    // And delete them in the other loop
    // Otherwise weird stuff happen
	for (auto enemy : m_enemies)
        if (enemy->IsAlive())
            enemy->Update();

    // Collision between player and objects/entities
    CollisionCheck();
}

void Game::Init()
{
    // Random number generator seed
    srand(time(0));

    // Misc settings
    m_window->setFramerateLimit(FRAMES_PER_SECOND_CAP);
    m_window->setKeyRepeatEnabled(true); // If this is set to false, you have to press up all the time to move
    m_window->setVerticalSyncEnabled(true);

    // Renderer initialization (this draws what you see on the screen)
    m_renderer->Init(m_window);

    // Treat
    //Treat* treat = new Treat(sf::Vector2f(100, WINDOW_HEIGHT - GROUND_HEIGHT - 16));
    //m_treats.push_back(treat);
    //treat = new Treat(sf::Vector2f(50, WINDOW_HEIGHT - GROUND_HEIGHT - 16));
    //m_treats.push_back(treat);

    //m_treats.push_back(new Treat(sf::Vector2f(100, 100)));
    //m_treats.push_back(new Treat(sf::Vector2f(116, 116)));

    //m_renderer->AssignTreats(m_treats); // For drawing
}