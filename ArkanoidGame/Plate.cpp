#include "Plate.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"
#include "Ball.h"
#include <algorithm>
#include <iostream>

namespace Arkanoid {
	
	void Plate::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "Plate.png"));
		texture.setSmooth(true);
		InitSprite(sprite, width, height, texture);
		sprite.setPosition(SCREEN_WIDTH / 2, YPosition);
		auto rect = sprite.getGlobalBounds();
		
	}
	
	void Plate::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setPosition(sprite.getPosition().x + speed, YPosition);
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setPosition(sprite.getPosition().x - speed, YPosition);
			
		}

		if (sprite.getGlobalBounds().left + width >= SCREEN_WIDTH)
		{
			sprite.setPosition(SCREEN_WIDTH-sprite.getGlobalBounds().width/2, YPosition);
		}
		else if (sprite.getGlobalBounds().left<= 0)
		{
			sprite.setPosition(sprite.getGlobalBounds().width/2, YPosition);
		}
	
	};
	void Plate::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	};
	
	bool Plate::CollisionWithBall(const Ball& ball)
	{
		
		auto sqr = [](float x) {
			return x * x;
			};
		
		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball.GetPosition();
		
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(ball.GetSize() / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(ball.GetSize() / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= ball.GetSize() / 2.0;

	}

}

