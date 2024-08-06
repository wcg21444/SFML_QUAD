#include "Physics.h"
#include "Object.h"
#include <iostream>

#include "Base.h"
float Physics::dt;


void Physics::setPosition(sf::Vector2f pos, Object* object)
{
	position_old = pos;
	object->setPosition(pos);
}

void Physics::setPosition(float x, float y, Object* object)
{
	object->setPosition(sf::Vector2f(x, y));
}

void Physics::setVelocity(sf::Vector2f vel)
{
	velocity_old = velocity;
	velocity = vel;
}

void Physics::setVelocity(float x, float y)
{
	setVelocity(sf::Vector2f(x, y));
}

void Physics::setAccelerate(sf::Vector2f acc)
{
	accelerate_old = accelerate;
	accelerate = acc;
}

void Physics::setAccelerate(float x, float y)
{
	setAccelerate(sf::Vector2f(x,y));
}

void Physics::updatePosition(Object* object)
{
	object->setPosition(this->position + this->velocity * dt + this->accelerate * dt * dt / 2);
}

void Physics::updateVelocity()
{
	sf::Vector2f v = velocity;
	v += (accelerate + accelerate_old) * dt / 2;
	setVelocity(v);
}

void Physics::boundrayRebound(sf::Rect<float> boundary)
{

	if (position.x < boundary.left)
	{
		sf::Vector2f new_vel(velocity);
		new_vel.x = -new_vel.x;
		setVelocity(new_vel);
	}
	if (position.x > boundary.left+boundary.width )
	{
		sf::Vector2f new_vel(velocity);
		new_vel.x = -new_vel.x;
		setVelocity(new_vel);
	}
	if (position.y < boundary.top)
	{
		sf::Vector2f new_vel(velocity);
		new_vel.y = -new_vel.y;
		setVelocity(new_vel);
	}
	if (position.y > boundary.top+boundary.height )
	{
		sf::Vector2f new_vel(velocity);
		new_vel.y = -new_vel.y;
		setVelocity(new_vel);
	}
}
