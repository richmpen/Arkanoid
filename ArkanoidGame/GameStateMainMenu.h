#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace Arkanoid
{
	class Game;

	class GameStateMainMenu : public GameStateData 
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;
		Menu menu;
		sf::Sprite background;
		sf::Texture backgroundTexture;
	};

}
