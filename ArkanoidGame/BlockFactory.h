#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
namespace Arkanoid
{
    class Block;
    
    class BlockFactory
    {
        protected:
            int createdBreackableBlocksCount = 0;
        public:
            virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
            virtual ~BlockFactory() = default;
            int GetcreatedBreackableBlocksCount();
            void CleatCounter();
    };

    class SimpleBlockFactory final : public BlockFactory
    {
        public:
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
        ~SimpleBlockFactory() = default;
    };

    class ThreeHitBlockFactory final : public BlockFactory
    {
        public:
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
        ~ThreeHitBlockFactory() = default;
    };

    class UnbreackableBlockFactory final : public BlockFactory
    {
        public:
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
        ~UnbreackableBlockFactory() = default;
    };
    
}
