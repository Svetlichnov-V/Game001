#pragma once
#include "SFML/Graphics.hpp"
#include "GameObjects.h"
#include "Storage.h"
#include "String.h"
#include "Vector2f.h"
#include "Logic.h"
#include "Manager.h"
#include "Interface.h"
#include "Buns.h"



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


	Interface interFace(&camera, &logic);


	Physics_constants physics(Vector2f(0, 10));
	Manager manager(&storage, &camera, &physics);


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
	paints[0] = "Textures/Player/stand/stand.png";
	//paints[0] = "036.png"

	String paintsAnimCreatingFBleft[3];
	paintsAnimCreatingFBleft[0] = "Textures/Player/creatingFBleft/0.png";
	paintsAnimCreatingFBleft[1] = "Textures/Player/creatingFBleft/1.png";
	paintsAnimCreatingFBleft[2] = "Textures/Player/creatingFBleft/2.png";

	String paintsAnimCreatingFBright[3];
	paintsAnimCreatingFBright[0] = "Textures/Player/creatingFBright/0.png";
	paintsAnimCreatingFBright[1] = "Textures/Player/creatingFBright/1.png";
	paintsAnimCreatingFBright[2] = "Textures/Player/creatingFBright/2.png";

	StorageImages stIm[3];
	stIm[0] = StorageImages("Stand", 1, paints);
	stIm[1] = StorageImages("left_creating_FB", 3, paintsAnimCreatingFBleft);
	stIm[2] = StorageImages("right_creating_FB", 3, paintsAnimCreatingFBright);


	Sprite sp(stIm, 3);

	Vector2f vertex[16]{ Vector2f(0,  0),  Vector2f(0,  16), Vector2f(0,  32), Vector2f(0,  48),
						   Vector2f(0,  64), Vector2f(8,  64), Vector2f(16, 64), Vector2f(24, 64),
						   Vector2f(32, 64), Vector2f(32, 48), Vector2f(32, 32), Vector2f(32, 16),
						   Vector2f(32, 0),  Vector2f(24, 0),  Vector2f(16, 0),  Vector2f(8,   0) };

	Player Elve("Player", Vector2f(415, 587), &sp, vertex, 16, "Stand", Vector2f(32, 64), Vector2f(16, 32), 1);

	Elve.setVelosity(Vector2f(30, 0));

	storage.AddObject(&Elve);




	String paints1[1];
	paints1[0] = "036.png";

	StorageImages stImKnife("Test paint", 1, paints1);

	Sprite spKnife(&stImKnife, 1);

	Knight knight0("knight0", Vector2f(100, 500), &spKnife, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight1("knight1", Vector2f(200, 100), &spKnife, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight2("knight2", Vector2f(300, 800), &spKnife, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	Knight knight3("knight3", Vector2f(400, 900), &spKnife, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);

	storage.AddObject(&knight0);
	storage.AddObject(&knight1);
	storage.AddObject(&knight2);
	storage.AddObject(&knight3);


	String namesPaintsCube[1];
	namesPaintsCube[0] = "Cube.png";

	StorageImages stImCube("Cube Images", 1, namesPaintsCube);

	Sprite spCube(&stImCube, 1);

	Vector2f vertexCube[4]{ Vector2f(0,  0) , Vector2f(0,  32),  Vector2f(32, 32), Vector2f(32, 0) };

	StationaryGameObject cube0("Cube1", Vector2f(539, 687) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube1("Cube2", Vector2f(600, 800) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube2("Cube3", Vector2f(1200, 700), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube3("Cube4", Vector2f(1800, 500), &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube4("Cube5", Vector2f(800, 900) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube5("Cube6", Vector2f(700, 950) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube6("Cube7", Vector2f(650, 650) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);
	StationaryGameObject cube7("Cube8", Vector2f(200, 800) , &spCube, vertexCube, 4, "Cube Images", Vector2f(32, 32), Vector2f(16, 16), 100000);

	storage.AddObject(&cube0);
	storage.AddObject(&cube1);
	storage.AddObject(&cube2);
	storage.AddObject(&cube3);
	storage.AddObject(&cube4);
	storage.AddObject(&cube6);
	storage.AddObject(&cube5);
	storage.AddObject(&cube7);

	Vector2f g(0, 10);

	Clock clock;
	float dt;

	while (camera.isOpen())
	{
		dt = clock.getDefTime();

		manager.draw(dt);
		manager.physics(dt);

		interFace.work();

		logic.work();
	};

	return 0;
}