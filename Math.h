#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

//零向量
const sf::Vector2f ZV = { 0.f,0.f };

class Ratio
{
private:
	int num;
	int den;
public:
	Ratio(int num = 0, int den = 1) :num(num), den(den) {};
	inline int getNum() const { return num; }
	inline int getDen() const { return den; }
	inline float getVal() { return (float)this->getNum() / this->getDen(); }

};

inline Ratio operator*(Ratio r1, Ratio r2)
{
	return Ratio(r1.getNum() * r2.getNum(), r1.getDen() * r2.getDen());
}

inline Ratio operator/(Ratio r1, Ratio r2)
{
	return Ratio(r1.getNum() * r2.getDen(), r1.getDen() * r2.getNum());
}

template<typename Ty>
concept Vec = (bool)std::is_same<Ty, sf::Vector2f>()|| (bool)std::is_same<Ty, sf::Vector2i >()||(bool)std::is_same<Ty, sf::Vector2u>();
template <Vec Ty_vec>
inline Ty_vec operator*(Ty_vec v_real, Ratio r_real)
{
	v_real.x = v_real.x * r_real;
	v_real.y = v_real.y * r_real;
	return v_real;
}
template <Vec Ty_vec2f>
inline Ty_vec2f operator*(Ratio r_real, Ty_vec2f v_real)
{
	v_real.x = v_real.x * r_real;
	v_real.y = v_real.y * r_real;
	return v_real;
}
template <Vec Ty_vec2f>
inline Ty_vec2f operator/(Ty_vec2f v_real, Ratio r_real)
{
	v_real.x = v_real.x / r_real;
	v_real.y = v_real.y / r_real;
	return v_real;
}

template<typename Ty>
concept is_num = (bool)std::is_arithmetic<Ty>();

template<is_num Ty_num>
inline float operator*(Ty_num n, Ratio r_real)
{
	return n * (float)r_real.getNum() / r_real.getDen();
}

template<is_num Ty_num>
inline float operator*(Ratio r_real, Ty_num n)
{
	return n * (float)r_real.getNum() / r_real.getDen();
}

template<is_num Ty_num>
inline float operator/(Ty_num n, Ratio r_real)
{
	return n * (float)r_real.getDen() / r_real.getNum();
}

namespace VMf
{
	//求向量长度
	inline float getLength(sf::Vector2f vec)
	{
		return (float)sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	//求v1 点乘 v2
	inline float dot(sf::Vector2f v1, sf::Vector2f v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	//求向量1在向量2上的投影向量
	inline sf::Vector2f getProjection(sf::Vector2f v1, sf::Vector2f v2)	
	{
		return v2 * dot(v1, v2) / (getLength(v2) * getLength(v2));
	}

	//求v1 x v2
	inline sf::Vector3f cross_2x2(sf::Vector2f v1, sf::Vector2f v2)
	{
		return sf::Vector3f(0, 0, v1.x * v2.y - v1.y * v2.x);
	}

	//v2 x v3
	inline sf::Vector2f cross_2x3z(sf::Vector2f v2, sf::Vector3f v3)
	{
		return sf::Vector2f(v2.y * v3.z, -v2.x * v3.z);
	}

	//v3 x v2
	inline sf::Vector2f cross_z3x2(sf::Vector3f v3, sf::Vector2f v2)
	{
		return sf::Vector2f(v2.x * v3.z, -v2.y * v3.z);
	}
}
