#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

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
			data = new GameStateMainMenu();
			((GameStateMainMenu*)data)->Init();
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlaying();
			((GameStatePlaying*)data)->Init();
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOver();
			((GameStateGameOver*)data)->Init();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenu();
			((GameStatePauseMenu*)data)->Init();
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecords();
			((GameStateRecords*)data)->Init();
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	GameState::~GameState()
	{
		if (data) {
			switch (type)
			{
			case GameStateType::MainMenu:
			{
				delete ((GameStateMainMenu*)data);
				break;
			}
			case GameStateType::Playing:
			{
				delete ((GameStatePlaying*)data);
				break;
			}
			case GameStateType::GameOver:
			{
				delete ((GameStateGameOver*)data);
				break;
			}
			case GameStateType::ExitDialog:
			{
				delete ((GameStatePauseMenu*)data);
				break;
			}
			case GameStateType::Records:
			{
				delete ((GameStateRecords*)data);
				break;
			}
			default:
				assert(false);
				break;
			}
 			
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenu*)data)->Update(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlaying*)data)->Update(timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOver*)data)->Update(timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenu*)data)->Update(timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecords*)data)->Update(timeDelta);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenu*)data)->Draw(window);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlaying*)data)->Draw(window);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOver*)data)->Draw(window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenu*)data)->Draw(window);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecords*)data)->Draw(window);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void GameState::Control(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			((GameStateMainMenu*)data)->Control(event);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlaying*)data)->Control(event);
			break;
		}
		case GameStateType::GameOver:
		{
			((GameStateGameOver*)data)->Control(event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			((GameStatePauseMenu*)data)->Control(event);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecords*)data)->Control(event);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void* GameState::CopyData(const GameState& state) const
	{
		void* data = nullptr;
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenu();
			*((GameStateMainMenu*)data) = *(GameStateMainMenu*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlaying();
			*((GameStatePlaying*)data) = *(GameStatePlaying*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOver();
			*((GameStateGameOver*)data) = *(GameStateGameOver*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenu();
			*((GameStatePauseMenu*)data) = *(GameStatePauseMenu*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecords();
			*((GameStateRecords*)data) = *(GameStateRecords*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}
		return data;
	}
}