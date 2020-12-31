#pragma once
#include "GameObjects.h"
#include "Storage.h"



class Logic;



class Timer : public GameObject
{
protected:
	float time;
	Logic* logic;
public:

	Timer(String name, Logic* lg, float t);

	void move(float dt);

	virtual void inTheEnd() = 0;
};

class TimerCreateFairBall : public Timer
{
public:
	TimerCreateFairBall(String name, Logic* lg, float t) :Timer(name, lg, t) {};

	void inTheEnd();
};



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
	int iter = 1;
	bool creatingFB = false;
	String process = "Stay";
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
		this->processingFairBalls();
		this->deleteObjects();
	}

	void processingFairBalls()
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();

			if (gameObject.name == "NULL")
				break;

			//std::cout << gameObject.getTypeName() << '\n';
			if (gameObject.getTypeName() != "FairBall")
				continue;

			Iterator iter1(storage);
			while (true)
			{
				GameObject& gObj = iter1.stepIteration();
				if (gObj.name == "NULL")
					break;

				if (gObj.name == gameObject.name)
					continue;

				bool collide = this->fairBallIsCollide(gameObject, gObj);
				if (collide)
				{
					this->explosionFairBall(gameObject, gObj);
				}
			}
		}
	}

	void deleteObjects()
	{
		Iterator iter1(storage);
		while (true)
		{
			GameObject& gObj = iter1.stepIteration();
			if (gObj.name == "NULL")
				break;

			if (!(this->checkIsLive(gObj)))
				this->destructionObject(gObj);
		}
	}

	void createFairBall()
	{
		creatingFB = false;

		if (iter == 256)
			iter = 1;

		String name = String("fairBall") + ch(iter);
		iter += 1;

		Vector2f position;

		GameObject& player = (*storage)["Player"];

		if (player.getOrientation() == "left")
			position = player.position + Vector2f(-18, 8);
		if (player.getOrientation() == "right")
			position = player.position + Vector2f(34, 8);

		player.changeTexture("Stand", 0);

		assert((player.getOrientation() == "left") || (player.getOrientation() == "right"));

		Vector2f vertexs[8] = { Vector2f(0, 0), Vector2f(0, 8), Vector2f(0, 16), Vector2f(8, 16),
								Vector2f(16, 16), Vector2f(16, 8), Vector2f(16, 0), Vector2f(8, 0) };

		FairBall* fairBall = new FairBall (name, position, sprite, vertexs, 8, player.getOrientation(), Vector2f(16, 16), Vector2f(8, 8), 1);

		Vector2f mousePosition = sf::Mouse::getPosition();
		Vector2f velosity = -120 * (position + Vector2f(8, 8) - mousePosition).norm();

		fairBall->setVelosity(velosity);
		storage->AddObject(fairBall);
	}

	bool fairBallIsCollide(GameObject& fb, GameObject& gm)
	{
		Vector2f v = fb.isCollide(gm);
		return v.mod();
	}

	void explosionFairBall(GameObject& fairBall, GameObject& gm)
	{
		gm.getDamage(3);
		storage->DeleteObject(fairBall.name);
	}

	bool checkIsLive(GameObject& gm)
	{
		return (gm.getHitPoints() > 0);
	}

	void destructionObject(GameObject& gm)
	{
		storage->DeleteObject(gm.name);
	}

	bool isCreatingFB()
	{
		return creatingFB;
	}

	void beginCreatingFB()
	{
		creatingFB = true;
		Vector2f mousePosition = sf::Mouse::getPosition();
		GameObject& player = (*storage)["Player"];
		Vector2f playerPosition = player.getPositionCenter();

		if ((mousePosition - playerPosition).x < 0)
		{
			player.setOrientation("left");
			player.changeTexture("left_creating_FB", 0);
		}

		if ((mousePosition - playerPosition).x >= 0)
		{
			player.setOrientation("right");
			player.changeTexture("right_creating_FB", 0);
		}

		TimerCreateFairBall* TCFB = new TimerCreateFairBall("TCFB", this, 0.15);
		storage->AddObject(TCFB);
	}

	void moveRight()
	{
		GameObject player = (*storage)["Player"];
		process = "moveRight";
		player.setVelosity(Vector2f(10, 0));
		player.setOrientation("right");
		player.changeTexture("move_right", 0);
	}

	void processingPlayer()
	{

	}
};



Timer::Timer(String name, Logic* lg, float t)
{
	time = t;
	logic = lg;
	this->name = name;
};

void Timer::move(float dt)
{
	time -= dt;
	if (time < 0)
	{
		this->inTheEnd();
		logic->destructionObject(*this);
	}
}

void TimerCreateFairBall::inTheEnd()
{
	logic->createFairBall();
}