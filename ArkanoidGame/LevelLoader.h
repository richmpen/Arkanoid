#pragma once
#include "Block.h"
#include <vector>
#include <string>
#include <memory>
#include <map>


namespace Arkanoid {

	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreackable,
	};

	struct Level {
		std::vector<std::pair<sf::Vector2i,BlockType>> m_blocks;
	};

	class LevelLoader final
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();
	private:
		void LoadLevelsFromFile();

		std::vector<Level> levels;
		static BlockType CharToBlockType(char symbol);
	};

}

