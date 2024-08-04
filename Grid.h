#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Line
{
private:
	sf::Vertex endPoints[2];
public:
	Line(sf::Vertex p1, sf::Vertex p2)
	{
		endPoints[0] = p1;
		endPoints[1] = p2;
	}
	void draw(sf::RenderWindow& wnd) const// TODO: replace by renderer
	{
		wnd.draw(endPoints, 2, sf::Lines);
	}
};


class Grid
{
private:
	std::vector<Line> XLines;
	std::vector<Line> YLines;
	sf::Vector2f view[2];
	float interval;
public:
	Grid(sf::Vector2f p1, sf::Vector2f p2,float interval);

	void update(sf::Vector2f p1, sf::Vector2f p2, float interval);
	void draw(sf::RenderWindow& wnd);
};