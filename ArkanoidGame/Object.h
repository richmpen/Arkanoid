#pragma once
#include "SFML/Graphics.hpp"

namespace Arkanoid {

	class Object {
	public:
		const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
		const sf::FloatRect& GetRect() const { return sprite.getGlobalBounds(); }

		void Draw(sf::RenderWindow& window);

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}