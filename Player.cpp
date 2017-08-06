#include "Player.h"
#include <iostream>

const float acceleration = 0.2f; // Doesn't seem to affect much
const float maxSpeed = 12.0f;
const float rotationSpeed = 0.3f;

const float dec = 0.3f;
const float turnSpeed = 0.08f;
float speed = 0.0f;
float angle = 0.0f;

Player::Player()
{
    m_vehicle = new Vehicle(this);
    LoadAndInitPlaneSprite();
    //LoadAndInitPlayerSprite();
    SetState(PLAYER_STATE_ALIVE);
	SetLevel(1);
	m_score = 0;
    m_money = 0;
    m_health = DEFAULT_PLAYER_HP;
    m_maxHealth = DEFAULT_PLAYER_HP;
    m_position = { 300, 300 }; // @todo change this to some default value
    SetMoving(false);
    SetShooting(false);

    m_kills = 0;
	m_KillCounterWhenLastLeveledUp = 0;
	m_xp = 0;
	m_xpMultiplier = 1.0f;

    bulletBuffer.loadFromFile("sounds/shoot_laser.wav");
    bulletSound.setBuffer(bulletBuffer);
    bulletSound.setVolume(5); // @todo change this from the menu...

    spaceshipBuffer.loadFromFile("sounds/sapceship_thrust.flac"); // @todo change the name from "sapceship" to "spaceship"
    spaceshipSound.setBuffer(spaceshipBuffer);
    spaceshipSound.setVolume(8);

	bulletTexture.loadFromFile("images/fire_blue.png");
	bulletAnimation = new Animation(bulletTexture, 0, 0, 32, 64, 16, 0.8);
}

Player::~Player()
{

}

void Player::LoadAndInitPlayerSprite()
{
    if(IsFlying())
        ResetFlyingSettings();

    if (!m_texture.loadFromFile("img/spaceman_robot.png"))
        printf("[ERROR] Could not load img/spaceman_robot.png!");

    SetFlying(false); // We're not on the plane anymore

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 96-32-32, 128-32-32-32)); // Sprite is 32x32 (not the whole .png)
    m_sprite.setOrigin({ 16, 16 }); // Half of 32 (center of the sprite basically)
    // This needs to be set because if the plane was loaded earlier, it will still be set to the plane's scale
    m_sprite.setScale(1.0f, 1.0f);
    m_sprite.setRotation(0.0f);
    m_sprite.setPosition(m_position);
}

void Player::LoadAndInitHelicopterSprite()
{
    if (IsFlying())
        ResetFlyingSettings();
}

void Player::ResetFlyingSettings()
{
    speed = 0;
    angle = 0;
}

void Player::LoadAndInitPlaneSprite()
{
    ResetFlyingSettings();

    if (!m_texture.loadFromFile("img/spaceship_2.png"))
        printf("[ERROR] Could not load img/spaceship_2.png!");

    m_source = sf::Vector2i(0, 0); // Which movement direction in file

    SetFlying(true);
    m_vehicle->SetType(VEHICLE_TYPE_PLANE);

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
    m_sprite.setOrigin({ 20, 20 });
    m_sprite.setScale(1.5f, 1.5f);
    m_sprite.setRotation(0.0f);
    m_sprite.setPosition(m_position);
}

void Player::CollisionCheck(sf::Vector2f &currentPos)
{   
    // Map borders
    // There is a lot of room for improvements right here
    if (currentPos.x < 10.0f)
        currentPos.x = 10.0f;
    else if (currentPos.x > WINDOW_WIDTH)
        currentPos.x = WINDOW_WIDTH;

    if (currentPos.y < 10.0f)
        currentPos.y = 10.0f;
    // Ground height check (sand)
    // @todo if the player is on a plane, destroy the plane, and deal GetMaxHealth() / 2 damage to player
    //else if (currentPos.y + 16 > WINDOW_HEIGHT - GROUND_HEIGHT) // 16 = half of 32 (player sprite is 32x32)
    else if (currentPos.y > WINDOW_HEIGHT)
    {
        //currentPos.y = WINDOW_HEIGHT - GROUND_HEIGHT;
        currentPos.y = WINDOW_HEIGHT;

        //if (IsFlying())
          //  LoadAndInitPlayerSprite();
    }

    //m_sprite.setPosition(currentPos); // Update our position
}

