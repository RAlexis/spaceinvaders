#include "menu.h"
#include "Defines.h"

Menu::Menu()
{
	m_fullscreen = false;
    m_selectedItemIndex = 0;

    m_bgTexture.loadFromFile("img/space_bg.png");
	m_bgTexture.setRepeated(true);
	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	m_menuMoveSoundBuffer.loadFromFile("sounds/menu_move.wav");
	m_menuMoveSound.setBuffer(m_menuMoveSoundBuffer);
	m_menuMoveSound.setVolume(10);

	m_menuPressSoundBuffer.loadFromFile("sounds/menu_press.wav");
	m_menuPressSound.setBuffer(m_menuPressSoundBuffer);
	m_menuPressSound.setVolume(3);

	m_font.loadFromFile("utils/arial.ttf");
}

Menu::~Menu()
{

}

// TODO: readjust button positions after we change the resolution
void Menu::MakeFullscreenOrWindowed(sf::RenderWindow& window)
{
	// Do we really need this?
	//window.close();

	if (!m_fullscreen)
	{
		WINDOW_WIDTH = sf::VideoMode::getFullscreenModes()[0].width;
		WINDOW_HEIGHT = sf::VideoMode::getFullscreenModes()[0].height;
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, sf::VideoMode::getDesktopMode().bitsPerPixel), WINDOW_NAME, sf::Style::Fullscreen);
	}
	else
	{
		WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
		WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, sf::VideoMode::getDesktopMode().bitsPerPixel), WINDOW_NAME, sf::Style::Close | sf::Style::Titlebar);
	}

	m_fullscreen = !m_fullscreen;
}

void Menu::LoadMainMenu()
{
	m_selectedItemIndex = 0;
	m_currentItemCount = 4;

	for (int i = 0; i < m_currentItemCount; ++i)
		m_menu[i].setCharacterSize(50);

	m_menu[0].setFont(m_font);
	m_menu[0].setFillColor(sf::Color::Green);
	m_menu[0].setString("Play");
	//menu[0].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 1));
	m_menu[0].setPosition(WINDOW_WIDTH / 2 - 350, WINDOW_HEIGHT / 2);

	m_menu[1].setFont(m_font);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setString("Reset");
	//menu[1].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 2));
	m_menu[1].setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2);

	m_menu[2].setFont(m_font);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setString("Credits");
	//menu[2].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 3));
	m_menu[2].setPosition(WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 2);

	m_menu[3].setFont(m_font);
	m_menu[3].setFillColor(sf::Color::White);
	m_menu[3].setString("Exit");
	//menu[3].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 3));
	m_menu[3].setPosition(WINDOW_WIDTH / 2 + 250, WINDOW_HEIGHT / 2);
}

// IDEA:
/*
	Rewrite each m_menu with what I need then draw it like that
	instead of using multiple arrays for each menu we want
*/

void Menu::LoadOptionsMenu()
{
	m_selectedItemIndex = 0;
	m_currentItemCount = 4;

	m_menu[0].setFont(m_font);
	m_menu[0].setFillColor(sf::Color::Green);
	m_menu[0].setString("Mute all sounds");
	//menu[0].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 1));
	m_menu[0].setPosition(WINDOW_WIDTH / 2 - 350, WINDOW_HEIGHT / 2);

	m_menu[1].setFont(m_font);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setString(m_fullscreen ? "Windowed" : "Fullscreen");
	//menu[1].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 2));
	m_menu[1].setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2);

	m_menu[2].setFont(m_font);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setString("Option 3");
	//menu[2].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 3));
	m_menu[2].setPosition(WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 2);

	m_menu[3].setFont(m_font);
	m_menu[3].setFillColor(sf::Color::White);
	m_menu[3].setString("Back");
	//menu[3].setPosition(sf::Vector2f(_resolution.x / 2, _resolution.y / (NUMBER_OF_ITEMS + 1) * 3));
	m_menu[3].setPosition(WINDOW_WIDTH / 2 + 250, WINDOW_HEIGHT / 2);
}

