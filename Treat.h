#ifndef _TREAT_H
#define _TREAT_H

#include "SFML/Graphics.hpp"

#define DEFAULT_MONEY_VALUE 1

class Treat
{
    public:
        Treat(sf::Vector2f position);
        ~Treat();

        void Update();
        void InitTexture();
        
        void SetPosition(sf::Vector2f position)
        {
            m_sprite.setPosition(position);
        }

        sf::Sprite GetSprite()
        {
            return m_sprite;
        }

        void ModMoneyValue(int value)
        {
            m_moneyValue += value;
        }

        int GetMoneyValue()
        {
            return m_moneyValue;
        }

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        int m_moneyValue;
};

#endif