#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Object.h"
#include <array>

#include "Colladiable.h"


namespace Arkanoid
{
	class Ball;

	class Plate : public Object
	{
		public:
		
		Plate(const sf::Vector2f& position);
		~Plate() =default;
		void Update(float timeDelta)override;
		bool CheckCollisionWithBall(const Ball& ball) const;

		private:
		float YPosition = SCREEN_HEIGHT - PLATE_HEIGHT / 2;
	};
}
