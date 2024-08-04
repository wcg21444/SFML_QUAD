#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
class Object;

class QuadtreeNode
{
private:
	QuadtreeNode* children[4];
	std::vector<Object*> objects;
	int curr_depth;
	sf::Vector2f div_center;
	float div_size;//划分正方形的半边长 
public:
	QuadtreeNode(Object* object, sf::Vector2f center, float current_depth,float div_center);
};

class Quadtree
{
private:
	int max_depth;
	int max_number_objects;
	float space_size; //世界空间正方形边长尺寸
	QuadtreeNode* root;
public:
	Quadtree(std::vector<Object*> objects, int max_depth, int max_num);
};
