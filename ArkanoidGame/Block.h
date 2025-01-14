#pragma once
#include "Object.h"

namespace Arkanoid {
	class Ball;
	class Block : public Object
	{
	public:
		Block(sf::Color color, sf::Vector2f position, sf::Vector2f size);
		~Block()override = default ;
		void Update(float timeDelta) override;
		bool CheckCollisionWithBall(const Ball& ball) const;
	};

}