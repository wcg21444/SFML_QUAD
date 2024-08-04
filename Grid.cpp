#include "Grid.h"
/*
	p1
			
			p2
*/

Grid::Grid(sf::Vector2f p1, sf::Vector2f p2, float interval)
	:interval(interval)
{
	this->update(p1, p2, interval);
}

void Grid::update(sf::Vector2f p1, sf::Vector2f p2, float interval)
{
	if(interval>1)
	{
		XLines.clear();
		YLines.clear();

		float width = p2.x - p1.x;
		float height = p2.y - p1.y;

		int n_YLine = width / interval;//Y方向的线数量
		int n_XLine = height / interval;//X方向线的数量

		YLines.reserve(n_XLine);
		XLines.reserve(n_YLine);

		//YLine;
		for (int i = 0; i < n_YLine; ++i)
		{
			YLines.emplace_back(Line(sf::Vector2f(i * width / n_YLine, 0.f), sf::Vector2f(i * width / n_YLine, height)));
		}
		//XLines
		for (int i = 0; i < n_XLine; ++i)
		{
			XLines.emplace_back(Line(sf::Vector2f(0, i * height / n_XLine), sf::Vector2f(width, i * height / n_XLine)));
		}
	}
}

void Grid::draw(sf::RenderWindow& wnd)
{
	for (const auto& l : XLines)
	{
		l.draw(wnd);
	}
	for (const auto& l : YLines)
	{
		l.draw(wnd);
	}
}
