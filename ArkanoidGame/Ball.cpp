#include "Ball.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Plate.h"


namespace Arkanoid {
	Ball::Ball(const sf::Vector2f& position) :
	Object(TEXTURES_PATH + "Ball.png",position,BALL_SIZE,BALL_SIZE)
	{
		texture.setSmooth(true);
		const float angle = 225.f + rand() % 90;
		const auto pi = std::acos(-1.f);
		dir.x = std::cos(pi / 180.f * angle);
		
		dir.y = std::sin(pi / 180.f * angle);
	}

	Ball::~Ball()
	{
	}
	
	void Ball::Update(float timeDelta)
	{
		
	}

	void Ball::CalculatingTrajectory(float timeDelta)
	{
		auto position = sprite.getPosition() + BALL_SPEED * timeDelta * dir;
		
		position.x = std::max(BALL_SIZE/2.f, std::min(position.x, SCREEN_WIDTH - BALL_SIZE/2.f));
		position.y = std::max(BALL_SIZE/2.f, position.y);
    
		sprite.setPosition(position);
    
		if (position.x - BALL_SIZE/2 <= 0 || position.x + BALL_SIZE/2 >= SCREEN_WIDTH) {
			Turning(Turn::X);
		}

		if (position.y - BALL_SIZE/2 <= 0) {
			Turning(Turn::Y);
		}
	}
	
	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		const auto pi = std::acos(-1.f);
		dir.x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		dir.y = -1 * abs(std::sin(pi / 180.f * angle));
	}
	
	void Ball::Turning(Turn directions)
	{
		switch (directions) {
		case Turn::X:
			dir.x *= -1;
			break;
		case Turn::Y:
			dir.y *= -1;
			break;
		case Turn::Both:
			dir.x *= -1;
			dir.y *= -1;
			break;
		}
	}
	
	void Ball::SetPositionOnPlate(const sf::Vector2f positionPlate) 
	{
		sprite.setPosition(sf::Vector2f(positionPlate.x, positionPlate.y));
	}
}
