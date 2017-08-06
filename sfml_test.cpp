#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

// Default values
int WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
int WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close | sf::Style::Titlebar);
    // Max width & height for a screen (ex 1366x768)
    //std::cout << sf::VideoMode::getFullscreenModes()[0].width << ' ' << sf::VideoMode::getFullscreenModes()[0].height;

    Player* player = new Player();
    Renderer* renderer = new Renderer(player);
    Game game(&window, player, renderer);

	//sf::Music music;
	//music.openFromFile("sounds/background_music.wav");
	//music.setVolume(3);
	//music.play();
	//music.setLoop(true);

    Menu menu;

	// Start in full screen
	menu.MakeFullscreenOrWindowed(window);
	// So we can draw the highscore on the menu :)
	menu.SetHighscore(game.GetHighScore());

	switch (menu.ShowMenu(&window))
	{
		case MENU_SELECTION_RESET_GAME:
			game.GetPlayer()->Die();
			game.ClearEnemiesAndBullets();
			game.GetRenderer()->SetLastActionMessage("You have reset the game.");
			break;

		case MENU_SELECTION_SHOW_OPTIONS:
			menu.ShowOptionsMenu(&window);
			break;

		default:
			break;
	}

    while (window.isOpen())
    {
		// This is if we resize the window
		// But it is disabled, as it causes lag
		//std::cout << window.getSize().x << ' ' << window.getSize().y << std::endl;
		if (window.getSize().x != WINDOW_WIDTH || window.getSize().y != WINDOW_HEIGHT)
		{
			WINDOW_WIDTH = window.getSize().x;
			WINDOW_HEIGHT = window.getSize().y;
			window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, sf::VideoMode::getDesktopMode().bitsPerPixel), WINDOW_NAME);
		}

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                switch (menu.ShowMenu(&window))
                {
                    case MENU_SELECTION_RESET_GAME:
						game.GetPlayer()->Die();
						game.ClearEnemiesAndBullets();
						game.GetRenderer()->SetLastActionMessage("You have reset the game.");
                        break;

					case MENU_SELECTION_SHOW_OPTIONS:
						menu.ShowOptionsMenu(&window);
						break;

                    default:
                        break;
                }
            }
        }
        
        // This has to be outside the while loop, otherwise things won't be smooth (movement, for example)
       game.Update();
    }

    return 0;
}