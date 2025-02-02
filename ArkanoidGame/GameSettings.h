#pragma once
#include <string>

namespace Arkanoid
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;

	const int BLOCKS_COUNT_ROWS = 4;
	const int BLOCKS_COUNT_IN_ROW = 12;
	
	const int WIN_SCORE = BLOCKS_COUNT_ROWS*BLOCKS_COUNT_IN_ROW;
	const float TIME_PER_FRAME = 1.f / 60.f;
	
	const float BLOCK_SPACING_HORIZONTAL = 5.f;
	const float BLOCK_SPACING_VERTICAL = 5.f;
	const float BLOCK_WIDTH = (SCREEN_WIDTH - BLOCKS_COUNT_IN_ROW * BLOCK_SPACING_HORIZONTAL) / BLOCKS_COUNT_IN_ROW;
	const float BLOCK_HEIGHT = 50.f;
	const float BREAK_DELAY = 1.5f;
	const int CRUMBLING_HEALTH = 3;
	
	const float BALL_SIZE = 50.f;
	const float BALL_SPEED = 500.f;
	
	const float PLATE_WIDTH = 200.f;
	const float PLATE_HEIGHT = 50.f;
	const float PLATE_SPEED = 10.0f;
	
	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME;

	const std::string GAME_NAME = "Arkanoid";
}
