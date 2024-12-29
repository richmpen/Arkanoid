#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Object.h"
#include <array>


namespace Arkanoid
{
	class Ball;

	class Plate : public Object
	{
		public:
		
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		bool CollisionWithBall(const Ball& ball);

		

		private:
		
		float width = 200.f;
		float height = 50.f;
		float speed = 10.0f;
		float YPosition = SCREEN_HEIGHT-100.f;
	};
}
