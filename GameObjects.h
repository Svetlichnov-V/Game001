#pragma once
#include "Vector2f.h"
#include "String.h"


class Camera;
class GameObject;
class Sprite;
class StdGameObject;
class StorageImages;


float max(float a, float b);

float reducedMass(const float m1, const float m2);


class StorageImages
{
	String name;
	sf::Image* images;
	int numberOfImages;

public:

	StorageImages() 
	{
		images = new sf::Image[1];
		name = "NULL";
		numberOfImages = 0;
	}

	StorageImages(String name, int numberOfImages, String* namesOfFiles)
	{
		this->numberOfImages = numberOfImages;
		this->name = name;
		images = new sf::Image[numberOfImages];
		sf::Image image;
		for (int i = 0; i < numberOfImages; i++)
		{
			image.loadFromFile(namesOfFiles[i].c_str());                                     //!!!!!!!!
			sf::Vector2u size = image.getSize();
			int x = size.x;
			int y = size.y;
			images[i].create(x, y);
			images[i].copy(image, 0, 0);

			//sf::Color c = images[i].getPixel(100, 100);
			//std::cout << c.r << ' ' << c.b << ' ' << c.g << '\n';
			//std::cout << 1 << '\n';

			//sf::Texture tx;
			//tx.create(x, y);
			//tx.update(images[i]);  
			
			//std::cout << 1 << '\n';                                                                                    //!!!!!!!!!!
		}
	}

	StorageImages(const StorageImages& stImages)
	{
		name = stImages.name;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}
	}

	~StorageImages()
	{
		delete[] images;
	}

	StorageImages& operator = (const StorageImages& stImages)
	{
		name = stImages.name;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}

		return *this;
	}

	String getName()
	{
		return name;
	}

	sf::Image* getImage (const int index)
	{
		//std::cout << index << '\n';
		assert(index < numberOfImages);
		return &images[index];
	}

	int getNumberOfImages()
	{
		return numberOfImages;
	}
};


class Sprite          // What do we should to name it?
{
	int numberOfStorages;
	StorageImages* images;
//	sf::Texture texture;
//	sf::RectangleShape shape;

public:

//	sf::RectangleShape shape;

	sf::Image* getImage(String nameStorage, const int index)
	{
		//std::cout << nameStorage << '\n';
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
			{
				return images[i].getImage(index);
			}
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}

	Sprite(StorageImages* images, int numberOfStorage)
	{
		this->images = new StorageImages[numberOfStorage];
		this->numberOfStorages = numberOfStorage;
		for (int i = 0; i < numberOfStorage; i++)
		{
			this->images[i] = images[i];
		}
		
		//texture.loadFromImage(this->getImage(nameFistStImages, 0));
		//shape.setTexture(&texture);
	}

	Sprite(String imagesName, String nameOfFile)
	{
		images = new StorageImages[1];
		numberOfStorages = 1;
		StorageImages image (imagesName, 1, &nameOfFile);
		images[0] = image;

		//texture.loadFromImage(this->getImage(imagesName, 0));
		//shape.setTexture(&texture);
	}

	~Sprite()
	{
		delete[] images;
	}

	int getSizeStorage(String nameStorage)
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
			{
				return images[i].getNumberOfImages();
			}
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}
	/*
	void changeTexture(String nameStorage, const int index)
	{
		texture.loadFromImage(this->getImage(nameStorage, index));
	}

	void setSize(Vector2f size)
	{
		shape.setSize(sf::Vector2f(size.x, size.y));
	}
	*/
};



class GameObject
{
protected:
	Vector2f* vertexs;
	int numberOfVertexs = 0;
	Vector2f size = Vector2f(0, 0);
	Vector2f velosity = Vector2f(0, 0);
	float mass = 1;
public:
	Vector2f position;
	String name;

	Vector2f changeImpulse = Vector2f(0, 0);
	
	//Vector2f rightBottomCorrow;

	GameObject() {}

	GameObject(Vector2f v, String str) : position(v), name(str) {}

	virtual void draw(Camera* camera) {}

	virtual void changeTexture(String nameStorage, const int index) {}

	//virtual void changeTexture() {}
	
	//virtual void setCurrentImageIndex(int index) {}

	//virtual void setCurrentImage(String name, int index) {}

