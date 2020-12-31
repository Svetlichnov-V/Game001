#pragma once
#include <iostream>
#include "Storage.h"


class Physics_constants
{
	Vector2f g;
public:
	Physics_constants() :g(Vector2f(0, 10)) {}
	Physics_constants(Vector2f g) :g(g) {}
	Vector2f getG() { return g; }
	void setG(Vector2f g) { this->g = g; }
};

class Manager
{
	Camera* camera;
	Storage* storage;
	Physics_constants* physics_constants;

public:

	Manager(Storage* st, Camera* cm, Physics_constants* ph) :
		storage(st),
		camera(cm),
		physics_constants(ph)
	{}

	void draw(float dt)
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
			{
				break;
			}
			gameObject.draw(camera);
			gameObject.animation(dt);
		}
		camera->display();
	}

	void physics(float dt)
	{
		this->nullChangeImpulse();
		this->gravitation(dt, physics_constants->getG());
		this->collision();
		this->moveAndChangeVelosity(dt);
	}

private:

	void nullChangeImpulse()
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.nullChangeImpulse();
		}
	}

	void gravitation(float dt, Vector2f g)
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.gravitation(g, dt);
		}
	}

	void collision()
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
				break;
			Iterator iter1(storage);
			while (true)
			{
				GameObject& gObj = iter1.stepIteration();
				if (gObj.name == "NULL")
					break;
				Vector2f v = gameObject.isCollide(gObj);
				gameObject.resolutionCollision(gObj, v);
			}
		}
	}

	void moveAndChangeVelosity(float dt)
	{
		Iterator iter(storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.move(dt);
			gameObject.changeVelosity();
		}
	}
};