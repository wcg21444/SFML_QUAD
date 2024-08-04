#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "config.h"

template<typename T>
concept drawable = requires(sf::RenderWindow & wnd, T & obj) { wnd.draw(obj); };

template<typename T>
concept drawable_entity = requires(sf::RenderWindow & wnd, T & ent) { wnd.draw(ent.getShape()); };

class Renderer
{
private:
	sf::RenderWindow& m_window;
public:
	Renderer(sf::RenderWindow& wnd);
	//vertex 使用屏幕空间
	void renderLine(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, sf::Color color = sf::Color::White);
	template<drawable T_Drawable>
	//render使用屏幕空间
	void renderShape(T_Drawable& shape);
	template<drawable_entity T_Entity>
	void renderEntity(T_Entity& entity);
	template<drawable_entity T_Entity,typename Func>
	void renderEntityTransformation(T_Entity& entity, Func func);
};

template<drawable T_Drawable>
void Renderer::renderShape(T_Drawable& shape)
{
	m_window.draw(shape);
}

template<drawable_entity T_Entity>
inline void Renderer::renderEntity(T_Entity& entity)
{
	renderEntityTransformation(entity, [&]()->void {
		auto& shape = entity.getShape();
		m_window.draw(shape);
	});

}

template<drawable_entity T_Entity, typename Func>
inline void Renderer::renderEntityTransformation(T_Entity& entity,Func func)//坐标变换,从物理空间变换到屏幕空间进行渲染
{
	auto& shape = entity.getShape();

	shape.setPosition(shape.getPosition() * M2P);
	shape.setOrigin(shape.getOrigin() * M2P);

	func();	//执行渲染操作

	shape.setPosition(shape.getPosition() / M2P);
	shape.setOrigin(shape.getOrigin() / M2P);
}
