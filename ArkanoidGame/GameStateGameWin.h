#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace Arkanoid
{
	class Game;

	class GameStateGameWin : public GameStateData
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;

		float timeSinceGameWin = 0.f;

		sf::RectangleShape background;
		sf::Text gameWinText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
		Menu menu;
	};


}