	virtual void animation(float timeBeetweenFrame) {}



	virtual Vector2f getPositionVertex(int number) { return Vector2f(0, 0); }

	int getNumberOfVertex() { return numberOfVertexs;}

	Vector2f getSize() { return size; }

	virtual Vector2f getVelosity() { return velosity; }

	virtual float getMass() { return mass; }

	virtual Vector2f isCollide(GameObject& gObj) { return Vector2f(0, 0); }

	virtual void resolutionCollision(GameObject& gObj, Vector2f vectorCollision) {}

	virtual void setVelosity(Vector2f v) {}

	virtual void move(float dt) {}

	virtual void changeVelosity() {}

	virtual void reactionOnForce(Vector2f force, float dt) {}

	virtual void nullChangeImpulse() {}

	virtual void gravitation(Vector2f g, float dt) {}

	virtual Vector2f getPositionCenter() { return Vector2f(0, 0); }



	virtual String getOrientation() { return "NULL"; }

	virtual void getDamage(int damage) {};

	virtual int getHitPoints() { return 1; }

	virtual String getTypeName() { return "GameObject"; }

	virtual void setOrientation(String orient) {};
};


class Camera: public GameObject
{
	sf::RenderWindow window;
	Vector2f velosity;
	int sizeWindowX;
	int sizeWindowY;
	sf::Color windowColor;
	//sf::VideoMode videoMode;

public:

	Camera(String name, Vector2f position, int sizeWindowX = 1960, int sizeWindowY = 1080, sf::Color color = sf::Color(0,0,0))
	{
		this->name = name;
		this->position = position;
		this->sizeWindowX = sizeWindowX;
		this->sizeWindowY = sizeWindowY;
		sf::VideoMode videoMode(sizeWindowX, sizeWindowY);
		windowColor = color;
		window.create(videoMode, name.c_str());
	}

	void close()
	{
		window.close();
	}

	bool objectInDrawableSpace(sf::Vector2f pos, int charactSize)
	{
		//std::cout << (pos.x > -charactSize);
		//std::cout << (pos.y > -charactSize);
		//std::cout << (pos.x < charactSize + sizeWindowX);
		//std::cout << (pos.y < charactSize + sizeWindowY) << '\n';
		//std::cout << pos << '\n';
		return (pos.x > -charactSize) && (pos.y > -charactSize) && (pos.x < charactSize + sizeWindowX) && (pos.y < charactSize + sizeWindowY);
	}

	void draw(sf::Shape* shape, sf::Vector2f shapePosition, int charactSize)
	{
		sf::Vector2f shapePositionInCamera = shapePosition - sf::Vector2f(position.x, position.y);

		//std::cout << shapePositionInCamera << '\n';
		//std::cout << ":::" << objectInDrawableSpace(shapePositionInCamera, charactSize) << '\n';

		//std::cout << ".draw" << '\n';

		if (objectInDrawableSpace(shapePositionInCamera, charactSize))
		{
			//std::cout << "kuygfy" << '\n';
			shape->setPosition(shapePositionInCamera);
			window.draw(*shape);
		}
	}

	bool pollEvent(sf::Event& event)
	{
		return window.pollEvent(event);
	}

	void display()
	{
		window.display();
		window.clear();
	}

	void displayWithoutClear()           // You need double draw background objects and 
	{
		window.display();
	}

	void setFrameralLimit(int fps)
	{
		window.setFramerateLimit(fps);
	}

	bool isOpen()
	{
		return window.isOpen();
	}



	void move(float dt)
	{
		position += velosity * dt;
	}
};



class StdGameObject: public GameObject
{
protected:
	
	Sprite* sprite;
	String nameCurrentImage;
	int indexCurrentImage;
	int characteristicSize;
	sf::Texture texture;
	sf::RectangleShape shape;
	float timeFromLastChangeImage = 0;
	float timeBeetweenImages = 0.05;

	//Vector2f velosity;
	//Vector2f changeImpulse = Vector2f(0, 0);
	//float mass;
	//Vector2f size;
	Vector2f centerMass;
	//Vector2f* vertexs;
	//int numberOfVertex;

	int hitPoints = 10;
	
public:

	//Vector2f changeImpulse = Vector2f(0, 0);

