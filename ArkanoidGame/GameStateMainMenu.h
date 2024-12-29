#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace Arkanoid
{
	class Game;

	class GameStateMainMenu
	{
	public:
		void Init();
		void Shutdown();
		void Control(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
	private:
		sf::Font font;
		Menu menu;
		sf::Sprite background;
		sf::Texture backgroundTexture;
	};

}
