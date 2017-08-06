#include "Renderer.h"

Renderer::Renderer(Player* player)
    : m_player(player)
{
	m_message = "";

    m_bgTexture.loadFromFile("img/space_bg.png");
    m_bgTexture.setRepeated(true);
    m_bgSprite.setTexture(m_bgTexture);
    m_bgSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    m_bgSprite2.setTexture(m_bgTexture);
    m_bgSprite2.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    m_totalBgDiff = 0;
    m_scrollingSpeed = 5;
   
	explTexture.loadFromFile("images/explosions/type_B.png");
	expl = new Animation(explTexture, 0, 0, 192, 192, 64, 1);
}

Renderer::~Renderer()
{

}

// Safe to remove
void Renderer::AddEnemy(Enemy* enemy)
{
    //m_enemies.push_back(enemy);
}

void Renderer::DeleteTreat(Treat* treat)
{
    std::vector<Treat*>::iterator it = m_treats.begin();
    while (it != m_treats.end())
    {
        if ((*it) == treat)
        {
            delete *it;
            it = m_treats.erase(it);
            return;
        }
        else
            ++it;
    }
}

void Renderer::DrawMoneyCount()
{
    // This is just for UI
    sf::Texture treatTexture;
    sf::Sprite treatSprite;
    if (!treatTexture.loadFromFile("img/coin.png"))
        printf("[ERROR] Could not load img/coin.png!");

    treatSprite.setTexture(treatTexture);
    treatSprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
    treatSprite.setScale(0.2f, 0.2f);
    treatSprite.setPosition(sf::Vector2f(0, 0));

    m_window->draw(treatSprite);

    sf::Font font;
    font.loadFromFile("utils/arial.ttf");
    
    std::ostringstream tmp;
    tmp << "x" << m_player->GetMoney();

    sf::Text text(tmp.str(), font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20, 0);

    m_window->draw(text);
}

void Renderer::DrawPlaneHealth()
{
    sf::RectangleShape healthBarOutline(sf::Vector2f(30, 5));
    healthBarOutline.setScale(static_cast<float>(m_player->GetVehicle()->GetMaxHealth()) / (m_player->GetVehicle()->GetMaxHealth() / 2), 2.5f);
    healthBarOutline.setFillColor(sf::Color(255, 255, 128, 128)); // Black, half transparent
    healthBarOutline.setOutlineThickness(0.5); // Outline border thickness
    healthBarOutline.setOutlineColor(sf::Color::Black); // Outline border color
    healthBarOutline.setPosition(5, 60);
    m_window->draw(healthBarOutline);

    sf::RectangleShape healthBar(sf::Vector2f(30, 5));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setScale(static_cast<float>((m_player->GetVehicle()->GetHealth())) / (m_player->GetVehicle()->GetMaxHealth() / 2), 2.5f);
    healthBar.setPosition(5, 60);
    m_window->draw(healthBar);

    sf::Font font;
    font.loadFromFile("utils/arial.ttf");

    std::ostringstream tmp;
    tmp << m_player->GetVehicle()->GetHealth();

    sf::Text text(tmp.str(), font);
    text.setCharacterSize(11);
    text.setFillColor(sf::Color::Black);
    text.setPosition(23, 60);

    if (m_player->GetVehicle()->GetHealth() > 0)
        m_window->draw(text);
}

