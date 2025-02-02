#pragma once
#include <queue>
#include <set>

#include "Colladiable.h"
#include "Object.h"
#include "IDelayedAction.h"

namespace Arkanoid {
	class Ball;
	class Block : public Object, public Colladiable
	{
	protected:	
		void OnHit() override;
		int hitcount = 1;
		sf::Texture texture;
	public:
		Block(const std::string& texturePath,sf::Vector2f position);
		virtual ~Block();
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		bool isDestroyed();
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
		protected:
		void OnHit() override;
		public:
		SmoothDestroyableBlock(const std::string& texturePath, sf::Vector2f position, sf::Color color);
		~SmoothDestroyableBlock() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
		private:
		sf::Color color = sf::Color::White;
	};

	class UnbreackableBlock : public Block
	{
		public:
		UnbreackableBlock(const std::string& texturePath, const sf::Vector2f& position);
		void OnHit() override;
		void Update(float timeDelta) override
		{
			int i = 0;
			++i;
		}
	};

	class CrumblingBlock : public Block
	{
		protected:
		void OnHit() override;
		public:
		
		CrumblingBlock(const std::string& texturePath, const sf::Vector2f& position);
		~CrumblingBlock() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		void SwitchBlockTexture();
		private:
		std::queue<sf::Texture> DestroyTextures;
		sf::Texture brokenTexture;
		sf::Texture lastBrokenTexture;
	};

	
}