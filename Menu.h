#ifndef _MENU_H
#define _MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

// Number of buttons in the menu
//#define NUMBER_OF_ITEMS 4
const int maxItems = 4;

enum MenuOptions
{
    MENU_SELECTION_NONE         = 0,
    MENU_SELECTION_RESET_GAME   = 1,
	MENU_SELECTION_SHOW_OPTIONS = 2,
    MENU_SELECTION_EXIT         = 3,
	
	// Options menu
	MENU_SELECTION_FULLSCREEN   = 4
};

class Menu
{
public:
    Menu();
    ~Menu();

    int ShowMenu(sf::RenderWindow* _window);
	int ShowOptionsMenu(sf::RenderWindow* window);

    void MoveUp();

    void MoveDown();

    int GetPressedItem()
    {
        return m_selectedItemIndex;
    }

    void Draw(sf::RenderWindow* window);

	void LoadMainMenu();
	void LoadOptionsMenu();
	void MakeFullscreenOrWindowed(sf::RenderWindow& window);

	void SetHighscore(int hs)
	{
		m_highscore = hs;
	}

	int GetHighscore()
	{
		return m_highscore;
	}

	void DrawHighscore(sf::RenderWindow* _window);
	void DrawGameName(sf::RenderWindow* _window);
	void DrawCredits(sf::RenderWindow* _window);

private:
    int m_selectedItemIndex;
    sf::Font m_font;
	int m_currentItemCount;
    sf::Text m_menu[maxItems];
    sf::Texture m_bgTexture;
    sf::Sprite m_bgSprite;

	sf::SoundBuffer m_menuMoveSoundBuffer;
	sf::Sound m_menuMoveSound;

	sf::SoundBuffer m_menuPressSoundBuffer;
	sf::Sound m_menuPressSound;

	int m_fullscreen;

	int m_highscore;
};

#endif