#pragma once
#include <SFML/Graphics.hpp>

class App
{
private:
	sf::RenderWindow* window;
public:
	~App();
	void createWindow(int width, int height, std::string title);
	sf::RenderWindow& getWindow();
};