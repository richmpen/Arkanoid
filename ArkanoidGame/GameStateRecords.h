#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameStateData.h"

namespace Arkanoid
{
	class Game;

	class GameStateRecords : public GameStateData
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	
}
