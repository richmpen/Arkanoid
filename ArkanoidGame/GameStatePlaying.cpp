#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include "Object.h"
#include <string>
#include "Block.h"
#include <vector>
#include <random>
#include <algorithm>
#include "LevelLoader.h"

namespace Arkanoid
{
	void GameStatePlaying::Init()
	{	
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Alata-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));
		assert(gameWinSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "GameWin.wav"));
		assert(backgroundTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "BackgroudnGameScene.png"));

		factories.emplace(BlockType::Simple, std::make_unique<SimpleBlockFactory>());
		factories.emplace(BlockType::ThreeHit, std::make_unique<ThreeHitBlockFactory>());
		factories.emplace(BlockType::Unbreackable, std::make_unique<UnbreackableBlockFactory>());

		
		InitSprite(backgroundSprite, backgroundWidth,backgroundHeight, backgroundTexture);
		backgroundSprite.setPosition(0,0);

		gameObjects.emplace_back(std::make_shared<Plate>(sf::Vector2f(SETTINGS.SCREEN_WIDTH/2,SETTINGS.SCREEN_HEIGHT-SETTINGS.PLATE_HEIGHT/2)));
		 Plate* plate = (Plate*)gameObjects.back().get();
		 auto ball = std::make_shared<Ball>(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f));
		 ball->AddObserver(weak_from_this());
		 gameObjects.emplace_back(ball);
		
		gameStart = false;

		SpawnBlocks();

		score = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(32);
		scoreText.setFillColor(sf::Color::Blue);

		
		winRuleText.setFont(font);
		winRuleText.setCharacterSize(32);
		winRuleText.setFillColor(sf::Color::Red);
		winRuleText.setString("you need to Win: " + std::to_string(SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW));
		winRuleText.setOrigin(GetTextOrigin(winRuleText, { 1.f, 0.f }));

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(32);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Press SPACE to Play \n ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
		gameWinSound.setBuffer(gameWinSoundBuffer);
	}

	void GameStatePlaying::Shutdown(){}

	void GameStatePlaying::Control(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlaying::Update(float timeDelta)
	{

		
		static auto updateFunctor = [timeDelta](auto obj) { obj->Update(timeDelta); };

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::for_each(blocks.begin(), blocks.end(), updateFunctor);


		std::shared_ptr <Plate> plate = std::dynamic_pointer_cast<Plate>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		BackgroundMove(timeDelta);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameStart = true;
		}
		if (gameStart) {
			ball->Update(timeDelta);
		}
		else {
			ball->SetPositionOnPlate(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f));
		}
		
		auto isCollision = plate->CheckCollision(ball);

		bool needInverseDirX = false;
		bool needInverseDirY = false;


		bool hasBrokeOneBlock = false;

		blocks.erase(
			std::remove_if(blocks.begin(), blocks.end(),
				[ball, &hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this](const auto& block) {
					if ((!hasBrokeOneBlock) && block->CheckCollision(ball)) {
						hasBrokeOneBlock = true;
						const auto ballPos = ball->GetPosition();
						const auto blockRect = block->GetRect();

						GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
						
					}
					return block->isDestroyed();
				}),
			blocks.end()
					);
		if (needInverseDirX) {
			ball->Turning(Turn::X);
		}
		if (needInverseDirY) {
			ball->Turning(Turn::Y);
		}

			/*const bool GameWin = blocks.size() <= unbreackableBlocksCount;
			const bool GameOver = !plate->CheckCollision(ball) && ball->GetPosition().y > plate->GetRect().top;
		
			if (GameOver)
			{
				gameOverSound.play();
		
				Game& game = Application::Instance().GetGame();
				game.ShowRecords();
				game.LooseGame();
			}
			if (GameWin)
			{
				gameWinSound.play();
		
				Game& game = Application::Instance().GetGame();
				game.ShowRecords();
				game.LoadNextLevel();
			}*/
		
			scoreText.setString("Score: " + std::to_string(score));
	}
	
	void GameStatePlaying::Draw(sf::RenderWindow& window)
	{
		window.draw(backgroundSprite);
		
		static auto drawFunc = [&window](auto block) { block->Draw(window); };
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);

		
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		winRuleText.setOrigin(GetTextOrigin(winRuleText, { 0.f, 0.f }));
		winRuleText.setPosition(150.f, 10.f);
		window.draw(winRuleText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	

	void GameStatePlaying::BackgroundMove(float timeDelta)
	{
		if (bgMoveRight)
		{
			backgroundSprite.setPosition(backgroundSprite.getPosition().x - backgroundSpeed * timeDelta, backgroundSprite.getPosition().y);
			if (backgroundSprite.getPosition().x <= -(backgroundWidth/2 - SETTINGS.SCREEN_WIDTH))
			{
				bgMoveRight = false;
			}
		}
		else
		{
			backgroundSprite.setPosition(backgroundSprite.getPosition().x + backgroundSpeed * timeDelta, backgroundSprite.getPosition().y);
			if (backgroundSprite.getPosition().x >= (backgroundWidth/2 - SETTINGS.SCREEN_WIDTH))
			{
				bgMoveRight = true;
			}
		}
	}
	void GameStatePlaying::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1) {
			Game& game = Application::Instance().GetGame();

			game.WinGame();
		}
		else
		{
			std::shared_ptr <Plate> platform = std::dynamic_pointer_cast<Plate>(gameObjects[0]);
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->restart();
			ball->restart();

			blocks.clear();
			++currentLevel;
			SpawnBlocks();
			gameStart = false;
		}
	}
	void GameStatePlaying::SpawnBlocks()
	{
		for (const auto& pair : factories) {
			pair.second->CleatCounter();
		}

		auto self = weak_from_this();

		auto level = levelLoader.GetLevel(currentLevel);

		for (auto pairPosBlockType : level.m_blocks) {

			auto blockType = pairPosBlockType.second;
			sf::Vector2i pos = pairPosBlockType.first;

			sf::Vector2f position{
			(float)SETTINGS.BLOCK_SPACING_HORIZONTAL + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SPACING_HORIZONTAL),
				(float)100.f + pos.y * (SETTINGS.BLOCK_HEIGHT + SETTINGS.BLOCK_SPACING_VERTICAL)
			};

			blocks.emplace_back(factories[blockType]->CreateBlock(position));
			blocks.back()->AddObserver(self);
		}

		
		for (const auto& pair : factories) {
			breackableBlocksCount += pair.second->GetcreatedBreackableBlocksCount();
		}
		
	}

	void GameStatePlaying::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block) {
			--breackableBlocksCount;
			Game& game = Application::Instance().GetGame();
			if (breackableBlocksCount == 0) {
				game.LoadNextLevel();
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetRect().top) {
				gameOverSound.play();
				Application::Instance().GetGame().LooseGame();
			}
		}
	}

	void GameStatePlaying::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY) {

		if (ballPos.y > blockRect.top + blockRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < blockRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			needInverseDirX = true;
		}
	}
	
}

