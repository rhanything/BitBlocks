#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "GameStatus.h"
class Timer
{
private:
	double timeInterval;
	sf::Font * fontTimes = new sf::Font();


public:
	sf::Clock * timer;
	sf::Text scoreText;
	sf::Time GetElapsedTime();
	void Start();
	void Restart();
	void Stop();
	void IntervalFunction(float score);
	void SetTimeInterval(int param);
};