	StdGameObject()
	{
		if (!vertexs)
		{
			//std::cout << 1 << '\n';
			vertexs = new Vector2f[1];
		}
	};

	void setSize(Vector2f size)
	{
		this->size = size;
		shape.setSize(sf::Vector2f(size.x, size.y));
		characteristicSize = max(size.x, size.y);
	}

	StdGameObject(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs,
		int numberOfVertexs, String nameFistStImages, Vector2f size, Vector2f centerMass, int mass)
	{
		//std::cout << "StdGameObject1" << '\n';

		this->name = name;
		this->position = position;
		//rightBottomCorrow = position + size;
		this->sprite = sprite;
		this->numberOfVertexs = numberOfVertexs;
		this->vertexs = new Vector2f[numberOfVertexs];
		this->centerMass = centerMass;
		this->mass = mass;

		for (int i = 0; i < numberOfVertexs; i++)
		{
			this->vertexs[i] = vertexs[i];
		}

		nameCurrentImage = nameFistStImages;

		//std::cout << nameCurrentImage << '\n';

		indexCurrentImage = 0;

		texture.create(size.x, size.y);
		texture.update(*(sprite->getImage(nameFistStImages, 0)));   //!!!!!
		shape.setTexture(&texture);

		this->setSize(size);
	}

	StdGameObject(const StdGameObject& gameObject)
	{
		std::cout << "StdGameObject2" << '\n';

		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];

		this->nameCurrentImage = nameCurrentImage;
		this->indexCurrentImage = indexCurrentImage;

		texture.loadFromImage(*(sprite->getImage(nameCurrentImage, indexCurrentImage)));
		shape.setTexture(&texture);

