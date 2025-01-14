#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"


namespace Arkanoid {
	
	class Plate;

	enum class Turn {
		X,
		Y,
		Both
	};

	class Ball : public Object
	{
	public:
		Ball(const sf::Vector2f& position);
		virtual ~Ball();
		void Update(float timeDelta) override;
		void CalculatingTrajectory(float timeDelta);
		void Turning(Turn directions);
		void ChangeAngle(float angle);
		void SetPositionOnPlate(const sf::Vector2f positionPlate);
		
	private:
		sf::Vector2f dir;
		float lastAngle = 90;
	};
}