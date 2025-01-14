#pragma once
#include "Object.h"
#include "vector"

namespace Arkanoid {
	class Ball;
	class Block : public Object
	{
	public:
		Block(sf::Color color, sf::Vector2f position, sf::Vector2f size);
		virtual ~Block()override = default ;
		void Init() override;
		virtual void Update(float timeDelta) override;
		bool Destroyed();
		
		virtual bool Collision( const Object& object) const;
	};

}