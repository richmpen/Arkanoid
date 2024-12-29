#include "Ball.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"
#include "Object.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Plate.h"


namespace Arkanoid {

	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "Ball.png"));
		texture.setSmooth(true);
		InitSprite(sprite, size, size, texture);
		const float angle = 225.f + rand() % 90;
		const auto pi = std::acos(-1.f);
		dir.x = std::cos(pi / 180.f * angle);
		dir.y = std::sin(pi / 180.f * angle);
		
	}
	void Ball::Update(float timeDelta, Plate& plate)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameStart = true;
		}
		
		if (gameStart) {
			CalculatingTrajectory(timeDelta);
		}
		else {
			sprite.setPosition(plate.GetPosition().x, plate.GetPosition().y - 75.f);

		}
		
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void Ball::CalculatingTrajectory(float timeDelta)
	{
		auto position = sprite.getPosition() + speed * timeDelta * dir;
		sprite.setPosition(position);
		if (position.x-size/2 <= 0 || position.x+size/2 >= SCREEN_WIDTH) {
			Turning(Turn::X);
			
		}

		if (position.y-size/2 <= 0) {
			Turning(Turn::Y);
			
		}
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
}