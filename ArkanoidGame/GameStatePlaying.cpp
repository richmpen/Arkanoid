#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include "Object.h"
#include <string>

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
		winRuleText.setString("you need to Win: " + std::to_string(WIN_SCORE));
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
		for (auto&& object:GameObjects)
		{
			object->Update(timeDelta);
		}
		for (auto&& item:blocks)
		{
			item->Update(timeDelta);
		}

		std::shared_ptr<Plate> plate = std::dynamic_pointer_cast<Plate>(GameObjects[0]);
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
		
		bool collisionDetected = false;
		for (size_t i = 0; i < blocks.size(); ++i) {
			const auto block = blocks[i].get();
			if (block->CheckCollisionWithBall(*ball)) {
				const auto ballPos = ball->GetPosition();
				const auto blockRect = block->GetRect();
				
				if (ballPos.y >= blockRect.top + blockRect.height) {  
					ball->Turning(Turn::Y);
					collisionDetected = true;
				}
				else if (ballPos.y <= blockRect.top) { 
					ball->Turning(Turn::Y);
					collisionDetected = true;
				}
				else if (ballPos.x <= blockRect.left) {  
					ball->Turning(Turn::X);
					collisionDetected = true;
				}
				else if (ballPos.x >= blockRect.left + blockRect.width) {  
					ball->Turning(Turn::X);
					collisionDetected = true;
				}
            
				score += 1;
				blocks.erase(blocks.begin() + i);
				if (collisionDetected) break;
				i--;
			}
		}
		
		if (plate->CheckCollisionWithBall(*ball)) {
			ball->Turning(Turn::Y);
		}

		const bool GameWin = blocks.empty();
		const bool GameOver = !plate->CheckCollisionWithBall(*ball) && ball->GetPosition().y > plate->GetRect().top;

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
		for (auto&& object:GameObjects)
		{
			object->Draw(window);
		}
		for (auto&& item:blocks)
		{
			item->Draw(window);
		}
		
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
		
		for(int row = 0; row < BLOCKS_COUNT_ROWS; ++row)
		{
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col)
			{
				blocks.emplace_back(std::make_shared<Block>(sf::Color::Blue, sf::Vector2f(
					BLOCK_SPACING_HORIZONTAL + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SPACING_HORIZONTAL),
					100.f + row * (BLOCK_HEIGHT + BLOCK_SPACING_VERTICAL)), sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT)));
			}
		}
	}
}

