#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateData.h"
#include "GameStateGameWin.h"
#include <assert.h>


namespace Arkanoid
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = std::make_unique<GameStateMainMenu>();
			break;
		}
		case GameStateType::Playing:
		{
			data = std::make_unique<GameStatePlaying>();
			break;
		}
		case GameStateType::GameOver:
		{
			data = std::make_unique<GameStateGameOver>();
			break;
		}
		case GameStateType::GameWin:
		{
			data = std::make_unique<GameStateGameWin>();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = std::make_unique<GameStatePauseMenu>();
			break;
		}
		case GameStateType::Records:
		{
			data = std::make_unique<GameStateRecords>();
			break;
		}
		default:
			assert(false);
			break;
		}
		if (data) {
			data->Init();
		}
	}


	GameState::~GameState()
	{
		if (data) {
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::Control(sf::Event& event)
	{
		data->Control(event);
	}

	
}