#pragma once
#include "SFML/Graphics.hpp"


class Clock
{
	sf::Clock clock;
	float time1;
	float time2;
public:
	Clock()
	{
		time1 = clock.getElapsedTime().asSeconds();
		time2 = clock.getElapsedTime().asSeconds();
	}

	float getDefTime()
	{
		time1 = clock.getElapsedTime().asSeconds();
		float dt = time1 - time2;
		time2 = time1;
		return dt;
	}
};
