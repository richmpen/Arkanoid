#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace Arkanoid
{

	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min,
		Middle,
		Max
	};

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
}
