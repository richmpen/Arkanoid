#include "BlockFactory.h"
#include "Block.h"


namespace Arkanoid
{
    int BlockFactory::GetcreatedBreackableBlocksCount()
    {
        return createdBreackableBlocksCount;
    }

    void BlockFactory::CleatCounter()
    {
        createdBreackableBlocksCount = 0;
    }

    std::shared_ptr<Block> SimpleBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        ++createdBreackableBlocksCount;
        return std::make_shared<SmoothDestroyableBlock>("SmoothDestroyableBlock.png", position, sf::Color::White);
    }

    std::shared_ptr<Block> UnbreackableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        ++createdBreackableBlocksCount;
        return std::make_shared<UnbreackableBlock>("UnbreackableBlock.png",position);
    }

    std::shared_ptr<Block> ThreeHitBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        ++createdBreackableBlocksCount;
        return std::make_shared<ThreeHitBlock>("CrumblingBlock1.png",position);
    }

}