#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "Plate.h"
#include "Object.h"

namespace Arkanoid
{
	void GameStatePlaying::Init()
	{	
		assert(font.loadFromFile(FONTS_PATH + "Alata-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		assert(backgroundTexture.loadFromFile(TEXTURES_PATH + "BackgroudnGameScene.png"));
		
		InitSprite(backgroundSprite, backgroundWidth,backgroundHeight, backgroundTexture);
		backgroundSprite.setPosition(0,0);
		
		plate.Init();
		ball.Init();

		score = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(32);
		scoreText.setFillColor(sf::Color::Blue);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(32);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Press SPACE to Play \n ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
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
		
		BackgroundMove(timeDelta);
		
		plate.Update(timeDelta);
		ball.Update(timeDelta, plate);

		const bool isCollision = plate.CollisionWithBall(ball);
		if (isCollision) {
			ball.Turning(Turn::Y);
			score +=10;
		}

		const bool isGameFinished = !isCollision && ball.GetPosition().y > plate.GetRect().top;

		if (isGameFinished)
		{
			gameOverSound.play();

			Game& game = Application::Instance().GetGame();
			game.UpdateRecord(PLAYER_NAME, score);
			game.PushState(GameStateType::GameOver, false);
		}

		scoreText.setString("Score: " + std::to_string(score));
	}
	
	void GameStatePlaying::Draw(sf::RenderWindow& window)
	{
		window.draw(backgroundSprite);
		plate.Draw(window);
		ball.Draw(window);
		
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

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

}

