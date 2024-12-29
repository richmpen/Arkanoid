#include "Application.h"
#include <cstdlib>

namespace Arkanoid
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	Application::Application() :
		window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME)
	{
		
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	void Application::Run()
	{
		sf::Clock gameClock;

		while (window.isOpen()) {

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.Control(window);

			if (!window.isOpen()) {
				break;
			}

			if (game.Update(TIME_PER_FRAME))
			{
				window.clear();

				game.Draw(window);

				window.display();
			}
			else
			{
				window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < TIME_PER_FRAME) {
				sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
			}
		}
	}

}