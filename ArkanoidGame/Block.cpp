#include "Block.h"
#include "Ball.h"
#include "Sprite.h"
#include "Object.h"
#include <algorithm>
#include <iostream>
#include <assert.h>

namespace Arkanoid {


	Block::Block(sf::Color color, sf::Vector2f position, sf::Vector2f size)
		:Object(TEXTURES_PATH + "Plate.png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "Plate.png"));
		texture.setSmooth(true);
	}

	void Block::Update(float timeDelta)
	{
		
	}

	bool Block::Collision(const Object& object) const
	{
		return GetRect().intersects(object.GetRect());
	}
}
