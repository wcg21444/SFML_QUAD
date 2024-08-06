#include "Object.h"
#include "App.h"
#include "Base.h"
Box::Box(sf::Vector2f center_position, sf::FloatRect rect)
{
	shape = sf::RectangleShape(rect.getSize());
	sf::Vector2f origin = (rect.getSize() - rect.getPosition());
	origin.x /= 2;
	origin.y /= 2;
	shape.setOrigin(origin);
	physics.setPosition(center_position, this);
	shape.setFillColor(sf::Color::Green);

	bound_box = sf::Rect<float>(center_position - rect.getSize() / 2, rect.getSize());
}

void Box::draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
}

void Box::update(App& app)
{
	auto& wnd = app.getWindow();
	physics.setAccelerate(rnd_x.getNum()/160, rnd_y.getNum() / 90);

	physics.boundrayRebound(sf::Rect<float>(sf::Vector2f(0.f,0.f), (sf::Vector2f)wnd.getSize()));
	
	physics.updateVelocity();
	physics.updatePosition(this);

}

void Box::setPosition(sf::Vector2f pos)
{
	Object::setPosition(pos);

	//TODO: Transformation
	shape.setPosition(pos);
}


Object::Object()
{
}

Object::~Object()
{
}

void Object::setPosition(sf::Vector2f pos)
{	
	physics.position_old = physics.position;
	physics.position = pos;
}
