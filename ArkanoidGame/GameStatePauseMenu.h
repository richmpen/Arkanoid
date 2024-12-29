#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace Arkanoid
{
	class Game;

	class GameStatePauseMenu
	{
	public:
		void Init();
		void Shutdown();
		void Control(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	};

}
