#include "Object.h"
#include "App.h"
Box::Box(sf::Vector2f center_position, sf::FloatRect rect)
{
	shape = sf::RectangleShape(rect.getSize());
	sf::Vector2f origin = (rect.getSize() - rect.getPosition());
	origin.x /= 2;
	origin.y /= 2;
	shape.setOrigin(origin);
	shape.setPosition(center_position);
	shape.setFillColor(sf::Color::Red);

	physics.radius = sqrt(origin.x * origin.x + origin.y * origin.y);
}

void Box::draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
}

void Box::update(App& app)
{
	auto& wnd = app.getWindow();
	physics.setAccelerate(rnd_x.getNum()/2000, rnd_y.getNum()/2000);

	physics.updatePosition(this);
	physics.updateVelocity();
}

void Box::setPosition(sf::Vector2f pos)
{
	this->physics.position = pos;

	//TODO: Transformation
	shape.setPosition(pos);
}


Object::Object()
{
}

Object::~Object()
{
}
