#include "Plate.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "Object.h"
#include "Ball.h"


namespace Arkanoid {

	Plate::Plate(const sf::Vector2f& position):Object(SETTINGS.TEXTURES_PATH + "Plate.png",position,SETTINGS.PLATE_WIDTH,SETTINGS.PLATE_HEIGHT)
	{
		texture.setSmooth(true);
		sprite.setPosition(position);
	}
	

	void Plate::Update(float timeDelta) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setPosition(sprite.getPosition().x + SETTINGS.PLATE_SPEED, YPosition);
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setPosition(sprite.getPosition().x - SETTINGS.PLATE_SPEED, YPosition);
			
		}

		if (sprite.getGlobalBounds().left + SETTINGS.PLATE_WIDTH >= SETTINGS.SCREEN_WIDTH)
		{
			sprite.setPosition(SETTINGS.SCREEN_WIDTH-sprite.getGlobalBounds().width/2, YPosition);
		}
		else if (sprite.getGlobalBounds().left<= 0)
		{
			sprite.setPosition(sprite.getGlobalBounds().width/2, YPosition);
		}
	
	};

	bool Plate::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		if (!ball) return false;
		auto sqr = [](float x) {
			return x * x;
		};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->GetPosition();
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.0;
	}

	bool Plate::CheckCollision(std::shared_ptr<Colladiable> collidable)
	{
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		if (!ball) return false;
		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosOnPlate = (ball->GetPosition().x - (rect.left + rect.width / 2.0)) / rect.width;
			ball->ChangeAngle(90-20*ballPosOnPlate);
			return true;
		}
		return false;
	}

	void Plate::OnHit()
	{
	}
}


