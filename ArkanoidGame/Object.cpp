#include "Object.h"
#include "Sprite.h"
#include "SFML/Graphics.hpp"

namespace Arkanoid {

	

	void Object::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}
