#include "Plate.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "Object.h"
#include "Ball.h"


namespace Arkanoid {

	Plate::Plate(const sf::Vector2f& position):Object(TEXTURES_PATH + "Plate.png",position,PLATE_WIDTH,PLATE_HEIGHT)
	{
		texture.setSmooth(true);
		sprite.setPosition(position);
	}
	

	void Plate::Update(float timeDelta) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setPosition(sprite.getPosition().x + PLATE_SPEED, YPosition);
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setPosition(sprite.getPosition().x - PLATE_SPEED, YPosition);
			
		}

		if (sprite.getGlobalBounds().left + PLATE_WIDTH >= SCREEN_WIDTH)
		{
			sprite.setPosition(SCREEN_WIDTH-sprite.getGlobalBounds().width/2, YPosition);
		}
		else if (sprite.getGlobalBounds().left<= 0)
		{
			sprite.setPosition(sprite.getGlobalBounds().width/2, YPosition);
		}
	
	};

	bool Plate::CheckCollisionWithBall(const Ball& ball) const
	{
		auto sqr = [](float x) {
			return x * x;
			};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball.GetPosition();
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}

}

