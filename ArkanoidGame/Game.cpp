#include "Game.h"
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include <assert.h>

namespace Arkanoid
{

	Game::Game()
	{
		recordsTable =
		{
			{"John", SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW / 2},
			{"Jane", SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW / 3 },
			{"Alice", SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW / 4 },
			{"Bob", SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW / 5 },
			{"Clementine", SETTINGS.BLOCKS_COUNT_ROWS*SETTINGS.BLOCKS_COUNT_IN_ROW / 5 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::Control(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().Control(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			while (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().Update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		while (stateStack.size() > 0)
		{
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}



	void Game::StartGame()
	{
		SwitchStateTo(GameStateType::Playing);
	}
	void Game::PauseGame()
	{
		PushState(GameStateType::ExitDialog, false);
	}
	void Game::ExitGame()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}
	void Game::ShowRecords()
	{
		PushState(GameStateType::Records, true);
	}
	void Game::QuitGame() {
		SwitchStateTo(GameStateType::None);
	}
	void Game::WinGame()
	{
		PushState(GameStateType::GameWin, false);
	}
	void Game::LooseGame()
	{
		PushState(GameStateType::GameOver, false);
	}
	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		Control(window);
		if (Update(SETTINGS.TIME_PER_FRAME))
		{
			window.clear();

			Draw(window);

			window.display();
		}
		else
		{
			window.close();
		}
	}
	void Game::LoadNextLevel()
	{
		assert(stateStack.back().GetType() == GameStateType::Playing);
		auto playingData = (stateStack.back().GetData<GameStatePlaying>());
		playingData->LoadNextLevel();
	}
}
