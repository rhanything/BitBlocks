#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class GameScreen
{
private:sf::Font * fontText = new sf::Font(); 
		sf::Text  gameOverText, gameStageText;
public: int sizeX, sizeY; //tamanho da gameScreen
        sf::RenderWindow window; //gameWindow
		GameScreen(int sizex, int sizey, int stage);
		void GameOverScreen();
		void GameStageScreen(int stage);
		void Initialize();

};

