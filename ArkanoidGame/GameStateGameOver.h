#pragma once
#include "SFML/Graphics.hpp"

namespace Arkanoid
{
	class Game;

	class GameStateGameOver
	{
	public:
		void Init();
		void Shutdown();
		void Control(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
	private:
		sf::Font font;

		float timeSinceGameOver = 0.f;

		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
	};


}
