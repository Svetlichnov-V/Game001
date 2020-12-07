#pragma once
#include "GameObjects.h"
#include "Storage.h"
#include "Logic.h"

class Interface
{
	Camera* camera;
	Logic* logic;
public:

	Interface(Camera* cm, Logic* lg) :logic(lg), camera(cm) {};

	void work()
	{
		sf::Event event;

		while (camera->pollEvent(event))
		{
			switch (event.type) 
			{
				case sf::Event::Closed:
					camera->close();

				case sf::Event::MouseButtonPressed:
				{
					if (!(logic->isCreatingFB()))
						logic->beginCreatingFB();
				}

			}
			//if (event.type == sf::Event::Closed)
			//	camera->close();

		}
	}
};
