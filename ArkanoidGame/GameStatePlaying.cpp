#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include "Object.h"
#include <string>
#include "Block.h"

namespace Arkanoid
{
	void GameStatePlaying::Init()
	{	
		assert(font.loadFromFile(FONTS_PATH + "Alata-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		assert(gameWinSoundBuffer.loadFromFile(SOUNDS_PATH + "GameWin.wav"));
		assert(backgroundTexture.loadFromFile(TEXTURES_PATH + "BackgroudnGameScene.png"));
		
		InitSprite(backgroundSprite, backgroundWidth,backgroundHeight, backgroundTexture);
		backgroundSprite.setPosition(0,0);

		GameObjects.emplace_back(std::make_shared<Plate>(sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT-PLATE_HEIGHT/2)));
		 Plate* plate = (Plate*)GameObjects.back().get();
		GameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f))));
		
		gameStart = false;

		SpawnBlocks();

		score = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(32);
		scoreText.setFillColor(sf::Color::Blue);

		
		winRuleText.setFont(font);
		winRuleText.setCharacterSize(32);
		winRuleText.setFillColor(sf::Color::Red);
		winRuleText.setString("you need to Win: " + std::to_string(BLOCKS_COUNT_ROWS*BLOCKS_COUNT_IN_ROW));
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
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlaying::Update(float timeDelta)
	{

		
		static auto updateFunctor = [timeDelta](auto obj) { obj->Update(timeDelta); };

		std::for_each(GameObjects.begin(), GameObjects.end(), updateFunctor);
		std::for_each(blocks.begin(), blocks.end(), updateFunctor);


		std::shared_ptr <Plate> plate = std::dynamic_pointer_cast<Plate>(GameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(GameObjects[1]);
		BackgroundMove(timeDelta);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameStart = true;
		}
		if (gameStart) {
			ball->CalculatingTrajectory(timeDelta);
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

			const bool GameWin = blocks.empty();
			const bool GameOver = !plate->CheckCollision(ball) && ball->GetPosition().y > plate->GetRect().top;
		
			if (GameOver)
			{
				gameOverSound.play();
		
				Game& game = Application::Instance().GetGame();
				game.UpdateRecord(PLAYER_NAME, score);
				game.PushState(GameStateType::GameOver, false);
			}
			if (GameWin)
			{
				gameWinSound.play();
		
				Game& game = Application::Instance().GetGame();
				game.UpdateRecord(PLAYER_NAME, score);
				game.PushState(GameStateType::GameWin, false);
			}
		
			scoreText.setString("Score: " + std::to_string(score));
	}
	
	void GameStatePlaying::Draw(sf::RenderWindow& window)
	{
		window.draw(backgroundSprite);
		
		static auto drawFunc = [&window](auto block) { block->Draw(window); };
		std::for_each(GameObjects.begin(), GameObjects.end(), drawFunc);
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
			if (backgroundSprite.getPosition().x <= -(backgroundWidth/2 - SCREEN_WIDTH))
			{
				bgMoveRight = false;
			}
		}
		else
		{
			backgroundSprite.setPosition(backgroundSprite.getPosition().x + backgroundSpeed * timeDelta, backgroundSprite.getPosition().y);
			if (backgroundSprite.getPosition().x >= (backgroundWidth/2 - SCREEN_WIDTH))
			{
				bgMoveRight = true;
			}
		}
	}
	void GameStatePlaying::SpawnBlocks()
	{
		int row = 0;
		for(; row < BLOCKS_COUNT_ROWS; ++row)
		{
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col)
			{
				blocks.emplace_back(std::make_shared<SmoothDestroyableBlock>("SmoothDestroyableBlock.png", sf::Vector2f(
					BLOCK_SPACING_HORIZONTAL + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SPACING_HORIZONTAL),
					100.f + row * (BLOCK_HEIGHT + BLOCK_SPACING_VERTICAL) ), sf::Color::White));
			}
		}

		for (int col = 0; col < 4; ++col) {
			blocks.emplace_back(std::make_shared<UnbreackableBlock>("UnbreackableBlock.png",sf::Vector2f(
				BLOCK_SPACING_HORIZONTAL + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SPACING_HORIZONTAL),
				100.f + row * (BLOCK_HEIGHT + BLOCK_SPACING_VERTICAL))));
		}
		for (int col = 3; col < 8; ++col) {
			blocks.emplace_back(std::make_shared<Block>("Block.png", sf::Vector2f(
					BLOCK_SPACING_HORIZONTAL + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SPACING_HORIZONTAL),
					100.f + row * (BLOCK_HEIGHT + BLOCK_SPACING_VERTICAL))));
		}
		for (int col = 8; col < 12; ++col) {
			blocks.emplace_back(std::make_shared<CrumblingBlock>("CrumblingBlock1.png", sf::Vector2f(
					BLOCK_SPACING_HORIZONTAL + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SPACING_HORIZONTAL),
					100.f + row * (BLOCK_HEIGHT + BLOCK_SPACING_VERTICAL))));
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

