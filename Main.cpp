#pragma once
#include "SFML/Graphics.hpp"
#include "GameObjects.h"
#include "Storage.h"
#include "String.h"
#include "Vector2f.h"
#include "Logic.h"
#include "Manager.h"

void handlingEvent(Camera* camera)
{
	sf::Event event;
	while (camera->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			camera->close();
	}
}

int main()
{
	Storage storage;

	Camera camera("My game", Vector2f(0, 0));
	storage.AddObject(&camera);
	camera.setFrameralLimit(60);


	String paintsFairBalls[1];
	paintsFairBalls[0] = "fairBall.png";

	StorageImages stImFB[2]{ StorageImages("left", 1, paintsFairBalls), StorageImages("right", 1, paintsFairBalls) };

	Sprite spFB(stImFB, 2);

	Logic logic(&storage, &camera, &spFB);


	
	Vector2f downWallVertexs[4];
	downWallVertexs[0] = Vector2f(0, 0);
	downWallVertexs[1] = Vector2f(0, 400);
	downWallVertexs[2] = Vector2f(1980, 400);
	downWallVertexs[3] = Vector2f(1980, 0);
	Wall downWall("downWall", Vector2f(0, 1080), downWallVertexs, 4, Vector2f(1980, 0), 10000);
	storage.AddObject(&downWall);

	Vector2f upWallVertexs[4];
	upWallVertexs[0] = Vector2f(0, 0);
	upWallVertexs[1] = Vector2f(1980, 0);
	upWallVertexs[2] = Vector2f(1980, 400);
	upWallVertexs[3] = Vector2f(0, 400);
	Wall upWall("upWall", Vector2f(0, 0), upWallVertexs, 4, Vector2f(1980, 0), 10000);
	storage.AddObject(&upWall);

	Vector2f leftWallVertexs[4];
	leftWallVertexs[0] = Vector2f(0, 0);
	leftWallVertexs[1] = Vector2f(-400, 0);
	leftWallVertexs[2] = Vector2f(-400, 1080);
	leftWallVertexs[3] = Vector2f(0, 1080);
	Wall leftWall("leftWall", Vector2f(0, 0), leftWallVertexs, 4, Vector2f(0, 1080), 10000);
	storage.AddObject(&leftWall);

	Vector2f rightWallVertexs[4];
	rightWallVertexs[0] = Vector2f(0, 0);
	rightWallVertexs[1] = Vector2f(0, 1080);
	rightWallVertexs[2] = Vector2f(400, 1080);
	rightWallVertexs[3] = Vector2f(400, 0);
	Wall rightWall("rightWall", Vector2f(1980, 0), rightWallVertexs, 4, Vector2f(0, 1080), 10000);
	storage.AddObject(&rightWall);
	


	String paints[1];
	paints[0] = "036.png";

	StorageImages stIm("Test paint", 1, paints);

	Sprite sp(&stIm, 1);

	Vector2f vertex[16]{   Vector2f(0,  0),  Vector2f(0,  16), Vector2f(0,  32), Vector2f(0,  48),
						   Vector2f(0,  64), Vector2f(8,  64), Vector2f(16, 64), Vector2f(24, 64),
						   Vector2f(32, 64), Vector2f(32, 48), Vector2f(32, 32), Vector2f(32, 16),
						   Vector2f(32, 0),  Vector2f(24, 0),  Vector2f(16, 0),  Vector2f(8,   0) };

	Player Elve ("Player",  Vector2f(415, 587), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);

	Elve.setVelosity(Vector2f(30, 0));

	storage.AddObject(&Elve);


	Knight knight0("knight0", Vector2f(100, 500), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight1("knight1", Vector2f(200, 100), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight2("knight2", Vector2f(300, 800), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight3("knight3", Vector2f(400, 900), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	
	storage.AddObject(&knight0);
	storage.AddObject(&knight1);
	storage.AddObject(&knight2);
	storage.AddObject(&knight3);


	String namesPaintsCube[1];
	namesPaintsCube[0] = "Cube.png";

	StorageImages stImCube("Cube Images", 1, namesPaintsCube);

	Sprite spCube(&stImCube, 1);

	Vector2f vertexCube[4]{  Vector2f(0,  0) , Vector2f(0,  32),  Vector2f (32, 32), Vector2f(32, 0)};

	StationaryCube cube0("Cube1", Vector2f(539, 687), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube1("Cube2", Vector2f(600, 800), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube2("Cube3", Vector2f(1200, 700), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube3("Cube4", Vector2f(1800, 500), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube4("Cube5", Vector2f(800, 900), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube5("Cube6", Vector2f(700, 950), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube6("Cube7", Vector2f(650, 650), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryCube cube7("Cube8", Vector2f(200, 800), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);

	storage.AddObject(&cube0);
	storage.AddObject(&cube1);
	storage.AddObject(&cube2);
	storage.AddObject(&cube3);
	storage.AddObject(&cube4);
	storage.AddObject(&cube6);
	storage.AddObject(&cube5);
	storage.AddObject(&cube7);
	
	Vector2f g (0, 10);

	sf::Clock clock;
	int time = clock.getElapsedTime().asMilliseconds() + 400;
	srand(time);

	float time1 = clock.getElapsedTime().asSeconds();
	float time2 = clock.getElapsedTime().asSeconds();

	float dt;

	int i = 0;

	while (camera.isOpen())
	{
		time1 = clock.getElapsedTime().asSeconds();
		dt = time1 - time2;
		time2 = time1;

		handlingEvent(&camera);

		drawManager(&camera, &storage, dt);
		//camera.display();

		Iterator iter5(&storage);
		while (true)
		{
			GameObject& gameObject = iter5.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.nullChangeImpulse();
		}

		Iterator iter3(&storage);
		while (true)
		{
			GameObject& gameObject = iter3.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.gravitation(g, dt);
		}

		Iterator iter2(&storage);
		while (true)
		{
			GameObject& gameObject = iter2.stepIteration();
			if (gameObject.name == "NULL")
				break;
			Iterator iter1(&storage);
			while (true)
			{
				GameObject& gObj = iter1.stepIteration();
				if (gObj.name == "NULL")
					break;
				Vector2f v = gameObject.isCollide(gObj);
				gameObject.resolutionCollision(gObj, v);
			}
		}

		Iterator iter4(&storage);
		while(true)
		{
			GameObject& gameObject = iter4.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.move(dt);
			gameObject.changeVelosity();
		}

		camera.display();

		if (i == 200)
		{
			i = 0;
			logic.createFairBall();
		}
		logic.work();
		i++;
	};
	
	return 0;
}


//window.setFramerateLimit(60);

/*
int main()
{
	String str("hyj");
	String s = ch(2);
	std::cout << s << ' ' << s.len() << '\n';
	str += s;
	std::cout << str << ' ' << str.len() << '\n';
}*/