		this->setSize(gameObject.size);
		//this->rightBottomCorrow = position + size;
	}

	~StdGameObject()
	{
		//std::cout << "dStdGameObject : " << name << '\n';

		delete[] vertexs;
	}

	StdGameObject& operator = (const StdGameObject& gameObject)
	{
		if (vertexs)
			delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		nameCurrentImage = gameObject.nameCurrentImage;
		indexCurrentImage = gameObject.indexCurrentImage;
		size = gameObject.size;

		position = gameObject.position;
		velosity = gameObject.velosity;
		mass = gameObject.mass;
		centerMass = gameObject.centerMass;

		//rightBottomCorrow = position + size;
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];

		return *this;
	}

	void setCurrentImage(String name, int index)
	{
		//std::cout << "setCurrentImage" << '\n';

		nameCurrentImage = name;
		indexCurrentImage = index;
		sf::Image im = *(sprite->getImage(name, index));
	}

	void setCurrentImageIndex(int index)
	{
		//std::cout << "setCurrentImageIndex" << '\n';

		indexCurrentImage = index;
		sf::Image im = *(sprite->getImage(nameCurrentImage, index));
	}

	void changeTexture(String nameStorage, const int index)
	{
		//std::cout << "changeTexture" << '\n';

		nameCurrentImage = nameStorage;
		indexCurrentImage = index;
		texture.loadFromImage(*(sprite->getImage(nameStorage, index)));
	}

	void changeTexture()
	{
		//std::cout << "changeTexture" << '\n';

		texture.loadFromImage(*(sprite->getImage(nameCurrentImage, indexCurrentImage)));
	}
	
	void draw(Camera* camera)
	{
		//std::cout << nameCurrentImage << '\n';

		//this->changeTexture(nameCurrentImage, indexCurrentImage);
		//this->shape.setPosition(position.x, position.y);
		camera->draw(&shape, sf::Vector2f(position.x, position.y) , characteristicSize);
	}
	
	void animation(float timeBeetweenFrame)
	{
		timeFromLastChangeImage += timeBeetweenFrame;
		if (timeFromLastChangeImage > timeBeetweenImages)
		{
			timeFromLastChangeImage = 0;
			if (sprite->getSizeStorage(nameCurrentImage) - 1 <= indexCurrentImage)
				indexCurrentImage = -1;
			setCurrentImageIndex(indexCurrentImage + 1);
			this->changeTexture();
			return;
		}
	}



	Vector2f getPositionVertex(int number)
	{
		assert(number < numberOfVertexs);
		return position + vertexs[number];
	}

	Vector2f getVertex(int number)
	{
		assert(number < numberOfVertexs);
		return vertexs[number];
	}

	Vector2f getPositionCenter()
	{
		return centerMass + position;
	}

	Vector2f getInwardNormal(int numberVertex)
	{
		Vector2f v(0, 0);
		if (numberVertex == 0)
			v = this->getVertex(numberOfVertexs - 1) - this->getVertex(1);
		if (numberVertex == (numberOfVertexs - 1))
			v = this->getVertex(0) - this->getVertex(numberVertex - 1);
		if ((numberVertex != 0) && (numberVertex != (numberOfVertexs - 1)))
			v = this->getVertex(numberVertex - 1) - this->getVertex(numberVertex + 1);

		Vector2f d(v.y, -v.x);
		Vector2f a = this->getVertex(numberVertex) - centerMass;
		return ((a * d) * d * (-1)).norm();
	}

	Vector2f isCollide(GameObject& gObj)
	{
		if ((position - gObj.position).mod() > (size + gObj.getSize()).mod())
			return Vector2f(0, 0);
		int gObjNumberOfVertexs = gObj.getNumberOfVertex();
		if (gObjNumberOfVertexs < 2)
			return Vector2f(0, 0);

		Vector2f vectorCollision(0, 0);

		for (int numberVertex = 0; numberVertex < numberOfVertexs; numberVertex++)
		{
			bool flag = true;
			for (int numberGObjvertex = 1; numberGObjvertex < gObjNumberOfVertexs; numberGObjvertex++)
			{
				//std::cout << gObj.name << '\n';
				Vector2f v1 =  gObj.getPositionVertex(numberGObjvertex) - gObj.getPositionVertex(numberGObjvertex - 1);
				Vector2f v2 = this->getPositionVertex(numberVertex)     - gObj.getPositionVertex(numberGObjvertex - 1);

				//std::cout << numberVertex << ' ' << numberGObjvertex << " : " << v1 << " ; " << v2 << '\n';

				if (v1.vectComp(v2) > 0)
				{
					flag = false;
					break;
				}
			}
			Vector2f v1 =  gObj.getPositionVertex(0)            - gObj.getPositionVertex(gObjNumberOfVertexs - 1);
			Vector2f v2 = this->getPositionVertex(numberVertex) - gObj.getPositionVertex(gObjNumberOfVertexs - 1);

			if (v1.vectComp(v2) > 0)
			{
				continue;
			}

			if (flag)
			{
				//std::cout << (this->getVertex(numberVertex) - centerMass) << '\n';
				vectorCollision += this->getInwardNormal(numberVertex);
			}
		}

		if (vectorCollision.mod() == 0)
			return vectorCollision;

		return vectorCollision.norm();
	}

	void resolutionCollision(GameObject& gObj, Vector2f vectorCollision)
	{
		if (vectorCollision.mod() == 0)
			return;
		float progVelosity1 = velosity.projection(vectorCollision);
		float progVelosity2 = gObj.getVelosity().projection(vectorCollision);

		float redMass = reducedMass(mass, gObj.getMass());

		float dp = redMass * (progVelosity1 - progVelosity2);

		if (dp < 0)
			changeImpulse -= 2 * dp * vectorCollision;
	}

	void setVelosity(Vector2f v)
	{
		velosity = v;
	}

	void move(float dt)
	{
		position += velosity * dt;
	}

	void changeVelosity()
	{
		velosity += changeImpulse / mass;
	}

	void reactionOnForce(Vector2f force, float dt)
	{
		changeImpulse += force * dt;
	}

	void nullChangeImpulse()
	{
		changeImpulse = Vector2f(0, 0);
	}

	void gravitation(Vector2f g, float dt)
	{
		changeImpulse += g * mass * dt;
	}



	void getDamage(int damage)
	{
		hitPoints -= damage;
	}

	int getHitPoints()
	{
		return hitPoints;
	}
};


class Wall : public GameObject
{
	//Vector2f velosity;
	//Vector2f changeImpulse = Vector2f(0, 0);
	//float mass;
	//Vector2f size;
	//Vector2f centerMass;
	//Vector2f* vertexs;
	//int numberOfVertex;


public:

	Wall(String name, Vector2f position, Vector2f* vertexs,
		int numberOfVertexs, Vector2f size, int mass)
	{
		//std::cout << "StdGameObject1" << '\n';

		this->name = name;
		this->position = position;
		//rightBottomCorrow = position + size;
		this->numberOfVertexs = numberOfVertexs;
		this->vertexs = new Vector2f[numberOfVertexs];
		//this->centerMass = centerMass;
		this->mass = mass;

		for (int i = 0; i < numberOfVertexs; i++)
		{
			this->vertexs[i] = vertexs[i];
		}
		this->size = size;
	}

	Wall(Wall& gameObject)
	{
		//std::cout << "StdGameObject2" << '\n';

		delete[] vertexs;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];
		size = gameObject.size;
	}

	~Wall()
	{
		//std::cout << "dStdGameObject : " << name << '\n';

		delete[] vertexs;
	}

	Wall& operator = (Wall& gameObject)
	{
		delete[] vertexs;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		size = gameObject.size;
		//rightBottomCorrow = position + size;
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];
	}



	Vector2f getPositionVertex(int number)
	{
		//std::cout << number << ' ' << numberOfVertexs << '\n';
		assert(number < numberOfVertexs);
		return vertexs[number] + position;
	}

	Vector2f getVertex(int number)
	{
		assert(number < numberOfVertexs);
		return vertexs[number];
	}

	Vector2f isCollide(GameObject& gObj)
	{
		return Vector2f(0, 0);
	}

	void resolutionCollision(GameObject& gObj, Vector2f vectorCollision)
	{
		return;
	}
};


class StationaryGameObject : public GameObject
{

	Sprite* sprite;
	String nameCurrentImage;
	int indexCurrentImage;
	int characteristicSize;
	sf::Texture texture;
	sf::RectangleShape shape;
	float timeFromLastChangeImage = 0;
	float timeBeetweenImages = 0.05;


	Vector2f centerMass;



public:

	void setSize(Vector2f size)
	{
		this->size = size;
		shape.setSize(sf::Vector2f(size.x, size.y));
		characteristicSize = max(size.x, size.y);
	}

	StationaryGameObject(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs,
		int numberOfVertexs, String nameFistStImages, Vector2f size, Vector2f centerMass, int mass)
	{
		//std::cout << "StdGameObject1" << '\n';

		this->name = name;
		this->position = position;
		//rightBottomCorrow = position + size;
		this->sprite = sprite;
		this->numberOfVertexs = numberOfVertexs;
		this->vertexs = new Vector2f[numberOfVertexs];
		this->centerMass = centerMass;
		this->mass = mass;

		for (int i = 0; i < numberOfVertexs; i++)
		{
			this->vertexs[i] = vertexs[i];
		}

		nameCurrentImage = nameFistStImages;

		//std::cout << nameCurrentImage << '\n';

		indexCurrentImage = 0;

		texture.create(size.x, size.y);
		texture.update(*(sprite->getImage(nameFistStImages, 0)));   //!!!!!
		shape.setTexture(&texture);

		this->setSize(size);
	}

	StationaryGameObject(StationaryGameObject& gameObject)
	{
		std::cout << "StdGameObject2" << '\n';

		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];

		this->nameCurrentImage = nameCurrentImage;
		this->indexCurrentImage = indexCurrentImage;

		texture.loadFromImage(*(sprite->getImage(nameCurrentImage, indexCurrentImage)));
		shape.setTexture(&texture);

