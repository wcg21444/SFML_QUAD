#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Physics.h"

class QuadtreeNode;
class App;

class Object
{
friend QuadtreeNode;
protected:
	Physics physics;
	QuadtreeNode* masterNode;//ËùÊô½Úµã
	sf::Rect<float> bound_box;
public:
	Object();
	virtual ~Object();
	virtual void update(App& app) = 0;
	virtual void setPosition(sf::Vector2f pos);
	virtual void draw(sf::RenderWindow& wnd) = 0;
	inline  Physics& getPhysics() { return physics; }
};

class Box :public Object
{
private:
	sf::RectangleShape shape;
	Random<float> rnd_x = Random<float>(-1920.f, 1920.f);
	Random<float> rnd_y = Random<float>(-1080.f, 1080.f);
public:
	Box(sf::Vector2f center_position, sf::FloatRect rect);
	void draw(sf::RenderWindow& wnd);
	void update(App& app) override;
	void setPosition(sf::Vector2f pos) override;


};