void Renderer::DrawPlayerHealth()
{
    // This is just for UI
    /*
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    if (!heartTexture.loadFromFile("img/heart.png"))
        printf("[ERROR] Could not load img/heart.png!");

    heartSprite.setTexture(heartTexture);
    heartSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    heartSprite.setScale(0.6f, 0.6f);
    heartSprite.setPosition(sf::Vector2f(0, 20));

    m_window->draw(heartSprite);
    */
    /*
    sf::Font font;
    font.loadFromFile("utils/arial.ttf");

    std::ostringstream tmp;
    tmp << "x" << m_player->GetHealth();

    sf::Text text(tmp.str(), font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20, 20);

    m_window->draw(text);
    */

    sf::Font font;
    font.loadFromFile("utils/arial.ttf");

    std::ostringstream tmp;
    tmp << m_player->GetHealth();

    sf::Text text(tmp.str(), font);
    text.setCharacterSize(11);
    text.setFillColor(sf::Color::Black);
    text.setPosition(23, 25);
    //m_window->draw(text);

    sf::RectangleShape healthBarOutline(sf::Vector2f(30, 5));
    healthBarOutline.setScale(static_cast<float>(m_player->GetMaxHealth()) / (m_player->GetMaxHealth() / 2), 2.5f);
    healthBarOutline.setFillColor(sf::Color(255, 0, 0, 128)); // Black, half transparent
    healthBarOutline.setOutlineThickness(0.5); // Outline border thickness
    healthBarOutline.setOutlineColor(sf::Color::Black); // Outline border color
    healthBarOutline.setPosition(5, 25);
    m_window->draw(healthBarOutline);

    sf::RectangleShape healthBar(sf::Vector2f(30, 5));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setScale(static_cast<float>((m_player->GetHealth())) / (m_player->GetMaxHealth() / 2), 2.5f);
    healthBar.setPosition(5, 25);
    m_window->draw(healthBar);

    // This needs to be drawn after the health bar, otherwise you won't see it
    if (m_player->GetHealth() > 0)
        m_window->draw(text);
}

void Renderer::DrawPlayer()
{
    m_window->draw(m_player->GetSprite());
}

// This is baaaad
void Renderer::AssignTreats(std::vector<Treat*> treats)
{
    m_treats = treats;
}

// Unused
void Renderer::DrawSand()
{
	/*
    m_sandTexture.loadFromFile("img/sand.png");
    m_sandTexture.setRepeated(true); // It doesn't look smooth if this is not here
    m_sandSprite.setTexture(m_sandTexture);
    m_sandSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, GROUND_HEIGHT));
    m_sandSprite.setPosition(0, WINDOW_HEIGHT - GROUND_HEIGHT);

    m_window->draw(m_sandSprite);
	*/
}

void Renderer::DrawPlayerLevel()
{
	sf::Font font;
	font.loadFromFile("utils/arial.ttf");

	std::ostringstream tmp;
	tmp << "Level: " << m_player->GetLevel();

	sf::Text text(tmp.str(), font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 100);
	m_window->draw(text);
}

