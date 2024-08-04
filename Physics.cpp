#include "Physics.h"
#include "Object.h"
#include "Math.h"
#include <iostream>
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
