#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Arkanoid
{
	class Game;

	class GameStateRecords
	{
	public:
		void Init();
		void Shutdown();
		void Control(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
	private:
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	
}
