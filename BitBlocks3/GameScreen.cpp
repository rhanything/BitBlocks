#include "GameScreen.h"
#include <iostream>

/*GameScreenClass*/

	GameScreen::GameScreen(int sizex, int sizey, int stage)
	{
		sizeX = sizex;
		sizeY = sizey;

		/* Screen GameOver */
		if (!fontText->loadFromFile("arial.ttf"))
			std::cout << "ERRO FONTE" << std::endl;
		gameOverText = sf::Text("GAME OVER!", *fontText, 90);
		gameOverText.setColor(sf::Color(255, 255, 255));
		gameOverText.setPosition(sf::Vector2f(400, 400));
		/*FIM*/

		/*Screen GameStage*/
		gameStageText = sf::Text("Stage: " + std::to_string(stage), *fontText, 30);
		gameStageText.setColor(sf::Color(255, 255, 255));
		gameStageText.setPosition(sf::Vector2f(100, 300));
		/*FIM*/

	}

	void GameScreen::GameOverScreen()
	{
		gameOverText = sf::Text("GAME OVER!\n Press SpaceBar", *fontText, 90);
		window.draw(gameOverText);



	}

	void GameScreen::GameStageScreen(int stage)
	{
		gameStageText = sf::Text("Stage: " + std::to_string(stage), *fontText, 30);
		window.draw(gameStageText);
	}


	void GameScreen::Initialize()
	{
		/*Cria janela*/
		window.create(sf::VideoMode(sizeX, sizeY), "BitBlocks", sf::Style::Titlebar | sf::Style::Close);

		/*Seta posição da janela*/
		window.setPosition(sf::Vector2i(window.getPosition().x, 0));


	}
/*FIM*/