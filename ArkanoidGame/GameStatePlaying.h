#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Plate.h"
#include "Ball.h"


namespace Arkanoid
{
	class Game;

	class GameStatePlaying
	{
	public:

		void Init();
		void Shutdown();
		void Control(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void BackgroundMove(float timeDelta);
	private:

		sf::Texture backgroundTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;


		Plate plate;
		Ball ball;
		sf::Sprite apple;
		std::vector<sf::Sprite> rocks;
		int score = 0;


		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Sprite backgroundSprite;
		float backgroundSpeed = 30.f;
		float backgroundWidth = 7334.f;
		float backgroundHeight = 2200.f;
		bool bgMoveRight = true;



		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};

	
}
