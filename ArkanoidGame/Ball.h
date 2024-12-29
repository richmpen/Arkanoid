#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Plate.h"

namespace Arkanoid {
	
	class Plate;

	enum class Turn {
		X,
		Y,
		Both
	};

	class Ball : public Object {
	public:

		void Init();
		void Update(float timeDelta, Plate& plate);
		void Draw(sf::RenderWindow& window);
		void CalculatingTrajectory(float timeDelta);
		auto GetSize() const { return size; }
		void Turning(Turn directions);
		

	private:
		bool gameStart = false;
		float size = 50.f;
		float speed = 500.0f;
		sf::Vector2f dir;
	};
}