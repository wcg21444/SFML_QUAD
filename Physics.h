#pragma once
#include <SFML/Graphics.hpp>

class Object;

class Physics
{
	friend class Object;
public:
	static float dt;
public:
	float radius = 0.f;//��ΧȦ�뾶

	float mass = 0.f;

	//Displcements
	sf::Vector2f position = { 0.f,0.f };
	sf::Vector2f velocity = { 0.f,0.f };
	sf::Vector2f accelerate = { 0.f,0.f };

	sf::Vector2f position_old = { 0.f,0.f };//setPosition֮ǰ��Position
	sf::Vector2f velocity_old = { 0.f,0.f };//setVelocity֮ǰ��Velocity
	sf::Vector2f accelerate_old = { 0.f,0.f };//setAccelerate֮ǰ��Accelerate
	//TODO: Rotation
private:
	Physics() {};//ֻ����Object����й���
public:
	void setPosition(sf::Vector2f pos,Object* object);
	void setPosition(float x, float y, Object* object);
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float x, float y);
	void setAccelerate(sf::Vector2f acc);
	void setAccelerate(float x, float y);

	void updatePosition(Object* object);
	void updateVelocity();

};

