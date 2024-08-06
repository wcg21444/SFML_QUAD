#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<functional>

class Object;
class DivsionOutline
{
private:
	sf::RectangleShape shape;
public:
	//size:正方形半边长
	DivsionOutline() {}
	DivsionOutline(float size, sf::Vector2f center, sf::Color color = sf::Color::Yellow);
	DivsionOutline(sf::Rect<float> rect, sf::Color color = sf::Color::Yellow);
	void draw(sf::RenderWindow& wnd);
};

class QuadtreeNode
{
	friend class Quadtree;
private:
	QuadtreeNode* parent;
	QuadtreeNode* children[4];
	std::vector<Object*> objects;
	DivsionOutline div_outline;
	int curr_depth;//当前节点深度
	sf::Rect<float> div_area;
	sf::Vector2f div_center;
	sf::Vector2f div_radius;
public:
	QuadtreeNode(QuadtreeNode* parent_, std::vector<Object*> objects_, sf::Rect<float> div_area_, int depth_, const Quadtree* tree_);
	bool isLeaveNode();
	void draw(sf::RenderWindow& wnd);
};

class Quadtree
{
	friend class QuadtreeNode;
private:
	int max_depth;
	int max_node_objects;
	sf::Rect<float> worldspace;
	QuadtreeNode* root;
	int depth;
public:
	Quadtree(std::vector<Object*> objects_, int max_depth_, int max_num_,sf::Rect<float> worldspace_);
	Quadtree(const Quadtree&) = delete;
	Quadtree& operator=(const Quadtree&) = delete;

	void travelRecursion(QuadtreeNode* curr_node, std::function<void(QuadtreeNode*)> operation);

	void travel(std::function<void(QuadtreeNode*)> operation);

	void draw(sf::RenderWindow& wnd);
};