void Player::HandleGroundMovement()
{
    // Checking for movement
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_position.y -= PLAYER_MOVE_VALUE;
        m_source.y = 3;
    }*/
        
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_position.y += PLAYER_MOVE_VALUE;
        m_source.y = 0;
    }*/

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_position.x -= PLAYER_MOVE_VALUE;
        m_source.y = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_position.x += PLAYER_MOVE_VALUE;
        m_source.y = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        SetHealth(GetHealth() - 1);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) // Enter the plane
    {
        LoadAndInitPlaneSprite();
        return;
    }

    UpdateSpriteDirection();
    CollisionCheck(m_position);
    m_sprite.setPosition(m_position);
}

void Player::UpdateSpriteDirection()
{
    m_time = m_clock.getElapsedTime();
    if (m_time.asMilliseconds() >= 300)
    {
        m_source.x++;

        if (m_source.x * 32 >= 3) // @todo fix m_texture.getSize().x
            m_source.x = 0;

        m_clock.restart();
    }

    m_sprite.setTextureRect(sf::IntRect(m_source.x * 32, m_source.y * 32, 32, 32));
}

void Player::UpdateSpaceshipSpriteDirection()
{
    if (!IsMoving())
    {
        m_source.x = 1;
        m_source.y = 0;
    }
    else if (IsMovingLeft() && !IsMovingLeftAndUp() && !IsMovingLeftAndDown())
    {
        m_source.x = 0;
        m_source.y = 0;
    }
    else if (IsMovingLeftAndUp())
    {
        m_source.x = 0;
        m_source.y = 1;
    }
    else if (IsMovingLeftAndDown())
    {
        // These are the correct ones but the sprite is bugged or something
        //m_source.x = 0;
        //m_source.y = 2;

        m_source.x = 0;
        m_source.y = 1;
    }
    else if (IsMovingRight() && !IsMovingRightAndUp() && !IsMovingRightAndDown())
    {
        m_source.x = 2;
        m_source.y = 0;
    }
    else if (IsMovingRightAndUp())
    {
        m_source.x = 2;
        m_source.y = 1;
    }
    else if (IsMovingRightAndDown())
    {
        // These are the correct ones but the sprite is bugged or something
        //m_source.x = 2;
        //m_source.y = 2;

        m_source.x = 2;
        m_source.y = 1;
    }
    
    //printf("X: %d, Y: %d\n", m_source.x, m_source.y);

    m_sprite.setTextureRect(sf::IntRect(m_source.x * 40, m_source.y * 40, 40, 40));
}

