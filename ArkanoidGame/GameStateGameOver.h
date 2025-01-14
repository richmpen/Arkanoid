#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateData.h"

namespace Arkanoid
{
	class Game;

	class GameStateGameOver : public GameStateData
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;

		float timeSinceGameOver = 0.f;

		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
	};


}