		this->setSize(gameObject.size);
		//this->rightBottomCorrow = position + size;
	}

	~StationaryGameObject()
	{
		//std::cout << "dStdGameObject : " << name << '\n';

		delete[] vertexs;
	}

	StationaryGameObject& operator = (StationaryGameObject& gameObject)
	{
		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertexs = gameObject.numberOfVertexs;
		vertexs = new Vector2f[numberOfVertexs];
		nameCurrentImage = gameObject.nameCurrentImage;
		indexCurrentImage = gameObject.indexCurrentImage;
		size = gameObject.size;
		//rightBottomCorrow = position + size;
		for (int i = 0; i < numberOfVertexs; i++)
			this->vertexs[i] = vertexs[i];
	}

	void setCurrentImage(String name, int index)
	{
		//std::cout << "setCurrentImage" << '\n';

		nameCurrentImage = name;
		indexCurrentImage = index;
		sf::Image im = *(sprite->getImage(name, index));
	}

	void setCurrentImageIndex(int index)
	{
		//std::cout << "setCurrentImageIndex" << '\n';

		indexCurrentImage = index;
		sf::Image im = *(sprite->getImage(nameCurrentImage, index));
	}

	void changeTexture(String nameStorage, const int index)
	{
		//std::cout << "changeTexture" << '\n';

		nameCurrentImage = nameStorage;
		indexCurrentImage = index;
		texture.loadFromImage(*(sprite->getImage(nameStorage, index)));
	}

	void changeTexture()
	{
		//std::cout << "changeTexture" << '\n';

		texture.loadFromImage(*(sprite->getImage(nameCurrentImage, indexCurrentImage)));
	}

	void draw(Camera* camera)
	{
		//std::cout << nameCurrentImage << '\n';

		//this->changeTexture(nameCurrentImage, indexCurrentImage);
		//this->shape.setPosition(position.x, position.y);
		camera->draw(&shape, sf::Vector2f(position.x, position.y), characteristicSize);
	}



	Vector2f getPositionVertex(int number)
	{
		//std::cout << number << ' ' << numberOfVertexs << '\n';
		assert(number < numberOfVertexs);
		return vertexs[number] + position;
	}

	Vector2f getVertex(int number)
	{
		assert(number < numberOfVertexs);
		return vertexs[number];
	}

	Vector2f getPositionCenter()
	{
		return centerMass + position;
	}
};


class Player : public StdGameObject
{

	String orientation = "right";

public:

	Player(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs,
			int numberOfVertexs, String nameFistStImages, Vector2f size, Vector2f centerMass, int mass) : 
		StdGameObject(name, position, sprite, vertexs,
			numberOfVertexs, nameFistStImages, size, centerMass, mass)
	{}

	void resolutionCollision(GameObject& gObj, Vector2f vectorCollision)
	{
		if (vectorCollision.mod() == 0)
			return;

		if ((vectorCollision.y < 0) && (vectorCollision.x == 0))
		{
			changeImpulse = (-1) * mass * velosity;
			return;
		}

		float progVelosity1 = velosity.projection(vectorCollision);
		float progVelosity2 = gObj.getVelosity().projection(vectorCollision);

		float redMass = reducedMass(mass, gObj.getMass());

		float dp = redMass * (progVelosity1 - progVelosity2);

		if (dp < 0)
			changeImpulse -= 2 * dp * vectorCollision;
	}

	void changeOrientation(String orient)
	{
		if ((orient != "left") && (orient != "right"))
			assert(false);
		orientation = orient;
	}

	String getOrientation()
	{
		return orientation;
	}

	void setOrientation(String orient)
	{
		assert((orient == "left") || (orient == "right"));
		orientation = orient;
	}
};


class Knight : public StdGameObject
{
public:

	Knight(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs,
		int numberOfVertexs, String nameFistStImages, Vector2f size, Vector2f centerMass, int mass) :
		StdGameObject(name, position, sprite, vertexs,
			numberOfVertexs, nameFistStImages, size, centerMass, mass)
	{}

	void resolutionCollision(GameObject& gObj, Vector2f vectorCollision)
	{
		if (vectorCollision.mod() == 0)
			return;

		if ((vectorCollision.y < 0) && (vectorCollision.x == 0))
		{
			changeImpulse = (-1) * mass * velosity;
			return;
		}

		float progVelosity1 = velosity.projection(vectorCollision);
		float progVelosity2 = gObj.getVelosity().projection(vectorCollision);

		float redMass = reducedMass(mass, gObj.getMass());

		float dp = redMass * (progVelosity1 - progVelosity2);

		if (dp < 0)
			changeImpulse -= 2 * dp * vectorCollision;
	}
};


class FairBall : public StdGameObject
{
public:
	FairBall(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs,
		int numberOfVertexs, String nameFistStImages, Vector2f size, Vector2f centerMass, int mass) :
		StdGameObject(name, position, sprite, vertexs,
			numberOfVertexs, nameFistStImages, size, centerMass, mass)
	{}

	String getTypeName()
	{
		return "FairBall";
	}
};


