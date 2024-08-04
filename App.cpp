#include "App.h"

App::~App()
{
	if (window != nullptr)
	{
		delete window;
	}
}

void App::createWindow(int width,int height,std::string title)
{
	if (window != nullptr)
	{
		throw std::runtime_error("Window already exists");
	}
	else
	{
		window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	}
}

sf::RenderWindow& App::getWindow()
{
	return *window;
}
