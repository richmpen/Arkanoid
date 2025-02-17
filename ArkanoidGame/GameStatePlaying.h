#pragma once
#include <unordered_map>
#include "LevelLoader.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Plate.h"
#include "Ball.h"
#include "BlockFactory.h"
#include "GameStateData.h"
#include "IObserver.h"

namespace Arkanoid
{
	class Game;
	class Block;
	class GameStatePlaying : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlaying>
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY);
		void BackgroundMove(float timeDelta);
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;
	private:
		void SpawnBlocks();
		sf::Texture backgroundTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		std::vector<std::shared_ptr<Object>> gameObjects;
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

		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		int breackableBlocksCount = 0;

		LevelLoader levelLoader;
		int currentLevel = 0;
	};

	 
}
