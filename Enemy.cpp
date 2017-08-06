#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int type, sf::Vector2f position, int playerLevel, Animation* anim)
    : m_type(type), m_position(position), expl(anim)
{
    m_maxHealth = m_enemyHealth + playerLevel * 8.0f;
	m_health = m_maxHealth;
	//std::cout << "Hp: " << m_health << std::endl;
    //m_position = { 500, 0 }; // Set position before we init the sprites

    //sExplosion = new Animation(300, 300, 256, 256, 48, 0.5);

    SetState(ENEMY_STATE_ALIVE);
    switch (m_type)
    {
        case ENEMY_TYPE_ASTEROID:
            InitAsteroidSprite();
            break;
        case ENEMY_TYPE_SPACESHIP:
            InitSpaceshipSprite();
            break;
        default:
            break;
    }
}

Enemy::~Enemy()
{

}

void Enemy::InitAsteroidSprite()
{
    if (!m_texture.loadFromFile("img/asteroid.png"))
        printf("[ERROR] Could not load img/asteroid.png!\n");

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
    //m_sprite.setOrigin({ 45, 45 });
    m_sprite.setScale(0.5f, 0.5f);
    //m_sprite.setRotation(0.0f);
    m_sprite.setPosition(m_position);
}

void Enemy::InitSpaceshipSprite()
{
    if (!m_texture.loadFromFile("img/enemy_spaceship.png"))
        printf("[ERROR] Could not load img/enemy_spaceship.png!\n");

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); // Sprite is 32x32
    m_sprite.setOrigin({ 16, 16 }); // Half of 32 (center of the sprite basically)
    m_sprite.setScale(1.f, 1.f);
    m_sprite.setRotation(0.0f);
    m_sprite.rotate(180.0f);
    m_sprite.setPosition(m_position);
}

void Enemy::Update()
{
    if (!IsAlive())
        return;

	//updateAnimPos();
	//expl->update();

    switch (GetType())
    {
        case ENEMY_TYPE_ASTEROID:
            HandleAsteroidMovement();
            break;

        case ENEMY_TYPE_SPACESHIP:
            UpdateSpaceship();
            break;

        default:
            break;
    }
}

void Enemy::TakeDamage(int damage)
{
	if (damage > GetHealth())
	{
		SetHealth(0);
		SetState(ENEMY_STATE_DEAD);
	}
	else
		SetHealth(GetHealth() - damage);
}

void Enemy::UpdateSpaceship()
{
    if (!IsAlive())
        return;

	// Apparently this doesn't work
	if (m_sprite.getPosition().y >= WINDOW_HEIGHT)
        SetState(ENEMY_STATE_DEAD_NO_EXPL);

    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + SPACESHIP_SPEED);
}

// Falling
void Enemy::HandleAsteroidMovement()
{
    if (!IsAlive())
        return;

    if (m_sprite.getPosition().y >= WINDOW_HEIGHT)
        SetState(ENEMY_STATE_DEAD_NO_EXPL);

    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + ASTEROID_SPEED);
}