int Menu::ShowOptionsMenu(sf::RenderWindow* window)
{
	if (m_bgSprite.getTextureRect().width != WINDOW_WIDTH || m_bgSprite.getTextureRect().height != WINDOW_HEIGHT)
		m_bgSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	/*
	this->LoadOptionsMenu();
	//printf("showing options menu\n");

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				case sf::Keyboard::Left:
					this->MoveUp();
					break;

				case sf::Keyboard::Down:
				case sf::Keyboard::Right:
					this->MoveDown();
					break;

				case sf::Keyboard::Escape:
					m_menuPressSound.play();
					return ShowMenu(window);
					break;

				case sf::Keyboard::Space:
				case sf::Keyboard::Return:
					switch (this->GetPressedItem())
					{
					case 0:
					//	return MENU_SELECTION_NONE;
						break;
					case 1:
						MakeFullscreenOrWindowed(*window);
						break;
					case 2:
					//	return MENU_SELECTION_SHOW_OPTIONS;
					case 3:
						m_menuPressSound.play();
						return ShowMenu(window);
						break;
					}
					break;
				}
				break;

			case sf::Event::Closed:
				window->close();
				//return 0;
			}
		}

		window->clear();

		window->draw(m_bgSprite);
		this->Draw(window);

		if (GetHighscore() > 0)
			DrawHighscore(window);

		DrawGameName(window);

		window->display();
	}
	*/

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_menuPressSound.play();
				return ShowMenu(window);
			}
		}
		

		window->clear();
		window->draw(m_bgSprite);

		DrawCredits(window);
		DrawGameName(window);

		if (GetHighscore() > 0)
			DrawHighscore(window);

		window->display();

	}
}

void Menu::DrawCredits(sf::RenderWindow* _window)
{
	sf::Font font;
	font.loadFromFile("utils/arial.ttf");

	std::ostringstream msg;
	msg << "Razi Alexis, C.N. Mihai Eminescu, Oradea, clasa XII-G; profesor coordonator: Bolea Cristina";

	sf::Text text(msg.str(), font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);
	text.setPosition(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2);
	_window->draw(text);
}

// Show main menu
int Menu::ShowMenu(sf::RenderWindow* _window)
{
	if (m_bgSprite.getTextureRect().width != WINDOW_WIDTH || m_bgSprite.getTextureRect().height != WINDOW_HEIGHT)
		m_bgSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	this->LoadMainMenu();
	printf("showing main menu\n");

    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
				case sf::Keyboard::Left:
                    this->MoveUp();
                    break;

                case sf::Keyboard::Down:
				case sf::Keyboard::Right:
                    this->MoveDown();
                    break;

                case sf::Keyboard::Space:
                case sf::Keyboard::Return:
					m_menuPressSound.play();
                    switch (this->GetPressedItem())
                    {
                    case 0:
                        return MENU_SELECTION_NONE;
                        break;
                    case 1:
                        return MENU_SELECTION_RESET_GAME;
                        break;
                    case 2:
						return MENU_SELECTION_SHOW_OPTIONS;
					case 3:
                        _window->close();
                        break;
                    }
                    break;
                }
                break;

            case sf::Event::Closed:
                _window->close();
                return 0;
            }
        }

        _window->clear();

        _window->draw(m_bgSprite);

		DrawGameName(_window);

		if (GetHighscore() > 0)
			DrawHighscore(_window);

        this->Draw(_window);

        _window->display();
    }
}

void Menu::MoveUp()
{
    if (m_selectedItemIndex - 1 >= 0)
    {
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
        --m_selectedItemIndex;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Green);
		//m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
		m_menuMoveSound.play();
    }
}

void Menu::MoveDown()
{
    if (m_selectedItemIndex + 1 < m_currentItemCount)
    {
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
        ++m_selectedItemIndex;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Green);
		//m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
		m_menuMoveSound.play();
    }
}

void Menu::Draw(sf::RenderWindow* _window)
{
    for (int i = 0; i < m_currentItemCount; ++i)
        _window->draw(m_menu[i]);
}

void Menu::DrawGameName(sf::RenderWindow* _window)
{
	sf::Font font;
	font.loadFromFile("utils/arial.ttf");

	std::ostringstream score;
	score << "Space Invaders";

	sf::Text text(score.str(), font);
	text.setCharacterSize(80);
	text.setFillColor(sf::Color::Magenta);
	text.setPosition(WINDOW_WIDTH / 2 - 225, 100);
	_window->draw(text);
}

void Menu::DrawHighscore(sf::RenderWindow* _window)
{
	sf::Font font;
	font.loadFromFile("utils/Mathlete-Bulky.otf");

	std::ostringstream score;
	score << "Your highest score is " << GetHighscore() << "! Can you beat it?";

	sf::Text text(score.str(), font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(WINDOW_WIDTH / 2 - 250, 225);
	_window->draw(text);
}