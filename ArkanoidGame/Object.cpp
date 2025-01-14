#include "Object.h"
#include "Sprite.h"
#include <assert.h>
#include "SFML/Graphics.hpp"

namespace Arkanoid {
	Object::Object(const std::string& texturePath, const sf::Vector2f& position, float width, float height)
	{
		assert(texture.loadFromFile(texturePath));
		InitSprite(sprite,width,height,texture);
		sprite.setPosition(position);
	}

	void Object::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}
