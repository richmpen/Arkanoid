#include "Ball.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Plate.h"
#include <random>

namespace Arkanoid {
	Ball::Ball(const sf::Vector2f& position) :
	Object(SETTINGS.TEXTURES_PATH + "Ball.png",position,SETTINGS.BALL_SIZE,SETTINGS.BALL_SIZE)
	{
		texture.setSmooth(true);
		const float angle = 225.f + rand() % 90;
		const auto pi = std::acos(-1.f);
		dir.x = std::cos(pi / 180.f * angle);
		
		dir.y = std::sin(pi / 180.f * angle);
	}

	
	void Ball::Update(float timeDelta)
	{

		auto position = sprite.getPosition() + SETTINGS.BALL_SPEED * timeDelta * dir;

		position.x = std::max(SETTINGS.BALL_SIZE / 2.f, std::min(position.x, SETTINGS.SCREEN_WIDTH - SETTINGS.BALL_SIZE / 2.f));
		position.y = std::max(SETTINGS.BALL_SIZE / 2.f, position.y);

		sprite.setPosition(position);

		if (position.x - SETTINGS.BALL_SIZE / 2 <= 0 || position.x + SETTINGS.BALL_SIZE / 2 >= SETTINGS.SCREEN_WIDTH) {
			Turning(Turn::X);
		}

		if (position.y - SETTINGS.BALL_SIZE / 2 <= 0) {
			Turning(Turn::Y);
		}

		Emit();
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

	bool Ball::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<Object>(collidable);
		assert(gameObject != nullptr);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Ball::OnHit()
	{
		lastAngle += -5 + std::rand() % 11;
		ChangeAngle(lastAngle);
	}

	void Ball::restart()
	{
		Object::restart();
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		dir.x = std::cos(pi / 180.f * angle);
		dir.y = std::sin(pi / 180.f * angle);
	}
}
