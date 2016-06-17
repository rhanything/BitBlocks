#include "Timer.h"

void Timer::Start()
{
	timer = new sf::Clock();
}

void Timer::Restart()
{
	timer->restart();
}

void Timer::IntervalFunction( float score) //função a cada intervalo do timer
{
	sf::Int32  mili = GetElapsedTime().asMilliseconds();
	
	if (mili >= timeInterval)
	{
		if (!fontTimes->loadFromFile("arial.ttf"))
			std::cout << "ERRO FONTE" << std::endl;
		scoreText = sf::Text("Score: " + std::to_string(score), *fontTimes, 30);
		scoreText.setColor(sf::Color(255, 255, 255));
		scoreText.setPosition(sf::Vector2f(627, 5));
		Restart();
	}
}

void Timer::SetTimeInterval(int param)
{
	timeInterval = param;
}

sf::Time Timer::GetElapsedTime()
{
	sf::Time t;
	t = timer->getElapsedTime();
	return t;
}

void Timer::Stop()
{
	free(timer);
}