void Player::HandleAirMovement()
{
    // Direction
    //bool up = 0, down = 0, right = 0, left = 0;

	// We already delete bullets in Game.cpp
	/*std::vector<Bullet*>::iterator bullet = m_bullets.begin();
	while (bullet != m_bullets.end())
	{
		if (!(*bullet)->IsAlive())
			bullet = m_bullets.erase(bullet);
		++bullet;
	}*/

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //up = 1;
        SetMoving(true);
        m_source.x = 1;
        m_source.y = 1;
        m_position.y -= PLAYER_MOVE_VALUE;
        if (spaceshipSound.getStatus() != spaceshipSound.Playing)
            spaceshipSound.play();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //right = 1;
        SetMoving(true);
        m_source.x = 2;
        m_source.y = 1;
        m_position.x += PLAYER_MOVE_VALUE;
        if (spaceshipSound.getStatus() != spaceshipSound.Playing)
            spaceshipSound.play();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //down = 1;
        SetMoving(true);
        m_source.x = 1;
        m_source.y = 1;
        m_position.y += PLAYER_MOVE_VALUE;
        if (spaceshipSound.getStatus() != spaceshipSound.Playing)
            spaceshipSound.play();
    }
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //left = 1;
        SetMoving(true);
        m_source.x = 0;
        m_source.y = 1;
        m_position.x -= PLAYER_MOVE_VALUE;
        if (spaceshipSound.getStatus() != spaceshipSound.Playing)
            spaceshipSound.play();
    }

    // If the spaceship sound is playing and we're not pressing any keys to move
    if (spaceshipSound.getStatus() == spaceshipSound.Playing && 
       ! (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        spaceshipSound.stop();

    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        //m_vehicle->SetHealth(m_vehicle->GetHealth() - 30);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) // Eject from plane
    {
        LoadAndInitPlayerSprite();
        return; // We're done
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !IsShooting())
    {
		// every bullet adds 1 to the score
		SetScore(GetScore() + 1);

		SetShooting(true);
        //printf("creating bullet...\n");
        m_bullets.push_back(new Bullet(sf::Vector2f(m_position.x, m_position.y), m_level, bulletAnimation));

        bulletSound.play();
    }

    // You can't shoot forever by pressing space, you have to tap it
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        SetShooting(false);

    UpdateSpaceshipSpriteDirection();
	CollisionCheck(m_position); // map collision
    m_sprite.setPosition(m_position);

    /*
    if (up && speed < maxSpeed)
        if (speed < 0)
            speed += dec;
        else
            speed += acceleration;

    if (down && speed > -maxSpeed)
        if (speed > 0)
            speed -= dec;
        else
            speed -= acceleration;

    if (!up && !down)
    {
        if (speed - dec > 0)
            speed -= dec;
        else if (speed + dec < 0)
            speed += dec;
        else speed = 0;
    }

    if (right && speed != 0)
        angle += turnSpeed * speed / maxSpeed;

    if (left && speed != 0)
        angle -= turnSpeed * speed / maxSpeed;

    // If we don't do this, the position will be set to x = 0, y = 0 at spawn
    if (m_position.x > 0 && m_position.y > 0)//&&
        //   m_position.x != 10.0f && m_position.y != 0.0f &&
        //  m_position.x != WINDOW_WIDTH && m_position.y != WINDOW_HEIGHT)
    {
        m_position.x += sin(angle) * speed;
        m_position.y -= cos(angle) * speed;
    }
    // If we get here it means we've just spawned
    // (called when playing for the first time)
    else if (m_position.x == 0 && m_position.y == 0)
    {
        m_position = { 300, 300 };
    }
    else
    {
        // @todo fix this
        //CollisionCheck(m_position);
        // @todo change these to some default value
        //m_position.x = 300;
        //m_position.y = 300;
    }

    CollisionCheck(m_position);

    m_sprite.setPosition(m_position);
    m_sprite.setRotation(angle * 180 / 3.141593); // Warning here: C4244 conversion from 'double' to 'float'*/
}

void Player::Die()
{
	// Reset player settings
	SetLevel(1);
	m_score = 0;
	m_money = 0;
	m_health = DEFAULT_PLAYER_HP;
	m_maxHealth = DEFAULT_PLAYER_HP;
	m_position = { (float)WINDOW_WIDTH / 2, (float) WINDOW_HEIGHT - 10 };
	SetMoving(false);
	SetShooting(false);

	m_kills = 0;
	m_KillCounterWhenLastLeveledUp = 0;
	m_xp = 0;
	m_xpMultiplier = 1.0f;


}

void Player::AddXp(int enemyType)
{
	float xpToBeAdded;
	switch (enemyType)
	{
		case ENEMY_TYPE_ASTEROID:
			xpToBeAdded = rand() % 3 + 1 + 4;
			break;
		case ENEMY_TYPE_SPACESHIP:
			xpToBeAdded = rand() % 11 + 1 + 3;
			break;
		
		// How did we even get here in the first place?
		default:
			return;
	}

	xpToBeAdded *= m_xpMultiplier;
	m_xp += round(xpToBeAdded);
	if (m_xp > xpForLevel[GetLevel() - 1])
	{
		SetLevel(GetLevel() + 1);
		m_xpMultiplier += 0.18;
	}

	// we add the XP as score x2
	SetScore(GetScore() + m_xp * 2);

	//std::cout << "xptobeadded is " << xpToBeAdded << " -- xp mult " << m_xpMultiplier << std::endl;
}

void Player::Update()
{    
    if (GetState() == PLAYER_STATE_ALIVE)
    {
		//if (GetKills() % 5 == 0 && GetKills() > 0 && GetKills() != m_KillCounterWhenLastLeveledUp)
		{
			//m_KillCounterWhenLastLeveledUp = GetKills();
			//SetLevel(GetLevel() + 1);
			//std::cout << "Level is " << GetLevel() << std::endl;
		}

        if (IsFlying())
        {
            HandleAirMovement();

            if (m_vehicle->GetHealth() == 0)
                m_vehicle->Die();
        }
        else
        {
            HandleGroundMovement();

            // We ded
            if (GetHealth() == 0)
                Die();
        }
    }
}