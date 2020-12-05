#pragma once
#include "GameObjects.h"
#include "Storage.h"


String ch(int i)
{
	char c = static_cast<char>(i);
	char s[2];
	s[0] = c;
	s[1] = '\0';
	return String(s);
}

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
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();

			if (gameObject.name == "NULL")
				break;
			
			if (gameObject.name.len() != 9)
				continue;

			String name("", 9);

			for (int i = 0; i < 8; i++)
				name += gameObject.name[i];
			name[8] = '\0';

			if (name != "fairBall")
				continue;

			Iterator iter1(storage);
			while (true)
			{
				GameObject& gObj = iter1.stepIteration();
				if (gObj.name == "NULL")
					break;
				
				bool collide = this->fairBallIsCollide(gameObject, gObj);
				if (collide)
				{
					this->explosionFairBall(gameObject, gObj);
					if (!(this->checkIsLive(gObj)))
						this->destructionObject(gObj);
				}
			}
		}
	}

	void createFairBall()
	{
		if (iter = 256)
			iter = 0;

		String name = String("fairBall") + ch(iter);
		iter += 1;

		Vector2f position;
		GameObject& player = (*storage)["Player"];
		if (player.getOrientation() == "left")
			position = player.position + Vector2f(-18, 8);
		if (player.getOrientation() == "right")
			position = player.position + Vector2f(34, 8);
		assert((player.getOrientation() != "left") && (player.getOrientation() == "right"));

		Vector2f vertexs[4] = { Vector2f(0, 0), Vector2f(0, 16), Vector2f(16, 16), Vector2f(16, 0) };

		StdGameObject* fairBall = new StdGameObject (name, position, sprite, vertexs, 4, player.getOrientation(), Vector2f(16, 16), Vector2f(8, 8), -1);

		Vector2f mousePosition = sf::Mouse::getPosition();
		Vector2f velosity = -50 * (position + Vector2f(8, 8) - mousePosition).norm();

		fairBall->setVelosity(velosity);
		storage->AddObject(fairBall);
	}

	bool fairBallIsCollide(GameObject& fairBall, GameObject& gm)
	{
		Vector2f v = fairBall.isCollide(gm);
		return v.mod();
	}

	void explosionFairBall(GameObject& fairBall, GameObject& gm)
	{
		gm.getDamage(3);
		storage->DeleteObject(fairBall.name);
	}

	bool checkIsLive(GameObject& gm)
	{
		std::cout << gm.getHitPoints() << '\n';
		return gm.getHitPoints();
	}

	void destructionObject(GameObject gm)
	{
		storage->DeleteObject(gm.name);
	}
};