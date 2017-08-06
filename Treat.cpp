#include "Treat.h"

Treat::Treat(sf::Vector2f position)
{
    InitTexture();
    SetPosition(position);
    m_moneyValue = DEFAULT_MONEY_VALUE;
}

Treat::~Treat()
{

}

void Treat::InitTexture()
{
    if (!m_texture.loadFromFile("img/coin.png"))
        printf("[ERROR] Could not load img/coin.png!");

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
    m_sprite.setScale(0.25f, 0.25f);
    m_sprite.setPosition(sf::Vector2f(200, 200));
}

void Treat::Update()
{

}