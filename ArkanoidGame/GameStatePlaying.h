#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Plate.h"
#include "Ball.h"
#include "Block.h"
#include "GameStateData.h"

namespace Arkanoid
{
	class Game;
	class Block;
	class GameStatePlaying : public GameStateData
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		void BackgroundMove(float timeDelta);
	private:
		void SpawnBlocks();
		sf::Texture backgroundTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		std::vector<std::shared_ptr<Object>> GameObjects;
		std::vector<std::shared_ptr<Block>> blocks;
		int score = 0;
		bool gameStart = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text winRuleText;
		sf::Sprite backgroundSprite;
		float backgroundSpeed = 30.f;
		float backgroundWidth = 7334.f;
		float backgroundHeight = 2200.f;
		bool bgMoveRight = true;

		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
		sf::Sound gameWinSound;
	};

	 
}
