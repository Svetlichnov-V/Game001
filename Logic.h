#pragma once
#include "GameObjects.h"
#include "Storage.h"

class Logic
{
	//StdGameObject* fairBalls;
	Camera* camera;
	Storage* storage;
	Sprite* sprite;
	int iter = 0;
public:
	Logic(Storage* st, Camera* cm, Sprite* sp):
		storage(st),
		camera(cm),
		sprite(sp)
	{}

	~Logic()
	{
		//delete[] fairBalls;
	}

	void work()
	{

	}

	void createFairBall()
	{
		String name = String("fairBall") + String(char(iter));

		//std::cout << name << '\n';

		Vector2f position;
		GameObject& player = (*storage)["Player"];
		if (player.getOrientation() == "left")
			position = player.position + Vector2f(-32, 8);
		if (player.getOrientation() == "right")
			position = player.position + Vector2f(32, 8);
		assert((player.getOrientation() != "left") && (player.getOrientation() == "right"));

		Vector2f vertexs[4] = { Vector2f(0, 0), Vector2f(0, 16), Vector2f(16, 16), Vector2f(16, 0) };

		//std::cout << 0 << '\n';
		StdGameObject* fairBall = new StdGameObject (name, position, sprite, vertexs, 4, player.getOrientation(), Vector2f(16, 16), Vector2f(8, 8), 1);

		Vector2f mousePosition = sf::Mouse::getPosition();
		Vector2f velosity = -50 * (position + Vector2f(8, 8) - mousePosition).norm();

		storage->AddObject(fairBall);
	}

	bool fairBallIsCollide(StdGameObject& fairBall)
	{
		Vector2f v(0, 0);

		Iterator iter(storage);
		while (true)
		{
			GameObject& gObj = iter.stepIteration();
			if (gObj.name == "NULL")
				break;
			v += fairBall.isCollide(gObj);
		}

		return v.mod();
	}

	void explosionFairBall(StdGameObject& fb, GameObject& gm)
	{
		gm.getDamage(3);
		storage->DeleteObject[fb.name];
	}
};