void Renderer::DrawLastActionMessage()
{
	sf::Font font;
	font.loadFromFile("utils/arial.ttf");

	sf::Text text(m_message, font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	// pulled this * 7.2 outta nowhere lol
	text.setPosition(WINDOW_WIDTH - m_message.length() * 7.2, WINDOW_HEIGHT - 30);
	m_window->draw(text);
}

void Renderer::DrawScore()
{
	sf::Font font;
	font.loadFromFile("utils/Mathlete-Bulky.otf");

	std::ostringstream score;
	score << m_player->GetScore();

	sf::Text text(score.str(), font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(WINDOW_WIDTH - 150, 5);
	m_window->draw(text);
}


void Renderer::Update(std::vector<Enemy*> enemies, std::vector<Bullet*> bullets)
{
    //m_window->clear(sf::Color(135, 206, 235)); // Sky blue
    m_window->clear();

	// Reload bg size if we changed resolution
	if (m_bgSprite.getTextureRect().width != WINDOW_WIDTH || m_bgSprite.getTextureRect().height != WINDOW_HEIGHT)
	{
		m_bgSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		m_bgSprite2.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	}

    // Poor implementation of a scrolling background
	// But hey, it works
    if (m_bgSprite.getPosition().y > WINDOW_HEIGHT - m_scrollingSpeed * 2)
    {
        m_bgSprite.setPosition(0, 0);
        m_totalBgDiff = 0;
    }
    else
    {
        m_bgSprite2.setPosition(0, -WINDOW_HEIGHT + m_totalBgDiff);
        m_window->draw(m_bgSprite2);
        m_bgSprite.setPosition(m_bgSprite.getPosition().x, m_bgSprite.getPosition().y + m_scrollingSpeed);
        m_totalBgDiff += m_scrollingSpeed;
    }

    m_window->draw(m_bgSprite);

    //DrawSand();
    DrawPlayer();
	// Not implemented
    //for (auto treat : m_treats)
    //    m_window->draw(treat->GetSprite());
    DrawMoneyCount();
    DrawPlayerHealth();
	DrawPlayerLevel();
	DrawLastActionMessage();
	DrawScore();

    // We have to update the enemies in one loop
    // And delete them in another loop
    // Otherwise the sprites flicker on the screen and it's just buggy
	for (auto enemy : enemies)
		if (enemy->IsAlive())
		{
			if (enemy->GetType() != ENEMY_TYPE_ASTEROID)
			{
				sf::RectangleShape healthBarOutline(sf::Vector2f(15, 5));
				healthBarOutline.setScale(static_cast<float>(enemy->GetHealth()) / (enemy->GetMaxHealth() / 2), 1.0f);
				healthBarOutline.setFillColor(sf::Color(255, 0, 0, 128)); // Black, half transparent
				healthBarOutline.setOutlineThickness(0.5); // Outline border thickness
				healthBarOutline.setOutlineColor(sf::Color::Black); // Outline border color
				healthBarOutline.setPosition(enemy->GetSprite().getPosition().x - 16, enemy->GetSprite().getPosition().y - 45);
				m_window->draw(healthBarOutline);

				sf::RectangleShape healthBar(sf::Vector2f(15, 5));
				healthBar.setFillColor(sf::Color::Red);
				healthBar.setScale(static_cast<float>((enemy->GetHealth())) / (enemy->GetMaxHealth() / 2), 1.0f);
				healthBar.setPosition(enemy->GetSprite().getPosition().x - 16, enemy->GetSprite().getPosition().y - 45);
				m_window->draw(healthBar);
			}

			m_window->draw(enemy->GetSprite());
		}
		else if (enemy->GetState() == ENEMY_STATE_DEAD && enemy->GetExplosion()->isEnd() == false)
		{
			enemy->GetExplosion()->sprite.setPosition(enemy->GetSprite().getPosition());
			m_window->draw(enemy->GetExplosion()->sprite);
			enemy->GetExplosion()->update();

			// Enemies respawn if this is uncommented
			//if (enemy->GetExplosion()->isEnd())
				//enemy->SetState(ENEMY_STATE_DEAD_NO_EXPL);
		}

    if (m_player->IsFlying())
        DrawPlaneHealth();

    for (auto bullet : bullets)
        if (bullet->IsAlive())
        {
			bullet->GetAnimation()->sprite.setPosition(bullet->GetShape().getPosition());
			m_window->draw(bullet->GetAnimation()->sprite);
			bullet->GetAnimation()->update();
            //m_window->draw(bullet->GetShape());
            //printf("drawing bullet...\n");
        }

    DrawKillCounter();

    m_window->display();
}

void Renderer::DrawKillCounter()
{    
    sf::Font font;
    font.loadFromFile("utils/arial.ttf");

    std::ostringstream tmp;
    tmp << "Kills: " << m_player->GetKills();

    sf::Text text(tmp.str(), font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Red);
    text.setPosition(10, 80);

    m_window->draw(text);
}

// Safe to remove
void Renderer::AssignBullets(std::vector<Bullet*> bullets)
{
    //m_bullets = bullets;
}

void Renderer::Init(sf::RenderWindow* window)
{
    buffer.loadFromFile("sounds/shoot_laser.wav");
    sound.setBuffer(buffer);

    m_window = window;
}